#ifndef PAGE5_H
#define PAGE5_H

#include <QMainWindow>
#include <QList>

namespace Ui {
class page5;
}

class page5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit page5(QWidget *parent = nullptr);
    ~page5();

private:
    Ui::page5 *ui;

    void processDisplayImage();
};

#endif // PAGE5_H
