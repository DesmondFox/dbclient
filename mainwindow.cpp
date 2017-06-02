#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // фасад
    pFacade     = new DBFacade(this);

    // строка в статусбаре (теперь родителем её будет статусбар).
    statusLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText("Приложение загружено");

    connect(&loginDlg,  SIGNAL(sendData(QString,QString,QString,QString)),
                        SLOT(slotConnect(QString,QString,QString,QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    //
    // Открытие диалога авторизации
    //

    loginDlg.exec();
}

void MainWindow::on_actionClose_triggered()
{
    //
    // Завершение соединение
    //

    pFacade->closeConnection();
    ui->actionClose->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    statusLabel->setText("Соединение закрыто");
}

void MainWindow::slotConnect(QString hostnm, QString dbnm, QString usrnm, QString pass)
{
    //
    // Соединение с базой данных
    //

    try
    {
        // creating connection and processing exception
        pFacade->createConnection(hostnm, dbnm, usrnm, pass);
        ui->actionClose->setEnabled(true);
        ui->actionConnect->setEnabled(false);
        statusLabel->setText("Соединение открыто");
    }
    catch (DBException &e)
    {
        QMessageBox::critical(this, "Error", e.what());
        statusLabel->setText("Соединение сброшено");
        return;
    }
}
