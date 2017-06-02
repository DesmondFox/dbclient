#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

private slots:
    void okPressed();

signals:
    void sendData(QString hostname,
                  QString dbname,
                  QString usrname,
                  QString passwd);

};

#endif // LOGINDIALOG_H