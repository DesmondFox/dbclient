#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql>
#include <QDebug>

#include "dbexception.h"

class DBFacade : public QObject
{
    Q_OBJECT
public:
    explicit    DBFacade(QObject *parent = 0);
    ~DBFacade();

private:
    QSqlDatabase *pDB;

signals:
    void connectionSuccessed();

public slots:
    void createConnection(const QString &server,
                          const QString &dbname,
                          const QString &username,
                          const QString &password);
    void closeConnection();
};

#endif // DBFACADE_H
