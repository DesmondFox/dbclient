#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // фасад и поток
    pFacade     = new DBFacade();
    pThread     = new QThread(this);

    pFacade->moveToThread(pThread);
    pThread->start(QThread::NormalPriority);

    // строка в статусбаре (теперь родителем её будет статусбар).
    statusLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText("Приложение загружено");


    // Изначально был у меня такой вариант соединения, но потом я понял, что это бесполезно
    // Исключения при таком соединении не обработать
//        connect(&loginDlg,  SIGNAL(sendData(QString,QString,QString,QString)),
//                pFacade,    SLOT(createConnection(QString,QString,QString,QString)));

    connect(this, SIGNAL(closeConnection()), pFacade, SLOT(closeConnection()));
    connect(this, SIGNAL(sendConnectionData(QString,QString,QString,QString)),
            pFacade, SLOT(createConnection(QString,QString,QString,QString)));


}

MainWindow::~MainWindow()
{
    emit closeConnection();
    pThread->terminate();
    delete pFacade;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    //
    // Открытие диалога авторизации
    //

    loginDlg.exec();


    try
    {
        // creating connection and processing exception
        statusLabel->setText("Подключение...");

        emit sendConnectionData(loginDlg.getHostname(),
                                loginDlg.getDatabase(),
                                loginDlg.getUsername(),
                                loginDlg.getPassword());

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

void MainWindow::on_actionClose_triggered()
{
    //
    // Завершение соединение
    //

    emit closeConnection();

    ui->actionClose->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    statusLabel->setText("Соединение закрыто");
}
