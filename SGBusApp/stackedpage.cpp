#include "stackedpage.h"
#include "ui_stackedpage.h"
#include "customitemmodel.h"

StackedPage::StackedPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StackedPage)
{
    ui->setupUi(this);

    ui->stacked->addWidget(page2);
    ui->stacked->addWidget(mainWindow);
    ui->stacked->addWidget(page4);
    ui->stacked->addWidget(page_5);

    // ui->stacked->setCurrentIndex(0);
    // Display mainWindow by default
    ui->stacked->setCurrentWidget(page2);

    connect(ui->btn1, &QPushButton::clicked, this, &StackedPage::onBtn1Clicked);
    connect(ui->btn2, &QPushButton::clicked, this, &StackedPage::onBtn2Clicked);
    connect(ui->btn3, &QPushButton::clicked, this, &StackedPage::onBtn3Clicked);
    connect(ui->btn4, &QPushButton::clicked, this, &StackedPage::onBtn4Clicked);

    // CustomItemModel *model = new CustomItemModel;
    connect(page2, &Page2::testing123, page4->model, &CustomItemModel::test123);
    connect(page2, &Page2::testing123, page4, &Page4::onBtnClicked);

    connect(page4->model, &CustomItemModel::queried, page4, &Page4::querychanged);
    connect(page4, &Page4::onListViewItemClicked, page_5, &page5::getListViewClicked);
}

StackedPage::~StackedPage()
{
    delete ui;
}

void StackedPage::onBtn1Clicked(){
    ui->stacked->setCurrentWidget(page2);
}

void StackedPage::onBtn2Clicked(){
    ui->stacked->setCurrentWidget(page4);
}

void StackedPage::onBtn3Clicked(){
    ui->stacked->setCurrentWidget(page_5);
}

void StackedPage::onBtn4Clicked(){
    ui->stacked->setCurrentWidget(mainWindow);
}
