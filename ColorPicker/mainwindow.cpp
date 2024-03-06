#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setWindowTitle(" ");

    jsonData = loadJson.jsonData;
    listKeys = loadJson.listKeys;

    // initiate the combobox item
    ui->comboBox->addItem("");
    for (std::string key:listKeys){
        ui->comboBox->addItem(QString::fromStdString(key));
    }
    ui->colorCode->setText("");

    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchBtnClicked);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &MainWindow::onSearchBtnClicked);
    connect(ui->comboBox, &QComboBox::activated, this, &MainWindow::onComboBoxCollapsed);
    connect(ui->clipBoardBtn, &QPushButton::clicked, this, &MainWindow::copyToClipboard);
    connect(ui->clipBoardBtn, &QPushButton::clicked, this, &MainWindow::copyToClipboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onComboBoxCollapsed(){
    std::string comboBoxText = ui->comboBox->currentText().toStdString();
    QString colorCode = QString::fromStdString(jsonData[comboBoxText]);
    ui->colorCode->setText(colorCode);
    QString backgroundColor = "background-color:" + colorCode;
    ui->displayFrame->setStyleSheet(backgroundColor);
}

void MainWindow::onSearchBtnClicked() {
    QString leText = ui->lineEdit->text();
    std::vector<std::string> relevantList = loadJson.searchRelevant(leText.toStdString());

    // Clear comboBoxItem everytime
    ui->comboBox->clear();

    if (relevantList.empty()){
        qDebug() << "There is no related words found, please check!";
        return;
    }

    for (std::string it:relevantList){
        ui->comboBox->addItem(QString::fromStdString(it));
        qDebug() << "attention 123" << it;
    }

    std::string comboBoxText = ui->comboBox->currentText().toStdString();
    QString colorCode = QString::fromStdString(jsonData[comboBoxText]);
    ui->colorCode->setText(colorCode);
    QString backgroundColor = "background-color:" + colorCode;
    ui->displayFrame->setStyleSheet(backgroundColor);
}

void MainWindow::copyToClipboard(){
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->colorCode->text());
}
