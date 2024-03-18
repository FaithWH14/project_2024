#ifndef PAGE1_H
#define PAGE1_H

#include <QMainWindow>


namespace Ui {
class Page1;
}

class Page1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Page1(QWidget *parent = nullptr);
    ~Page1();

private:
    Ui::Page1 *ui;

    void applyStyleFromFile(const QString& filename);
};

#endif // PAGE1_H
