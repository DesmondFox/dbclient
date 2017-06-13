#include "maintablewidget.h"
#include "ui_maintablewidget.h"

MainTableWidget::MainTableWidget(DBFacade *pFacade,
                                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTableWidget)
{
    ui->setupUi(this);

    m_facade    = pFacade;
    m_facade->setMainTable(ui->tableView);

    ui->pushAdd->setEnabled(false);
    ui->pushDelete->setEnabled(false);
    ui->pushEdit->setEnabled(false);
    ui->tableView->setEnabled(false);


    ui->tableView->setSelectionBehavior(QTableView::SelectRows );
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView->setSelectionMode(QTableView::SingleSelection);

    m_addBuild.setFacade(m_facade);

    connect(m_facade,   SIGNAL(connectionSuccessed()),
                        SLOT(connectionEstablished()));
}

void MainTableWidget::setControls(bool stt)
{
    //
    // Установка состояния виджетов(вкл/выкл)
    //

    ui->pushAdd->setEnabled(stt);
    ui->pushDelete->setEnabled(stt);
    ui->pushEdit->setEnabled(stt);
    ui->tableView->setEnabled(stt);
}

MainTableWidget::~MainTableWidget()
{
    // Приходится удалять объект не сразу, т.к. поток всё ещё не закрыт.
//    m_facade->deleteLater();
    delete ui;
}

void MainTableWidget::connectionEstablished()
{
    // Подгрузим заранее ИД сооружений
    buildingID  = m_facade->getBuildingIDs();
}

void MainTableWidget::on_pushAdd_clicked()
{
    m_addBuild.setMode(A_ADDING);
    m_addBuild.loadData();
    m_addBuild.exec();
}

void MainTableWidget::on_pushEdit_clicked()
{
    if (ui->tableView->currentIndex().row() != -1)
    {
        // Вытягиваем данные с таблицы
        BuildData editData  = m_facade->getBuildData(ui->tableView->currentIndex().row());
        m_addBuild.setMode(A_EDIT);

        // Определение индекса города
        int cityIndex;
        for (int i = 0; i < m_addBuild.cities.length(); i++)
            if (m_addBuild.cities.at(i).cityID == editData.cityID)
            {
                cityIndex   = i;
                break;
            }



        m_addBuild.setCounts(editData.countGov, editData.countComm, editData.countPriv);

        m_addBuild.exec();



    }
}
