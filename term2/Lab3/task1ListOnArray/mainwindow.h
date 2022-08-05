#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <doublelist.h>
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
    DoubleList* listOfWorkers = new DoubleList();
    bool IsLeap(int year);
    void textOutput();
    void fileReset();
    bool loadFromFile();
    void divideAndAdd(QString& line);
    bool test(QString& line, bool mode);
    bool checkDate(QString& line, bool mode = false);
    void saveToFileAndAdd(QString& line);
    void realDate();
    int duration(int daySt, int monthSt, int yearSt);
    void quicksort(DoubleList*& list, int left, int right);

private slots:
    void on_pushButton_openFile_clicked();

    void on_pushButton_showList_clicked();

    void on_add_Button_clicked();

    void on_searchSurname_Button_clicked();

    void on_searchDepartment_Button_clicked();

    void on_searchWorkExp_Button_clicked();

    void on_delete_Button_clicked();

    void on_change_Button_clicked();

    void on_comboBox_5_currentTextChanged(const QString &currText);

    void on_comboBox_2_currentTextChanged(const QString &currText);

private:
    Ui::MainWindow *ui;
    QString filename;
    int dayBuff;
    int monthBuff;
    int yearBuff;
    int realDay;
    int realMonth;
    int realYear;
    int months[13]; // buffer, not for regular using. Intermediate values in months[2]
    bool checkFile = false;
    QString currTextParam;
};
#endif // MAINWINDOW_H
