#include "page1.h"
#include "ui_page1.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

Page1::Page1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Page1)
{
    ui->setupUi(this);

    this->setStyleSheet("C:\\Users\\faithwh14\\Desktop\\QT projects\\27_practice\\style.json");
}

Page1::~Page1()
{
    delete ui;
}

void Page1::applyStyleFromFile(const QString& filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "Failed to open style file");
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isObject()) {
        QMessageBox::critical(this, "Error", "Invalid JSON format");
        return;
    }

    QJsonObject rootObject = doc.object();
    const QStringList widgetNames = rootObject.keys();

    // Apply styles to widgets
    for (const QString &widgetName : widgetNames) {
        QJsonObject styles = rootObject.value(widgetName).toObject();

        // Find widgets by object name in the current UI
        QList<QWidget*> foundWidgets = findChildren<QWidget*>(widgetName);

        for (QWidget *widget : foundWidgets) {
            QString styleSheet;
            for (auto it = styles.constBegin(); it != styles.constEnd(); ++it) {
                styleSheet += QString("%1: %2;").arg(it.key(), it.value().toString());
            }
            widget->setStyleSheet(styleSheet);
            // ui->card1->setStyleSheet(styleSheet);
        }

        // Alternatively, if you're using ui pointer to access widgets:
        // ui->widgetName->setStyleSheet(styleSheet);
    }
}
