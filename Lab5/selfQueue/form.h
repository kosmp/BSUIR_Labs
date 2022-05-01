#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <ctime>
#include <QDebug>
#include <QMessageBox>
#include "queue.h"

namespace Ui {
class Form;
}

class Form : public QWidget, public queue<int>
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

public slots:
    void slot();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    int* arr;
    queue<int> a;
    queue<int> b;
};

#endif // FORM_H
