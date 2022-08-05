#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1200, 600);
    this->setFixedSize(1200,600);
    scene = new QGraphicsScene();
    wheel = new Wheel();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,1200,590);
    scene->addItem(wheel);
    ui->pushButton->setText("Start");
    timer = new QTimer(this);
    time = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //timer->start(100);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete wheel;
    delete ui;
}


void MainWindow::timerSlot()
{
    time++;
    wheel->setTransformOriginPoint(300,300);
    wheel->setRotation(time);
    wheel->moving();
}


void MainWindow::on_pushButton_clicked()
{
    flag = !flag;
    if(flag)
    {
        ui->pushButton->setText("Start");
        timer->stop();
    }
    else
    {
        ui->pushButton->setText("Stop");
        timer->start(5);
    }
}

