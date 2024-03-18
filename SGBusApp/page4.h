#ifndef PAGE4_H
#define PAGE4_H

#include <QMainWindow>

#include "customitemdelegate.h"
#include "customitemmodel.h"

#include <QListView>

namespace Ui {
class Page4;
}

class Page4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Page4(QWidget *parent = nullptr);
    ~Page4();

    QString busRoute;
    QString firstOrSecond;

    CustomItemModel *model;

    QString indexBusRoute;
    QString indexFirstOrSecond;
    QString indexBusStationName;
    QString indexBusStopCode;
    QString indexDistance;

public slots:
    void onBtnClicked(const QString &busRoute1, const QString &firstOrSecond1);
    void querychanged();
    void handleItemClicked(const QModelIndex &index);

private:
    Ui::Page4 *ui;
    CustomItemDelegate *delegate;
    // CustomItemModel *model;
};

#endif // PAGE4_H
