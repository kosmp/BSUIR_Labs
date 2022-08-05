#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <date.h>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QString>
#include <QGraphicsScene>
#include <QTableWidget>
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
    Date* dates;
            //new Date[20];
    QGraphicsScene* scene; 

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
protected:
    int i = 0;
    Date birthDayDate;
    bool birthDayCheck = false;
    void fileInit();
    void fileAddDate();
    void table();
    void changeData();
    QString directory1 = "D:/qt projects/z3/dates.txt";
    QString currentComboBox;
    int currentToChange;
};
#endif // MAINWINDOW_H
