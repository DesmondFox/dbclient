#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->pushConnect, SIGNAL(clicked(bool)), SLOT(okPressed()));
    connect(ui->pushCancel,  SIGNAL(clicked(bool)), SLOT(reject()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getHostname() const
{
    return ui->lineHostname->text();
}

QString LoginDialog::getDatabase() const
{
    return ui->lineDBname->text();
}

QString LoginDialog::getUsername() const
{
    return ui->lineUsername->text();
}

QString LoginDialog::getPassword() const
{
    return ui->linePass->text();
}

void LoginDialog::okPressed()
{
    QString errors;
    if (ui->lineHostname->text().isEmpty())
        errors.append("Заполните имя сервера\n");
    if (ui->lineDBname->text().isEmpty())
        errors.append("Заполните имя базы данных\n");
    if (ui->lineUsername->text().isEmpty())
        errors.append("Заполните имя пользователя");
    // Заполненость пароля проверяться не будет, т.к. бывают подключения без паролей

    if (errors.isEmpty())
    {
        emit accept();
        emit sendData(ui->lineHostname->text(),
                      ui->lineDBname->text(),
                      ui->lineUsername->text(),
                      ui->linePass->text());

        this->close();
    }
    else
        QMessageBox::information(this, "Вы не заполнили поля", errors);

}
