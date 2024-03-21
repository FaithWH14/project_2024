#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->radio1->setChecked(true);
    radioState = "1";

    QString queryString = "SELECT DISTINCT busroute FROM bus_info";
    busQuery.executeQuery(queryString, [this](QSqlQuery &query) {
        while (query.next()){
            busRouteList.append(query.value(0).toString());
        }
    });

    ui->busRouteCombo->addItems(busRouteList);
    onBusRouteSelected();

    connect(ui->busRouteCombo, &QComboBox::activated, this, &MainWindow::onBusRouteSelected);
    connect(ui->busStop1Combo, &QComboBox::activated, this, &MainWindow::onBusStop1Selected);
    connect(ui->busStop2Combo, &QComboBox::activated, this, &MainWindow::onBusStop2Selected);
    connect(ui->radio1, &QRadioButton::clicked, this, &MainWindow::onBusRouteSelected);
    connect(ui->radio2, &QRadioButton::clicked, this, &MainWindow::onBusRouteSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBusRouteSelected(){
    ui->busStop1Combo->clear();
    ui->busStop2Combo->clear();
    busStop1List.clear();
    busStop2List.clear();

    selectedBusRoute = ui->busRouteCombo->currentText();

    radioState = ui->radio1->isChecked() ? "1" : "2";
    QString queryString = QString("SELECT busstationname, distance FROM bus_info WHERE busroute = '%1' AND firstorsecond = '%2'").arg(selectedBusRoute).arg(radioState);
    qDebug() << "queryString mainwindow is: " << queryString;
    busQuery.executeQuery(queryString, [this](QSqlQuery &query){
        while (query.next()){
            busStop1List.append(query.value(0).toString());
            busDistanceList.append(query.value(1).toString());
        }
    });
    ui->busStop1Combo->addItems(busStop1List);
    ui->busStop2Combo->addItem("-");

    onBusStop1Selected();
}

void MainWindow::onBusStop1Selected(){
    ui->busStop2Combo->clear();

    QString currentBusStop1 = ui->busStop1Combo->currentText();

    int index = busStop1List.indexOf(currentBusStop1);

    qDebug() << "index: " << index << busStop1List.size();
    if (index == busStop1List.size()){
        ui->busStop2Combo->addItem("-");
        return;
    }

    busStop2List = busStop1List.mid(index + 1);

    ui->busStop2Combo->addItems(busStop2List);

    onBusStop2Selected();
}

void MainWindow::onBusStop2Selected(){
    int index1 = busStop1List.indexOf(ui->busStop1Combo->currentText());
    int index2 = busStop1List.indexOf(ui->busStop2Combo->currentText());

    ui->busStopNumberT->setText(QString::number(index2 - index1) + " more stations");

    float distance1 = busDistanceList[index1].toFloat();
    float distance2 = busDistanceList[index2].toFloat();

    qDebug() << "Distance is: " << busDistanceList[index1] << busDistanceList[index2];

    ui->distanceT->setText(QString::number(distance2 - distance1) + "KM");
}
