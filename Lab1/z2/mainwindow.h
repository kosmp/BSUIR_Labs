#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <hexagon.h>
#include <rectangle.h>
#include <rhombus.h>
#include <stareight.h>
#include <circle.h>
#include <QTimer>
#include <cstring>
#include <QMouseEvent>
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
    long long int time;
    static float scale;

private slots:
    void slotRotate();

    void slotMoveForward();

    void slotMoveBack();

    void slotMoveUp();

    void slotMoveDown();

    void slotScaleUp();

    void slotScaleDown();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void slotLines(const char* figures);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Figure *figure;
    QTimer *timer;
    bool flag = true;
    QPointF previousPoint;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};
#endif // MAINWINDOW_H
