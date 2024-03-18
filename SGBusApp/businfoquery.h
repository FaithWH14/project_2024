#ifndef BUSINFOQUERY_H
#define BUSINFOQUERY_H

// #include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QMap>
#include <QList>

class BusInfoQuery
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
public:
    BusInfoQuery();
    ~BusInfoQuery();

    // QSqlQuery query;

    // QString busStationName;

    void getAllBusInfo();
    QString getBusStationName(QString busStopCode);

    QString id;
    QString busRoute;
    QString firstOrSecond;
    QString busStopCode;
    QString busStationName;
    QString distance;

    struct Item{
        QString busServiceNo;
        QString busStopCode;
        QString busStopName;
        QString busDistance;
    };

    void executeQuery(const QString &queryString, const std::function<void(QSqlQuery&)>& callback);

    void runQuery() {
        QSqlQuery query1;
        // query.clear();
        qDebug() << "hahaha";
        query1.prepare("SELECT DISTINCT(busroute) FROM bus_info");
        if (!query1.exec()) {
            qDebug() << "ERROR: run query: " << query1.lastError().text();
        }

        while (query1.next()) {
            qDebug() << "attention runQuery successfully run! " << query1.value(0).toString();
        }
    }
};

#endif // BUSINFOQUERY_H
