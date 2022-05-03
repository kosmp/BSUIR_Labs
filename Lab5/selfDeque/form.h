#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "deque.h"
#include "QMessageBox"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

public slots:
    void slot();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    deque<int> a;
};

#endif // FORM_H
