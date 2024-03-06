#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QClipboard>
#include <QMessageBox>

#include "loadjson.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
    void onSearchBtnClicked();
    void onComboBoxCollapsed();
    void copyToClipboard();

private:
    Ui::MainWindow *ui;
    LoadJson loadJson;
    std::vector<std::string> listKeys;
    json jsonData;

};
#endif // MAINWINDOW_H
