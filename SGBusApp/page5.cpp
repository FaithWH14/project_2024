#include "page5.h"
#include "ui_page5.h"

page5::page5(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page5)
{
    ui->setupUi(this);

    processDisplayImage();

    connect(ui->leftArrow, &QPushButton::clicked, this, &page5::onPrevBtnClick);
    connect(ui->rightArrow, &QPushButton::clicked, this, &page5::onNextBtnClick);
}

page5::~page5()
{
    delete ui;
}

void page5::processDisplayImage(){
    QString num;

    QString fullName = QString("%1 - %2_%3.png").arg(busStopCode).arg(busStationName).replace(" ", "_");
    QList<QString> images;
    QString root_path = "C:\\Users\\faithwh14\\Desktop\\QT projects\\27_practice\\bus_img";

    for (int i=0; i<3; i++){
        num = QString::number(i+1);
        QString image = fullName.arg(num);
        qDebug() << "image name is: " << image;
        images.append(root_path + "\\" + image);
    }

    int target_width = ui->img1->width();
    int target_height = ui->img1->height();
    qDebug() << "target width and height is: " << target_width << target_height;

    QPixmap img1(images[0]);
    QPixmap img2(images[1]);
    QPixmap img3(images[2]);

    ui->img1->setPixmap(img1.scaled(target_width, target_height, Qt::KeepAspectRatio));
    ui->img2->setPixmap(img2.scaled(target_width, target_height, Qt::KeepAspectRatio));
    ui->img3->setPixmap(img3.scaled(target_width, target_height, Qt::KeepAspectRatio));
}

void page5::searchIndex() {
    for (int i=0; i<busStop.size(); ++i) {
        const auto& tuple = busStop[i];

        qDebug() << "attention searchindex: " << std::get<0>(tuple) <<  std::get<1>(tuple);
        if (std::get<0>(tuple) == busStopCode && std::get<1>(tuple) == busStationName) {
            currentImgIndex = i;
            break;
        }
    }
    if (currentImgIndex == -1) {
        qDebug() << "not found";
    } else {
        qDebug() << "found" << currentImgIndex;
    }
}
