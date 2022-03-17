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
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (i >= 10) QMessageBox::warning(this, "Warning","List is overflowed. In this list max can be 10 elements. You can't add more in the list.");
    if (i == 0) ui->label->setVisible(false);
    if (i < 10)
    {
        ui->label->setVisible(true);
        shared_ptr<DoubleList> ptr = make_shared<DoubleList>();
        //ptrSave = ptr;
        list->insert(ptr, i, qrand() % 1000 + 10);
        if (i == 0)
        {
            ui->label->setVisible(true);
            ui->label->setText(QString::number(list->getData(i)));
        }
        if (i == 1)
        {
            ui->label_2->setVisible(true);
            ui->label_2->setText(QString::number(list->getData(i)));
        }
        if (i == 2)
        {
            ui->label_3->setVisible(true);
            ui->label_3->setText(QString::number(list->getData(i)));
        }

        if (i == 3)
        {
            ui->label_4->setVisible(true);
            ui->label_4->setText(QString::number(list->getData(i)));
        }

        if (i == 4)
        {
            ui->label_5->setVisible(true);
            ui->label_5->setText(QString::number(list->getData(i)));
        }
        if (i == 5)
        {
            ui->label_6->setVisible(true);
            ui->label_6->setText(QString::number(list->getData(i)));
        }
        if (i == 6)
        {
            ui->label_7->setVisible(true);
            ui->label_7->setText(QString::number(list->getData(i)));
        }
        if (i == 7)
        {
            ui->label_8->setVisible(true);
            ui->label_8->setText(QString::number(list->getData(i)));
        }
        if (i == 8)
        {
            ui->label_9->setVisible(true);
            ui->label_9->setText(QString::number(list->getData(i)));
        }
        if (i == 9)
        {
            ui->label_10->setVisible(true);
            ui->label_10->setText(QString::number(list->getData(i)));
        }
        i++;
        ptrSave = std::move(ptr);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if (i == 0) ui->label->setVisible(false);
    if (i <= 0) QMessageBox::warning(this, "Warning","List is empty. You can't remove anything from the list.");
    if (i > 0)
    {
        i--;
        list->erase(ptrSave, i);
        ui->label->setVisible(true);
        switch (i)
        {
            case 0:
                ui->label->setVisible(false);
                break;
            case 1:
                ui->label_2->setVisible(false);
                break;
            case 2:
                ui->label_3->setVisible(false);
                break;
            case 3:
                ui->label_4->setVisible(false);
                break;
            case 4:
                ui->label_5->setVisible(false);
                break;
            case 5:
                ui->label_6->setVisible(false);
                break;
            case 6:
                ui->label_7->setVisible(false);
                break;
            case 7:
                ui->label_8->setVisible(false);
                break;
            case 8:
                ui->label_9->setVisible(false);
                break;
            case 9:
                ui->label_10->setVisible(false);
                break;

            default:
                break;
        }
    }
    if (i == 0) ui->label->setVisible(false);
}

