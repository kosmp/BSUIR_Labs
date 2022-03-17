#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(300,400);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,300,400);
    ui->label_0->setVisible(false);
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_Button_clicked()
{
    if (i >= 10) QMessageBox::warning(this, "Warning","Stack is overflowed. You can't add more in the stack.");
    if (i == 0) ui->label->setVisible(false);
    if (i < 10)
    {
        ui->label->setVisible(true);
        stack[i] = qrand() % 1000 + 10;
        if (i == 0)
        {
            ui->label_0->setVisible(true);
            ui->label_0->setText(QString::number(stack[i]));
        }
        if (i == 1)
        {
            ui->label_1->setVisible(true);
            ui->label_1->setText(QString::number(stack[i]));
        }
        if (i == 2)
        {
            ui->label_2->setVisible(true);
            ui->label_2->setText(QString::number(stack[i]));
        }

        if (i == 3)
        {
            ui->label_3->setVisible(true);
            ui->label_3->setText(QString::number(stack[i]));
        }

        if (i == 4)
        {
            ui->label_4->setVisible(true);
            ui->label_4->setText(QString::number(stack[i]));
        }
        if (i == 5)
        {
            ui->label_5->setVisible(true);
            ui->label_5->setText(QString::number(stack[i]));
        }
        if (i == 6)
        {
            ui->label_6->setVisible(true);
            ui->label_6->setText(QString::number(stack[i]));
        }
        if (i == 7)
        {
            ui->label_7->setVisible(true);
            ui->label_7->setText(QString::number(stack[i]));
        }
        if (i == 8)
        {
            ui->label_8->setVisible(true);
            ui->label_8->setText(QString::number(stack[i]));
        }
        if (i == 9)
        {
            ui->label_9->setVisible(true);
            ui->label_9->setText(QString::number(stack[i]));
        }
        i++;
    }
}


void MainWindow::on_delete_Button_clicked()
{
    if (i == 0) ui->label->setVisible(false);
    if (i <= 0) QMessageBox::warning(this, "Warning","Stack is empty. You can't remove anything from the stack.");
    if (i > 0)
    {
        i--;
        ui->label->setVisible(true);
        switch (i)
        {
            case 0:
                ui->label_0->setVisible(false);
                break;
            case 1:
                ui->label_1->setVisible(false);
                break;
            case 2:
                ui->label_2->setVisible(false);
                break;
            case 3:
                ui->label_3->setVisible(false);
                break;
            case 4:
                ui->label_4->setVisible(false);
                break;
            case 5:
                ui->label_5->setVisible(false);
                break;
            case 6:
                ui->label_6->setVisible(false);
                break;
            case 7:
                ui->label_7->setVisible(false);
                break;
            case 8:
                ui->label_8->setVisible(false);
                break;
            case 9:
                ui->label_9->setVisible(false);
                break;

            default:
                break;
        }
    }
    if (i == 0) ui->label->setVisible(false);
}

