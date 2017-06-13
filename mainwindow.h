#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWidgets>

#include "dbfacade.h"
#include "logindialog.h"
#include "maintablewidget.h"

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
    void connectionLosing(QString issue);

signals:
    void closeConnection();     // Завершить соединение с сервером
    void sendConnectionData(QString hst,
                            QString db,
                            QString usr,
                            QString psw);   // Открыть соединение
private:
    Ui::MainWindow  *ui;
    DBFacade        *pFacade;       // Фасад
    QThread         *pThread;       // Поток, в котором будет фасад
    LoginDialog     loginDlg;       // Диалог авторизации
    QLabel          *statusLabel;   // Строка состояния
    MainTableWidget *pMainTable;    // Главная таблица
};

#endif // MAINWINDOW_H
