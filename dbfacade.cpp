#include "dbfacade.h"

DBFacade::DBFacade(QObject *parent) : QObject(parent)
{
    pDB     = new QSqlDatabase();
    *pDB = pDB->addDatabase("QMYSQL");

    qDebug() << "Notice:\t Loaded drivers: " << pDB->drivers();
}

DBFacade::~DBFacade()
{
    this->closeConnection();
    delete pDB;
}

void DBFacade::createConnection(const QString &server,
                                const QString &dbname,
                                const QString &username,
                                const QString &password)
{
    // Соединяемся с базой

    pDB->setHostName(server);
    pDB->setDatabaseName(dbname);
    pDB->setPort(3306);
    pDB->setUserName(username);
    pDB->setPassword(password);

    qDebug() << "Notice:\t Creating connection";
    // Проверяем, если соединяется, то всё отлично, иначе кидаем исключение
    if (!pDB->open())
    {
        qDebug() << "Critical:\t No Connection " << pDB->lastError().text();
        emit losingConnection(pDB->lastError().text());
        return;
    }

    qDebug() << "Notice:\t Connection established " << pDB->hostName();
    emit connectionSuccessed();
}

void DBFacade::closeConnection()
{
    if (pDB->isOpen())
    {
        pDB->close();
        qDebug() << "Notice:\t Closing connection with " << pDB->hostName() << "'";
    }
}

