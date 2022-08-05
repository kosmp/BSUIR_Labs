#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map.h>
#include <string>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    map<int, std::string> m;

private slots:
    void on_showButton_clicked();

    void on_countButton_clicked();

    void on_insertButton_clicked();

    void on_removeButton_clicked();

    void on_findButton_clicked();

    void on_atButton_clicked();

private:
    Ui::MainWindow *ui;
    size_t countOfElemInMap = 0;
};
#endif // MAINWINDOW_H
