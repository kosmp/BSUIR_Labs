#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(200, 100);
    form = new Form();
    connect(this, &MainWindow::signal, form, &Form::slot);
}

MainWindow::~MainWindow()
{
    delete form;
}


void MainWindow::on_pushButton_clicked()
{
    form->show();
    emit signal();
    this->hide();
}

