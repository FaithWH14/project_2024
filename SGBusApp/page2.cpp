#include "page2.h"
#include "ui_page2.h"

#include <QDateTime>
#include <QList>

Page2::Page2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Page2)
{
    ui->setupUi(this);

    // TESTING ONE TWO THREE
    bus_query.getAllBusInfo();
    ui->busInfo->setText(ui->busServiceCombo->currentText());
    ui->busStopInfo->setText(ui->busStopCombo->currentText());

    ui->firstRadio->setChecked(true);
    if (ui->firstRadio->isChecked())
        radioState = "1";
    else
        radioState = "2";

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    QString busRouteQuery = "SELECT DISTINCT(busroute) FROM bus_info";
    // QString busRouteQuery = "SELECT DISTINCT busroute FROM bus_info WHERE busstopcode = 'sengkang int'";
    QString busStationQuery = "SELECT DISTINCT(busStationName) FROM bus_info";

    bus_query.executeQuery(busRouteQuery, [this](QSqlQuery& query) {
        while (query.next()) {
            initialBusServices.append(query.value(0).toString());
        }
    });

    bus_query.executeQuery(busStationQuery, [this](QSqlQuery& query){
        while (query.next()) {
            initialBusStationNames.append(query.value(0).toString());
        }
    });

    // initiate comboitems
    onResetBtnClicked();
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    connect(ui->requestBtn, &QPushButton::clicked, this, &Page2::onRequestBtnClicked);

    connect(ui->resetBtn, &QPushButton::clicked, this, &Page2::onResetBtnClicked);
    connect(ui->busServiceCombo, &QComboBox::activated, this, &Page2::onBusServiceComboCollapsed);
    connect(ui->busStopCombo, &QComboBox::activated, this, &Page2::onBusStopComboCollapsed);
    connect(ui->firstRadio, &QRadioButton::clicked, this, &Page2::onFirstRadioClicked);
    connect(ui->secondRadio, &QRadioButton::clicked, this, &Page2::onSecondRadioClicked);
    connect(ui->busLe1, &QLineEdit::editingFinished, this, &Page2::onBusServiceEditFinished);
    connect(ui->busLe2, &QLineEdit::editingFinished, this, &Page2::onBusStopEditFinished);
}

Page2::~Page2()
{
    delete ui;
}

void Page2::onRequestBtnClicked() {
    BusETA busEta;
    std::string busServiceNo = ui->busServiceCombo->currentText().toStdString();
    qDebug() << "what is this busserviceno" << busServiceNo;
    std::string busStopCode;
    QString haha;

    // QString onRequestQuery = "SELECT busstopcode FROM bus_api WHERE busstationname = ?";
    // QList<QVariant> parameter1 = {"sengkang int"};
    QString target = ui->busStopCombo->currentText();
    QString onRequestQuery = QString("SELECT DISTINCT busstopcode FROM bus_info WHERE busstationname = '%1'").arg(target);
    qDebug() << "is here run?" << onRequestQuery << "and what is target: " << target;

    bus_query.executeQuery(onRequestQuery, [&haha, &busStopCode](QSqlQuery &query){
        while (query.next()) {
            haha = query.value(0).toString();
            qDebug() << "what is busStopCode!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << haha;
            busStopCode = haha.toStdString();
        }
    });

    // busEta.getData();
    busEta.getData(busServiceNo, busStopCode);

    // QString result = QString::fromUtf8(busEta.result);
    QString etaNextBus = QString::fromUtf8(busEta.etaNextBus);
    QString etaNextBus2 = QString::fromUtf8(busEta.etaNextBus2);
    QString etaNextBus3 = QString::fromUtf8(busEta.etaNextBus3);

    QString timeLeft;
    QString timeLeft2;
    QString timeLeft3;

    convertTime(etaNextBus, timeLeft);
    convertTime(etaNextBus2, timeLeft2);
    convertTime(etaNextBus3, timeLeft3);

    currentBus = ui->busServiceCombo->currentText();  // attention
    currentFirstOrSecond = radioState;

    ui->busInfo->setText(currentBus);
    ui->busStopInfo->setText(ui->busStopCombo->currentText());
    ui->firstOrSecond->setText(currentFirstOrSecond);

    ui->eta1->setText(etaNextBus);
    ui->eta2->setText(etaNextBus2);
    ui->eta3->setText(etaNextBus3);

    ui->timeLeft1->setText(timeLeft);
    ui->timeLeft2->setText(timeLeft2);
    ui->timeLeft3->setText(timeLeft3);

    emit testing123(ui->busServiceCombo->currentText(), radioState);

    QList<std::tuple<QString, QString>> busStopList;
    QString onImageRequestQuery = QString("SELECT busstopcode, busstationname FROM bus_info WHERE busroute = '%1'").arg(currentBus);
    bus_query.executeQuery(onImageRequestQuery, [&busStopList](QSqlQuery &query){
        while (query.next()){
            qDebug() << "imageClicked" << query.value(0).toString() << query.value(1).toString();
            busStopList.append(std::make_tuple(query.value(0).toString(), query.value(1).toString()));
        }
    });

    emit ImageClicked(currentBus, ui->busStopCombo->currentText(), QString::fromStdString(busStopCode), busStopList);
}

void Page2::convertTime(QString &dateTime, QString &timeDiff){

    dateTime = dateTime.replace("\"", "");

    if (dateTime == "") {
        dateTime = "N/A";
        timeDiff = "N/A";
        return;
    }
    QString format = "yyyy-MM-ddTHH:mm:ss";

    // left(19) is to filter out the +08:00, which qdatetime not understand
    QDateTime timeDateTime = QDateTime::fromString(dateTime.left(19), format);
    QDateTime currentDateTime = QDateTime::currentDateTime();

    int secondsDifference = currentDateTime.secsTo(timeDateTime);
    int minutesDifference = secondsDifference / 60;

    dateTime = timeDateTime.toString("HH:mm");
    timeDiff = QString::number(minutesDifference);
}

void Page2::onBusServiceComboCollapsed(){
    QString currentText = ui->busServiceCombo->currentText();
    QString currentbusStopText = ui->busStopCombo->currentText();
    QString queryText = QString("SELECT DISTINCT busstationname FROM bus_info WHERE busroute = '%1' AND firstorsecond = %2").arg(currentText).arg(radioState);

    ui->busStopCombo->clear();
    bus_query.executeQuery(queryText, [this, &currentbusStopText](QSqlQuery &query){
        while (query.next()) {
            QString currentT = query.value(0).toString();
            if (currentT == currentbusStopText)
                ui->busStopCombo->insertItem(0, currentT);
            else
                ui->busStopCombo->addItem(currentT);
        }
        ui->busStopCombo->setCurrentIndex(0);
    });
}

void Page2::onBusStopComboCollapsed(){
    QString currentText = ui->busStopCombo->currentText();
    QString currentbusServiceText = ui->busServiceCombo->currentText();
    QString queryText = QString("SELECT DISTINCT busroute FROM bus_info WHERE busstationname = '%1' AND firstorsecond = %2").arg(currentText).arg(radioState);

    ui->busServiceCombo->clear();
    bus_query.executeQuery(queryText, [this, &currentbusServiceText](QSqlQuery &query){
        while (query.next()) {
            QString currentT = query.value(0).toString();
            if (currentT == currentbusServiceText)
                ui->busServiceCombo->insertItem(0, currentT);
            else
                ui->busServiceCombo->addItem(currentT);
        }
        ui->busServiceCombo->setCurrentIndex(0);
    });
}

void Page2::onResetBtnClicked(){
    ui->busServiceCombo->clear();
    ui->busStopCombo->clear();

    ui->busServiceCombo->addItem(". . .");
    std::sort(initialBusServices.begin(), initialBusServices.end());
    std::sort(initialBusStationNames.begin(), initialBusStationNames.end());

    ui->busServiceCombo->addItems(initialBusServices);
    ui->busStopCombo->addItem(". . .");
    ui->busStopCombo->addItems(initialBusStationNames);
}

void Page2::onFirstRadioClicked() {
    radioState = "1";
    onBusServiceComboCollapsed();
}

void Page2::onSecondRadioClicked() {
    radioState = "2";
    onBusServiceComboCollapsed();
}

void Page2::onBusServiceEditFinished(){
    ui->busServiceCombo->clear();
    QString leText = ui->busLe1->text();

    if (!initialBusServices.contains(leText)) {
        ui->busServiceCombo->addItem(". . .");
        ui->busServiceCombo->addItems(initialBusServices);
    } else {
        ui->busServiceCombo->insertItem(0, leText);
        ui->busServiceCombo->addItems(initialBusServices);
        onBusServiceComboCollapsed();
    }
}

void Page2::onBusStopEditFinished(){
    ui->busStopCombo->clear();
    QString leText = ui->busLe2->text();

    if (!initialBusServices.contains(leText)) {
        ui->busStopCombo->addItem(". . .");
        ui->busStopCombo->addItems(initialBusStationNames);
    } else {
        ui->busStopCombo->insertItem(0, leText);
        ui->busStopCombo->addItems(initialBusStationNames);
        onBusStopComboCollapsed();
    }
}

