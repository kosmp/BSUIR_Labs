#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <regex>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void parseVar(QString text);
    void classStructArray(QString text);
    void funcPrototypes(QString text);
    void changeCoordVarOrArray(QString text);
    void countLocVarsAndCoords(QString text);
    void countOverloadedFuncAndCoords(QString text);
    void branchingDepth(QString text);
    void logicErrors(QString text);

private slots:
    void on_button_checkInFile_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString text;
};
#endif // MAINWINDOW_H

