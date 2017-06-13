#include "addnewbuilddialog.h"
#include "ui_addnewbuilddialog.h"

AddNewBuildDialog::AddNewBuildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewBuildDialog)
{
    ui->setupUi(this);

    ui->cbGrom->setEnabled(false);

    connect(ui->cbCities,   SIGNAL(currentIndexChanged(int)), SLOT(slotCitiesChanged(int)));
    connect(ui->cbGrom,     SIGNAL(currentIndexChanged(int)), SLOT(slotCommChanged(int)));
}

AddNewBuildDialog::~AddNewBuildDialog()
{
    delete ui;
}

void AddNewBuildDialog::loadData()
{
    // Очищаем поля и заново загружаем списки городов и громад

    cities.clear();

    cities.append(m_facade->getCityList());

    QStringList lst;
    for (int i = 0; i < cities.length(); i++)
        lst << cities.at(i).name;


    ui->cbCities->clear();
    ui->cbCities->insertItems(0, lst);

    QStringList types;
    // Загрузка типов строений

    ui->cbTypes->clear();
    types = m_facade->getBuildTypesList();
    ui->cbTypes->insertItems(0, types);
}

void AddNewBuildDialog::setFacade(DBFacade *facade)
{
    m_facade    = facade;
}

void AddNewBuildDialog::setMode(EditMode em)
{
    currentMode = em;
    if (em == A_EDIT)
    {
        this->setWindowTitle("Добавление");
    }
    else
    {
        this->setWindowTitle("Редактирование");
    }

}

void AddNewBuildDialog::setCity(int ind)
{
    ui->cbCities->setCurrentIndex(ind);
}

void AddNewBuildDialog::setGrom(int ind)
{
    ui->cbGrom->setCurrentIndex(ind);
}

void AddNewBuildDialog::setType(int ind)
{
    ui->cbTypes->setCurrentIndex(ind);
}

void AddNewBuildDialog::setCounts(int CGov, int CCom, int CPriv)
{
    ui->sbGov->setValue(CGov);
    ui->sbComm->setValue(CCom);
    ui->sbPriv->setValue(CPriv);
}

void AddNewBuildDialog::setGromEnabled(bool stt)
{
    ui->cbGrom->setEnabled(stt);
}

void AddNewBuildDialog::on_buttonBox_accepted()
{
    // Добавление или редактирование строки в БД

    // Вытянем все значения из форм
    int RegID   = cities.at(ui->cbCities->currentIndex()).region;
    int CityID  = cities.at(ui->cbCities->currentIndex()).cityID;
    int TypeID  = ui->cbTypes->currentIndex()+1; // SQL indexes [1...
    int CGov    = ui->sbGov->value();
    int CComm   = ui->sbComm->value();
    int CPriv   = ui->sbPriv->value();


    // Добавление строки
    // ...и закинем в БД
    m_facade->addBuildToBase(CityID, RegID,
                             TypeID, CGov,
                             CComm,  CPriv);


}

void AddNewBuildDialog::slotCitiesChanged(int ind)
{
    groms.clear();
    ui->cbGrom->clear();

    if (ind != -1)
    {
        if (cities.at(ind).region == 0)
        {
            // Если это город, то мы просто закрываем поле
            ui->cbGrom->setEnabled(false);
            ui->cbTypes->setEnabled(true);
            ui->cbGrom->clear();
        }
        else
        {
            // Подгружаем все громады для текущего выбраного района
            ui->cbGrom->setEnabled(true);
            groms   = m_facade->getGromList(cities.at(ui->cbCities->currentIndex()).region);
            ui->cbGrom->insertItems(0, groms);
        }
    }
}

void AddNewBuildDialog::slotCommChanged(int ind)
{
    if (ind == 0)
        ui->cbTypes->setEnabled(true);
    else
        ui->cbTypes->setEnabled(false);
}

void AddNewBuildDialog::on_puspAddCity_clicked()
{
    /// TODO: Перейти к созданию городов
}
