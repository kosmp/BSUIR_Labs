#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <stack.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int check_brackets(QString line);
    void showResult(int& pos, int& linesCount, QString& inputLine);

private slots:
    void on_button_checkInFile_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool check = false;
};
#endif // MAINWINDOW_H
