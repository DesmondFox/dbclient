#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(okPressed()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
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
        emit sendData(ui->lineHostname->text(),
                      ui->lineDBname->text(),
                      ui->lineUsername->text(),
                      ui->linePass->text());
    else
        QMessageBox::information(this, "Вы не заполнили поля", errors);

}