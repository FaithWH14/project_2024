#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QTextEdit>

#include <QMainWindow>
#include <QComboBox>
#include <QRadioButton>

#include "businfo.h"
#include "businfoquery.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBusRouteSelected();
    void onBusStop1Selected();
    void onBusStop2Selected();

    // void onRadio1Clicked();
    // void onRadio2Clicked();

private:
    Ui::MainWindow *ui;

    QList<QString> busRouteList;
    QList<QString> busStop1List;
    QList<QString> busDistanceList;
    QList<QString> busStop2List;

    QString selectedBusRoute;
    QString radioState;

    BusInfoQuery busQuery;
};
#endif // MAINWINDOW_H
