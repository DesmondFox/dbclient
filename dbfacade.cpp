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

bool DBFacade::createConnection(const QString &server,
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

    // Проверяем, если соединяется, то всё отлично, иначе кидаем исключение
    if (!pDB->open())
    {
        qDebug() << "Critical:\t No Connection";
        throw DBException(pDB->lastError().text());
        return false;
    }

    qDebug() << "Notice:\t Connection established " << pDB->hostName();
    return true;
}

void DBFacade::closeConnection()
{
    if (pDB->isOpen())
    {
        pDB->close();
        qDebug() << "Notice:\t Closing connection with " << pDB->hostName() << "'";
    }
}

