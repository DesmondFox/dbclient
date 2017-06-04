#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QtWidgets>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    QString getHostname()   const;
    QString getDatabase()   const;
    QString getUsername()   const;
    QString getPassword()   const;

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
