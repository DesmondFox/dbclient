#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql>
#include <QDebug>

#include "dbexception.h"

/// TODO: login/pass to MainWindow class and send to DBFacade as parameters
const QString login = "sql11177506";
const QString passw = "ITIziMsIWx";

class DBFacade : public QObject
{
    Q_OBJECT
public:
    explicit    DBFacade(QObject *parent = 0);
    ~DBFacade();

    bool createConnection(const QString &server,
                          const QString &dbname,
                          const QString &username,
                          const QString &password);
    void closeConnection();

private:


    QSqlDatabase *pDB;

signals:

public slots:
};

#endif // DBFACADE_H
