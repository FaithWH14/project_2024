#include "page5.h"
#include "ui_page5.h"

page5::page5(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page5)
{
    ui->setupUi(this);

    processDisplayImage();
}

page5::~page5()
{
    delete ui;
}

void page5::processDisplayImage(){
    QString busStopCode = "67009";
    QString busStationName = "sengkang int";
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
