#ifndef STACKEDPAGE_H
#define STACKEDPAGE_H

#include <QMainWindow>

#include "page2.h"
#include "page4.h"
#include "page5.h"
#include "mainwindow.h"

namespace Ui {
class StackedPage;
}

class StackedPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit StackedPage(QWidget *parent = nullptr);
    ~StackedPage();

    QString busRoute;
    QString firstOrSecond;

private slots:
    void onBtn1Clicked();
    void onBtn2Clicked();
    void onBtn3Clicked();
    void onBtn4Clicked();

private:
    Ui::StackedPage *ui;

    Page2 *page2 = new Page2;
    Page4 *page4 = new Page4;
    page5 *page_5 = new page5;
    MainWindow *mainWindow = new MainWindow;
};

#endif // STACKEDPAGE_H
