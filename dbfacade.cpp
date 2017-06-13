#include "dbfacade.h"

DBFacade::DBFacade(QObject *parent) : QObject(parent)
{
    pDB     = new QSqlDatabase();
    *pDB = pDB->addDatabase("QMYSQL");
    m_query = new QSqlQuery(*pDB);

    qDebug() << "Notice:\t Loaded drivers: " << pDB->drivers();
    qDebug() << "Notice:\t Facade loaded in thread " << this->thread();

    /// TODO: Создать таймер, который будет проверять соединение с БД

}

void DBFacade::setMainTable(QTableView *tbl)
{
    model   = new MTableModel(this, *pDB);

//    model->setTable("maintableview");
    tbl->setModel(model);
    model->select();
}

QList<CityData> DBFacade::getCityList()
{
    // Получить список городов/районов
    QList<CityData> cities;
    QString     query("SELECT CitiesAndCommunities.CityOrCommName, "
                        "CitiesAndCommunities.RegionID, CitiesAndCommunities.CityID\n"
                      "FROM CitiesAndCommunities\n"
                      "WHERE CitiesAndCommunities.IsCity = 1");

    // Немного костыльно закидывать ИД региона в структуры.
    // Но при такой схеме данных по-другому не выйдет
    CityData dt;
    if (exec(query))
    {
        while(m_query->next())
        {
            dt.name     = m_query->value(0).toString();
            dt.region   = m_query->value(1).toInt();
            dt.cityID   = m_query->value(2).toInt();
            cities << dt;
        }
    }

    qDebug() << "Notice:\t Loading city list";
    return cities;
}

QStringList DBFacade::getGromList(const int &regID)
{

    // Получить список громад по названию района
    QStringList grom;

    QString query("SELECT CitiesAndCommunities.CityOrCommName\n"
                  "FROM CitiesAndCommunities\n"
                  "WHERE CitiesAndCommunities.RegionID = "+QString::number(regID)+"\n"
                  "ORDER BY CitiesAndCommunities.IsCity DESC");

    if (exec(query))
        while (m_query->next())
            grom << m_query->value(0).toString();

    qDebug() << "Notice:\t Loading Communications list for REGID:" << regID;
    return grom;
}

QStringList DBFacade::getBuildTypesList()
{
    // Загрузка типов строений (Убежище/ПРУ)
    QStringList types;
    QString query("SELECT BuildingTypes.TypeName\n"
                  "FROM BuildingTypes");
    if (exec(query))
    {
        while (m_query->next())
            types << m_query->value(0).toString();
        qDebug() << "Notice:\t Loading Build types";
    }
    else
        qDebug() << "Critical:\t Failture loading of types: " << m_query->lastError().text();

    return types;
}

QList<int> DBFacade::getBuildingIDs()
{
    // Подгрузка ID всех строений.
    // Странное решение, но выбора у меня нету
    QList<int> buildingIDs;
    QString query("SELECT TableBuildings.BuildID \n"
                  "FROM TableBuildings \n"
                      "LEFT JOIN CitiesAndCommunities ON TableBuildings.CityOrCommID = CitiesAndCommunities.CityID \n"
                  "ORDER BY TableBuildings.Region ASC, CitiesAndCommunities.IsCity DESC, TableBuildings.CityOrCommID ASC");

    QSqlQuery sq;

    if (sq.exec(query))
    {
        while (sq.next())
            buildingIDs << sq.value(0).toInt();
        qDebug() << "Notice:\t Loading building IDs";
    }
    return buildingIDs;
}

BuildData DBFacade::getBuildData(int build_id)
{
    // Загрузка строки таблицы (главная таблица)
    BuildData data;

    if (exec(   "SELECT     TableBuildings.BuildID, \n"
                            "TableBuildings.Region, \n"
                            "TableBuildings.CityOrCommID, \n"
                            "TableBuildings.BuildTypeID, \n"
                            "TableBuildings.CountGov, \n"
                            "TableBuildings.CountComm, \n"
                            "TableBuildings.CountPrivate, \n"
                "CitiesAndCommunities.IsCity \n"
                "FROM TableBuildings, CitiesAndCommunities \n"
                "WHERE TableBuildings.BuildID = " + QString::number(build_id)))
    {
        data.buildID    = m_query->value(0).toInt();
        data.regionID   = m_query->value(1).toInt();
        data.cityID     = m_query->value(2).toInt();
        data.typeID     = m_query->value(3).toInt();
        data.countGov   = m_query->value(4).toInt();
        data.countComm  = m_query->value(5).toInt();
        data.countPriv  = m_query->value(6).toInt();

        qDebug() << "Notice:\t Loading building data for BUILDID: " << build_id;
    }

    return data;
}

//QStringList DBFacade::getRegions()
//{
//    // Загрузка списка регионов (районов)

//    QStringList regions;

//    QString query("SELECT `RegionName`"
//                  "FROM `Regions`"
//                  "ORDER BY `RegionID` ASC");

//    if (exec(query))
//    {
//        while (m_query->next())
//            regions << m_query->value(0).toString();
//        qDebug() << "Notice:\t Loading regions";
//    }

//    return regions;
//}

void DBFacade::addBuildToBase(int cityID, int regID, int typeID, int cGov, int cCom, int cPrv)
{
    // Добавление строения в БД (главная таблица)
    QSqlQuery query;
    query.prepare("INSERT INTO TableBuildings \n"
                    "(Region, CityOrCommID, BuildTypeID, CountGov, CountComm, CountPrivate)\n"
                  "VALUES (:reg, :city, :type, :cgov, :ccom, :cprv)");
    if (regID != 0)
        query.bindValue(":reg", regID);
    query.bindValue(":city",    cityID);
    query.bindValue(":type",    typeID);
    query.bindValue(":cgov",    cGov);
    query.bindValue(":ccom",    cCom);
    query.bindValue(":cprv",    cPrv);

    if (!query.exec())
    {
        qDebug() << "Error:\t INSERT Query is failed: " << query.lastError().text();
        return;
    }
    qDebug() << "Notice:\t Building is added to DB";
    refreshMainTable();
}

void DBFacade::setBuildInBase(BuildData data)
{
    // Изменение строки в БД (главная таблица)
    QSqlQuery query;
    query.prepare("UPDATE INTO TableBuildings \n"
                  "SET   Region     = :reg,"
                  "CityOrCommID     = :city,"
                  "BuildTypeID      = :type,"
                  "CountGov         = :cgov,"
                  "CountComm        = :ccom,"
                  "CountPrivate     = :cprv"
                  "WHERE BuildID    = " + QString::number(data.buildID));
    query.bindValue(":reg",     data.regionID);
    query.bindValue(":city",    data.cityID);
    query.bindValue(":type",    data.typeID);
    query.bindValue(":cgov",    data.countGov);
    query.bindValue(":ccom",    data.countComm);
    query.bindValue(":cprv",    data.countPriv);

    if (!query.exec())
    {
        qDebug() << "Error:\t UPDATE query is failed: " << query.lastError().text();
        return;
    }
    qDebug() << "Notice:\t Building is edited";
    refreshMainTable();
}

DBFacade::~DBFacade()
{
    deleteMainTableView();
    this->closeConnection();
    delete m_query;
    delete pDB;
}

bool DBFacade::exec(const QString &query)
{
    m_query->clear();
    if (!m_query->exec(query))
    {
        /// TODO: Обработать ошибки запроса
        qDebug() << "Error:\t Query failed: " << m_query->lastError().text();
        return false;
    }
    return true;
}

void DBFacade::createMainTableView()
{
    /// TODO: Определение таблицы
    QString qy ("CREATE VIEW maintableview \n"
                "AS SELECT CitiesAndCommunities.CityOrCommName as `Міста/райони`,\n "
                "BuildingTypes.TypeName as `Тип ЗС`, "
                "TableBuildings.CountGov as `Держ`, "
                "TableBuildings.CountComm as `Комун`, "
                "TableBuildings.CountPrivate as `Прив`\n "
                "FROM TableBuildings \n"
                    "LEFT JOIN Regions ON TableBuildings.Region = Regions.RegionID \n "
                    "LEFT JOIN CitiesAndCommunities ON TableBuildings.CityOrCommID = CitiesAndCommunities.CityID \n "
                    "LEFT JOIN BuildingTypes ON TableBuildings.BuildTypeID = BuildingTypes.TypeID \n "
                "ORDER BY TableBuildings.Region ASC, CitiesAndCommunities.IsCity DESC, TableBuildings.CityOrCommID ASC");

    model->setTable("maintableview");
    model->select();

}


void DBFacade::refreshMainTable()
{
    // TODO
    model->select();
}

void DBFacade::deleteMainTableView()
{
    model->clear();
    model->select();
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

    qDebug() << "Notice:\t Facade working in thread " << this->thread();

    createMainTableView();
}

void DBFacade::closeConnection()
{
    if (pDB->isOpen())
    {
        pDB->close();
        qDebug() << "Notice:\t Closing connection with " << pDB->hostName();
    }
}

