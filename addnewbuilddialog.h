#ifndef ADDNEWBUILDDIALOG_H
#define ADDNEWBUILDDIALOG_H

#include <QDialog>
#include "dbfacade.h"

namespace Ui {
class AddNewBuildDialog;
}

enum EditMode
{
    A_EDIT,
    A_ADDING
};

class AddNewBuildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewBuildDialog(QWidget *parent = 0);

    ~AddNewBuildDialog();
    void loadData();
    void setFacade(DBFacade *facade);
    void setMode(EditMode em);

    // Изменение значений полей
    void setCity(int ind);
    void setGrom(int ind);
    void setType(int ind);
    void setCounts(int CGov, int CCom, int CPriv);
    void setGromEnabled(bool stt);

    QList<CityData> cities;     // Список городов с их параметрами
private slots:
    void on_buttonBox_accepted();
    void slotCitiesChanged(int ind);
    void slotCommChanged(int ind);

    void on_puspAddCity_clicked();

private:
    Ui::AddNewBuildDialog *ui;
    DBFacade    *m_facade;      // Фасад. Работа с БД

    QStringList groms;          // Список громад

    EditMode    currentMode;    // Текущий режим окна (редактирование/добавление)
                                // для того, что бы не создавать лишних классов


};

#endif // ADDNEWBUILDDIALOG_H
