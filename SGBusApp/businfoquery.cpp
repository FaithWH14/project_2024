#include "businfoquery.h"

BusInfoQuery::BusInfoQuery() {
    db.setDatabaseName("C:\\Users\\faithwh14\\Desktop\\QT projects\\27_practice\\bus_info.db");

    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
        return;
    }
}

BusInfoQuery::~BusInfoQuery(){
    db.close();
};

void BusInfoQuery::getAllBusInfo() {
    QSqlQuery query;

    query.prepare("SELECT * FROM bus_info WHERE BusRoute = 80");
    if (!query.exec()){
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
    // bus_route, firstOrSecond, busStopCode, busStationName, distance
    qDebug() << "ID || bus_route || firstOrSecond || busStopCode || busStationName || distance";
    while (query.next()) {
        id = query.value(0).toString();
        busRoute = query.value(1).toString();
        firstOrSecond = query.value(2).toString();
        busStopCode = query.value(3).toString();
        busStationName = query.value(4).toString();
        distance = query.value(5).toString();

        qDebug() << id << "||" << busRoute << "||" << firstOrSecond << "||" << busStopCode << "||" << busStationName << "||" << distance;
    }
}

QString BusInfoQuery::getBusStationName(QString busStopCode){
    QSqlQuery query;
    query.prepare("SELECT DISTINCT(busStationName) FROM bus_info WHERE busStopCode = :busStopCode");
    query.bindValue(":busStopCode", "67191");

    if (!query.exec()){
        qDebug() << "Error executing query:" << query.lastError().text();
        return "N/A";
    }

    QString ans;
    while (query.next()) {
        ans = query.value(0).toString();
    }
    // query.next();
    return ans;
}

void BusInfoQuery::executeQuery(const QString &queryString, const std::function<void(QSqlQuery&)>& callback) {
    QSqlQuery query;

    query.prepare(queryString);
    // for (int i=0; i<parameters.size(); ++i) {
    //     query.addBindValue(parameters.at(i));
    // }

    if (!query.exec()) {
        qDebug() << "something is wrong: " << query.lastError().text();
        return;
    }

    // while (query.next()) {
    //     qDebug() << "bus station is: " << query.value(0).toString();
    // }
    callback(query);
}
