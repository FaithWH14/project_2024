#ifndef PAGE2_H
#define PAGE2_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QDateTime>

#include "buseta.h"
#include "businfoquery.h"
// #include "businfo.h"

// #include "customitemmodel.h"

namespace Ui {
class Page2;
}

class Page2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Page2(QWidget *parent = nullptr);
    ~Page2();

    BusInfoQuery bus_query;

    QString currentBus = "80";
    QString currentFirstOrSecond = "2";

signals:
    void testing123(const QString &busRoute1, const QString &firstOrSecond1);

private slots:
    void onRequestBtnClicked();
    void onResetBtnClicked();
    void onBusServiceComboCollapsed();
    void onBusStopComboCollapsed();
    void onFirstRadioClicked();
    void onSecondRadioClicked();
    void onBusServiceEditFinished();
    void onBusStopEditFinished();

private:
    Ui::Page2 *ui;
    void convertTime(QString &dateTime, QString &timeDiff);

    QString timeLeft;
    QString time;

    QList<QString> initialBusServices;
    QList<QString> initialBusStationNames;

    QString radioState;

    // CustomItemModel *model;
};

#endif // PAGE2_H
