#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashtable.h"
#include <QMessageBox>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void print();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    HashTable a;
};
#endif // MAINWINDOW_H
