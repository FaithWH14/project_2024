#ifndef PAGE5_H
#define PAGE5_H

#include <QMainWindow>
#include <QList>

#include <QPushButton>

namespace Ui {
class page5;
}

class page5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit page5(QWidget *parent = nullptr);
    ~page5();

public slots:
    void getListViewClicked(QString busStationName1, QString busStopCode1, QList<std::tuple<QString, QString>> busStop1){
        busStationName = busStationName1;
        busStopCode = busStopCode1;
        processDisplayImage();

        busStop = busStop1;
        searchIndex();
        qDebug() << "currentindex getlistview: " << currentImgIndex;
    };

private slots:
    void onPrevBtnClick() {
        int prevIndex = currentImgIndex - 1;
        qDebug() << "currentIndex is: " << currentImgIndex << prevIndex;

        if (prevIndex >= 0 && prevIndex < busStop.size()){
            const auto& tuple = busStop[prevIndex];

            busStopCode = std::get<0>(tuple);
            busStationName = std::get<1>(tuple);

            qDebug() << "busStopCode12345" << busStopCode << busStationName;

            currentImgIndex = prevIndex;
            processDisplayImage();
        } else {
            qDebug() << "the index is out of scope";
        }
    };
    void onNextBtnClick() {
        int nextIndex = currentImgIndex + 1;
        qDebug() << "currentIndex is: " << currentImgIndex << nextIndex;

        if (nextIndex >= 0 && nextIndex < busStop.size()){
            const auto& tuple = busStop[nextIndex];

            busStopCode = std::get<0>(tuple);
            busStationName = std::get<1>(tuple);
            // qDebug() << "checking: " << busStopCode << busStationName;

            currentImgIndex = nextIndex;
            processDisplayImage();
        } else {
            qDebug() << "the index is out of scope";
        }
    };

private:
    Ui::page5 *ui;

    void processDisplayImage();
    QString busStopCode;
    QString busStationName;

    QList<std::tuple<QString, QString>> busStop;
    int currentImgIndex = -1;

    void searchIndex();
};

#endif // PAGE5_H
