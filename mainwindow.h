#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWidgets>

#include "dbfacade.h"
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();

    void on_actionClose_triggered();
    void slotConnect(QString hostnm,
                     QString dbnm,
                     QString usrnm,
                     QString pass);

private:
    Ui::MainWindow  *ui;
    DBFacade        *pFacade;
    LoginDialog     loginDlg;
    QLabel          *statusLabel;
};

#endif // MAINWINDOW_H
