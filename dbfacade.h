#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QTableView>
#include <QSqlQuery>
#include <QVariant>
#include <QTimer>

#include "mtablemodel.h"

struct CityData
{   // структура для хранения города/района и флага (есть ли у района громады),
    // также ИД города для запросов
    QString name;
    int     region;   // 0 - нету региона (город)
    int     cityID;
};

struct BuildData
{
    // Структура для хранения всего поля таблицы TableBuildings
    int     buildID;
    int     regionID;   // 0 - нету региона
    int     cityID;
    int     typeID;     // тип строения (0 - нету типа(громада))
    int     countGov;
    int     countComm;
    int     countPriv;
};

class DBFacade : public QObject
{
    Q_OBJECT
public:
    explicit    DBFacade(QObject *parent = 0);
    void        setMainTable(QTableView *tbl);
    QList<CityData> getCityList();
    QStringList     getGromList(const int &regID);
    QStringList     getBuildTypesList();
    QList<int>      getBuildingIDs();
    BuildData       getBuildData(int build_id);
//    QStringList     getRegions();

    void    addBuildToBase(int cityID,  int regID,
                               int typeID,  int cGov,
                               int cCom,    int cPrv);
    void    setBuildInBase(BuildData data);

    ~DBFacade();

private:
    QSqlDatabase    *pDB;
    MTableModel     *model;

    QSqlQuery       *m_query;

    QTimer  tmr;    // Проверяет соединение

    bool    exec(const QString &query);

    void    createMainTableView();
    void    refreshMainTable();
    void    deleteMainTableView();

signals:
    void connectionSuccessed();
    void losingConnection(QString why);
    void sendError(QString what);


public slots:
    void createConnection(const QString &server,
                          const QString &dbname,
                          const QString &username,
                          const QString &password);
    void closeConnection();
};

#endif // DBFACADE_H
