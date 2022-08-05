#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bitset.h>
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
    Bitset<64> bs = Bitset<64>("1000001100101000111000000010101000000100000000001001000000000101");

private slots:
    void on_allButton_clicked();

    void on_anyButton_clicked();

    void on_countButton_clicked();

    void on_flipAllButton_clicked();

    void on_noneButton_clicked();

    void on_resetAllButton_clicked();

    void on_setAllButton_clicked();

    void on_sizeButton_clicked();

    void on_testButton_clicked();

    void on_toStringButton_clicked();

    void on_toUllongButton_clicked();

    void on_toUlongButton_clicked();

    void on_resetOneButton_clicked();

    void on_setOneButton_clicked();

    void on_flipOneButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
