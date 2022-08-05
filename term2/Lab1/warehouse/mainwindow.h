#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <storageunit.h>
#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* scene;
    void loadFromFile();
    void saveToFile();
    void deleteFromFile(int problems[], int g);
    void deleteFromFile(int problem, bool check = false);
    void changeData();
    void showThings();
    void searchName();
    void searchModel();
    void sortByName();
    void sortByCode();
    void sortByCost();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_currentIndexChanged(int index1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;
    StorageUnit* things = nullptr;
    QString* thingsLines = nullptr;
    int i = 0;
    void textOutput();
    bool test(QString& line);
    QString currentComboBox;
    int currentToChange;
    void pushInArray(QString line, int index);
    QString filename;
};
#endif // MAINWINDOW_H
