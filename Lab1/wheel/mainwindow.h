#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <ctime>
#include "wheel.h"
#include "circle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Wheel *wheel;
    QTimer *timer;
    bool flag = true;
    int time;
private slots:
    void timerSlot();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
