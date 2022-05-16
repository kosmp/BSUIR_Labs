#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 350);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->textEdit->setReadOnly(true);

    ui->textEdit->setText(QString::fromStdString(bs.to_string()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_allButton_clicked()
{
    bool res = bs.all();
    if (res)
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_anyButton_clicked()
{
    bool res = bs.any();
    if (res)
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_countButton_clicked()
{
    size_t res = bs.count();
    QMessageBox::information(this, "Message", QString::number(res));
}


void MainWindow::on_flipAllButton_clicked()
{
    bs.flip();
    QMessageBox::information(this, "Message", "Fliped");
}


void MainWindow::on_noneButton_clicked()
{
    bool res = bs.none();
    if (res)
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_resetAllButton_clicked()
{
    bs.reset();
    QMessageBox::information(this, "Message", "Reseted ");
}


void MainWindow::on_setAllButton_clicked()
{
    bs.set();
    QMessageBox::information(this, "Message", "Setted");
}


void MainWindow::on_sizeButton_clicked()
{
    size_t res = bs.size();
    QMessageBox::information(this, "Message", "size: " + QString::number(res));
}


void MainWindow::on_testButton_clicked()
{
    size_t line = ui->lineEditTest->text().toInt();
    if (ui->lineEditTest->text().size() == 0 || line >= 64)
    {
        QMessageBox::information(this, "Message", "You need to insert in line a position to check. Must be < size.");
        return;
    }

    bool res = bs.test(line);
    if (res)
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_toStringButton_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setText(QString::fromStdString(bs.to_string()));
    QMessageBox::information(this, "Message", "Done");
}


void MainWindow::on_toUllongButton_clicked()
{
    unsigned long long res = bs.to_ullong();
    QMessageBox::information(this, "Message", "64 bit: " + QString::number(res));
}


void MainWindow::on_toUlongButton_clicked()
{
    unsigned long res = bs.to_ullong();
    QMessageBox::information(this, "Message", "32 bit: " + QString::number(res));
}


void MainWindow::on_resetOneButton_clicked()
{
    size_t line = ui->lineEditReset->text().toInt();
    if (ui->lineEditReset->text().size() == 0 || line >= 64)
    {
        QMessageBox::information(this, "Message", "You need to insert in line a position to reset. Must be < size.");
        return;
    }

    bs.reset(line);
    QMessageBox::information(this, "Message", "Done");
}


void MainWindow::on_setOneButton_clicked()
{
    size_t line = ui->lineEditSet->text().toInt();
    if (ui->lineEditSet->text().size() == 0 || line >= 64)
    {
        QMessageBox::information(this, "Message", "You need to insert in line a position to set. Must be < size.");
        return;
    }

    bs.set(line);
    QMessageBox::information(this, "Message", "Done");
}


void MainWindow::on_flipOneButton_clicked()
{
    size_t line = ui->lineEditFlip->text().toInt();
    if (ui->lineEditFlip->text().size() == 0 || line >= 64)
    {
        QMessageBox::information(this, "Message", "You need to insert in line a position to flip. Must be < size.");
        return;
    }

    bs.flip(line);
    QMessageBox::information(this, "Message", "Done");
}

