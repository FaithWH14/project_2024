#include "page3.h"
#include "ui_page3.h"

#include <QListView>
#include <QStringListModel>
#include <QStyledItemDelegate>

Page3::Page3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Page3)
{
    ui->setupUi(this);

    QStringListModel model;
    QStringList data;
    data << "Item 1"
         << "Item 2"
         << "Item 3";
    model.setStringList(data);

    ui->listView->setModel(&model);
}

Page3::~Page3()
{
    delete ui;
}
