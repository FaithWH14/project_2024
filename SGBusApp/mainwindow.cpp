#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    title = ui->title;
    display = ui->display;

    connect(ui->gdBtn, &QPushButton::clicked, this, &MainWindow::onGetDateClicked);
    connect(ui->gbBtn, &QPushButton::clicked, this, &MainWindow::onGetBusInfoClicked);

    connect(ui->hBtn, &QPushButton::clicked, this, &MainWindow::onGetTabClicked);
    connect(ui->mlBtn, &QPushButton::clicked, this, &MainWindow::onGetTabClicked);
    connect(ui->vlBtn, &QPushButton::clicked, this, &MainWindow::onGetTabClicked);
    connect(ui->pBtn, &QPushButton::clicked, this, &MainWindow::onGetTabClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGetDateClicked() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh-mm");
    display->setText(currentTime);
}

void MainWindow::onGetBusInfoClicked() {
    BusInfo busInfo;
    busInfo.getData();
    QString result = QString::fromUtf8(busInfo.result);
    display->setText(result);
}

void MainWindow::onGetTabClicked() {
    title->setText("haha");
}
