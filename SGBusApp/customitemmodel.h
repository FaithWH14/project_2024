// customitemmodel.h
#ifndef CUSTOMITEMMODEL_H
#define CUSTOMITEMMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "businfoquery.h"

class CustomItemModel: public QAbstractListModel {
    Q_OBJECT;

public:
    CustomItemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void queryService();

    QString busRoute = "80";
    QString firstOrSecond = "1";
    // QString busRoute;
    // QString firstOrSecond;
    struct Item{
        QString busSequence;
        QString busServiceNo;
        QString busStopName;
        QString busStopCode;
        QString busDistance;
    };
    QList<Item> busInfo_list;

public slots:
    void test123(QString busRoute1, QString firstOrSecond1) {
        busRoute = busRoute1;
        firstOrSecond = firstOrSecond1;
        qDebug() << "is test123 run?: " << busRoute << firstOrSecond;

        beginResetModel();
        queryService();
        endResetModel();

        emit queried();
    };

signals:
    void queried();

private:

    BusInfoQuery busQuery;
};

#endif //CUSTOMITEMMODEL_H
