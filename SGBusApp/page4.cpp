#include "page4.h"
#include "ui_page4.h"

#include <QListView>
#include <QStringListModel>

Page4::Page4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Page4)
{
    ui->setupUi(this);

    model = new CustomItemModel(this);
    delegate = new CustomItemDelegate(this);

    ui->listView->setModel(model);

    ui->listView->setItemDelegate(delegate);

    connect(ui->listView, &QListView::clicked, this, &Page4::handleItemClicked);
}

Page4::~Page4()
{
    delete ui;
}

void Page4::onBtnClicked(const QString &busRoute1, const QString &firstOrSecond1){
    // QString br = model->busRoute;
    // QString fs = model->firstOrSecond;
    // model->busRoute = page2->currentBus;
    // model->firstOrSecond = page2->currentFirstOrSecond;

    // qDebug() << "what is br and fs: " << busRoute << firstOrSecond;
    model->busRoute = busRoute1;
    model->firstOrSecond = firstOrSecond1;

    qDebug() << "what is busroute and firstorsecond: " << model->busRoute << model->firstOrSecond;

    ui->busValue->setText(busRoute1);
    ui->totalBusValue->setText(firstOrSecond1);
}

void Page4::querychanged() {
    // ui->listView->setModel(model);
}

void Page4::handleItemClicked(const QModelIndex &index){
    if (!index.isValid()){
        return;
    }

    indexBusRoute = index.data(Qt::UserRole).toString();
    // indexFirstOrSecond = index.data(Qt::UserRole).toString();
    indexBusStationName = index.data(Qt::UserRole+1).toString();
    indexBusStopCode = index.data(Qt::UserRole+2).toString();
    indexDistance = index.data(Qt::UserRole+3).toString();

    qDebug() << "handleItemClicked" << indexBusRoute << indexBusStationName << indexBusStopCode;
}
