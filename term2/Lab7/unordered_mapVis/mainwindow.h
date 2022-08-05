#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "unordered_map.h"
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
    unordered_map<int, std::string> um;

private slots:
    void on_loadFactorButton_clicked();

    void on_sizeButton_clicked();

    void on_EmptyButton_clicked();

    void on_clearButton_clicked();

    void on_insertButton_clicked();

    void on_eraseButton_clicked();

    void on_containsButton_clicked();

    void on_operatorButton_clicked();

private:
    Ui::MainWindow *ui;

    void print();
};
#endif // MAINWINDOW_H
