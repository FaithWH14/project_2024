#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QTextEdit>

#include <QMainWindow>

#include "businfo.h"

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

    QLabel *title;
    QTextEdit *display;

private slots:
    void onGetDateClicked();
    void onGetBusInfoClicked();
    void onGetTabClicked();

private:
    Ui::MainWindow *ui;
    // BusInfo busInfo;
};
#endif // MAINWINDOW_H
