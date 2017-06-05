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
    void connectionSuccess();

signals:
    void closeConnection();
    void sendConnectionData(QString hst,
                            QString db,
                            QString usr,
                            QString psw);
private:
    Ui::MainWindow  *ui;
    DBFacade        *pFacade;       // Фасад
    QThread         *pThread;       // Поток, в котором будет фасад
    LoginDialog     loginDlg;
    QLabel          *statusLabel;
};

#endif // MAINWINDOW_H
