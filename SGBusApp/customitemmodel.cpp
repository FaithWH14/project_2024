// customitemmodel.cpp
#include "customitemmodel.h"

#include <QtSql>

CustomItemModel::CustomItemModel(QObject *parent): QAbstractListModel(parent){

    // queryService();
    qDebug("is model constructor run?");
    // if (busRoute.isEmpty() or firstOrSecond.isEmpty())
    //     return;
    queryService();
}

int CustomItemModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    // qDebug() << "is rowCount run?";
    // return busInfo_list.count();

    return busInfo_list.count();
}

QVariant CustomItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const Item &item = busInfo_list[index.row()];

    if (role == Qt::DisplayRole) {
        return item.busSequence;
    } else if (role == Qt::UserRole) {
        return item.busServiceNo;
    } else if (role == Qt::UserRole + 1) {
        return item.busStopName;
    } else if (role == Qt::UserRole + 2) {
        return item.busStopCode;
    } else if (role == Qt::UserRole + 3) {
        return item.busDistance;
    }

    return QVariant();
}

void CustomItemModel::queryService() {
    busInfo_list.clear();  // attention

    QString queryString = QString("SELECT busstopcode, busstationname, distance FROM bus_info WHERE busroute = %1 AND firstorsecond = %2").arg(busRoute).arg(firstOrSecond);

    busQuery.executeQuery(queryString, [this](QSqlQuery& query){
        int busSequence = 0;
        while (query.next()) {
            QString busStopCode1 = query.value(0).toString();
            QString busStopName1 = query.value(1).toString();
            QString distance1 = query.value(2).toString();
            busSequence += 1;

            qDebug() << "querry service click" << busStopName1 << distance1;
            busInfo_list.append(Item{QString::number(busSequence), busRoute, busStopCode1, busStopName1, distance1});
            // busInfo_list.append(Item{});
        }
    });

    // how to call rowcount here?
    return;
}
