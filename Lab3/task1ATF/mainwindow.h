#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <doublelist.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTableWidget>
#include <QFileDialog>
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
    DoubleList* listOfConv = new DoubleList();
    void loadFromFile();
    void deleteFromFile();
    void saveToFileAndAdd(QString& line);
    void fileReset();
    bool test(QString& line, bool mode);
    void divideAndAdd(QString& line);
    bool checkDate(QString& line, bool mode = false);
    void textOutput();
    bool IsLeap();
    void calculateMonths();
    void quicksort(DoubleList*& list, int left, int right);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_add_Button_clicked();

    void on_deleteElem_Button_clicked();

    void on_deleteConvWithTel_Button_clicked();

    void on_searchCity_Button_clicked();

    void on_searchTel_Button_clicked();

    void on_change_Button_clicked();

    void on_comboBox_5_currentTextChanged(const QString &currText);

    void on_comboBox_currentTextChanged(const QString &currText);

private:
    Ui::MainWindow *ui;
    QString filename;
    int day;
    int month;
    int year;
    bool checkFile = false;
    int months[13];
    QString currTextParam;
};
#endif // MAINWINDOW_H
