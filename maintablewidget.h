#ifndef MAINTABLEWIDGET_H
#define MAINTABLEWIDGET_H

#include <QWidget>
#include "dbfacade.h"
#include "addnewbuilddialog.h"


namespace Ui {
class MainTableWidget;
}

class MainTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTableWidget(DBFacade *pFacade, QWidget *parent = 0);
    void setControls(bool stt);

    ~MainTableWidget();

private:
    Ui::MainTableWidget *ui;
    DBFacade    *m_facade;
    AddNewBuildDialog m_addBuild;
    QList<int>  buildingID;     // ИД всех строений. Для редактирования/добавления полей

private slots:
    void    connectionEstablished();    // соединение установлено
    void    on_pushAdd_clicked();
    void    on_pushEdit_clicked();
};

#endif // MAINTABLEWIDGET_H
