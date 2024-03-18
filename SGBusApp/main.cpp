#include "mainwindow.h"
#include "page1.h"
#include "page2.h"
#include "page4.h"

#include "stackedpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // Page1 w;
    // Page2 w;
    // Page4 w;

    StackedPage w;

    w.show();
    return a.exec();
}
