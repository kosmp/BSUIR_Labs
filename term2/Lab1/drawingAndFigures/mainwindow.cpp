#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(700, 720);
    this->setFixedSize(700,720);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,700,700);
    time = 0;
    ui->radioButton->setText("Triangle");
    ui->radioButton_2->setText("Square");
    ui->radioButton_3->setText("Hexagon");
    ui->radioButton_4->setText("Rhombus");
    ui->radioButton_5->setText("Rectangle");
    ui->radioButton_6->setText("Five-Star");
    ui->radioButton_7->setText("Six-Star");
    ui->radioButton_8->setText("Eight-Star");
    ui->radioButton_9->setText("Ellipse");
    ui->radioButton_10->setText("Circle");
    ui->pushButton->setText("<--");
    ui->pushButton_2->setText("-->");
    ui->pushButton_3->setText("+");
    ui->pushButton_4->setText("-");
    ui->pushButton_5->setText("rotating");
    ui->pushButton_6->setText("up");
    ui->pushButton_7->setText("down");
    timer = new QTimer();
    scale = 1;
    figure = nullptr;
    ui->radioButton->click();
    ui->label_3->setText("Area:");
    ui->label_4->setText("Perimetr:");
    ui->pushButton_8->setText("Enter");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //scene->addEllipse(event->x() - 5, event->y() - 5, 10,10, QPen(Qt::NoPen), QBrush(Qt::red));
    previousPoint = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    scene->addLine(previousPoint.x(), previousPoint.y(), event->x(), event->y(), QPen(Qt::red,8,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->pos();
}

void MainWindow::slotLines(const char* figures)
{
    if (!strcmp(figures, "Triangle"))
    {
        int x1 = ui->lineEdit->text().toInt();
        int y1 = ui->lineEdit_2->text().toInt();
        int x2 = ui->lineEdit_3->text().toInt();
        int y2 = ui->lineEdit_4->text().toInt();
        int x3 = ui->lineEdit_5->text().toInt();
        int y3 = ui->lineEdit_6->text().toInt();
        if (x1 == x2 && x2 == x3)
            if (x1 == x3)
            {
                QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers(coordinates) from 1 to 500 in the input fields! It's triangle vertex coordinates. So as to see a triangle, you must enter correct coordinates. x1 isn't equal x2 isn't equal x3");
                return;
            }
        if (y1 == y2 && y2 == y3)
            if (y1 == y3)
            {
                QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers(coordinates) from 1 to 500 in the input fields! It's triangle vertex coordinates. So as to see a triangle, you must enter correct coordinates. y1 isn't equal y2 isn't equal y3");
                return;
            }

        if(x1 > 0 && x2 > 0 && x3 > 0 && y1 > 0 && y2 > 0 && y3 > 0 && x1 <= 500 && x2 <= 500 && x3 <= 500 && y1 <= 500 && y2 <= 500 && y3 <= 500)
        {
            figure->setCoordTriangle(x1, y1, x2, y2, x3, y3);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers(coordinates) from 1 to 500 in the input fields! It's triangle vertex coordinates. So as to see a triangle, you must enter correct coordinates.");
        }
    }
    else if(!strcmp(figures, "Square"))
    {
        int x1 = ui->lineEdit_4->text().toInt();
        int y1  = ui->lineEdit_5->text().toInt();
        int side = ui->lineEdit_6->text().toInt();
        if (x1 > 0 && y1 > 0 && side > 0 && x1 <= 500 && y1 <= 500 && side <= 500)
        {
            figure->setCoord(x1, y1, side);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500 in the input fields! In the 1-st field - coordinate x1, in the 2-nd field coordinate y1 of current figure's vertex. In the 3-rd field - side of this square. Fields can't be empty.");
        }
    }
    else if(!strcmp(figures, "Hexagon"))
    {
        int R = ui->lineEdit_6->text().toInt();
        if (R > 0 && R <= 500)
        {
            figure->setCoordHexagon(R);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500 in the input fields. It's the radius of the circumscribed circle.");
        }
    }
    else if(!strcmp(figures, "Ellipse"))
    {
        int x = ui->lineEdit_3->text().toInt();
        int y = ui->lineEdit_4->text().toInt();
        int w  = ui->lineEdit_5->text().toInt();
        int h = ui->lineEdit_6->text().toInt();
        if (x > 0 && y > 0 && w > 0 && h > 0 && x <= 500 && y <= 500 && w <= 500 && h <= 500)
        {
            figure->setCoord(x, y, w, h);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - coordinate x, 2-nd field - coordinate y, 3-rd field - width, 4-th field - height");
        }
    }
    else if(!strcmp(figures, "Circle"))
    {
        int x1 = ui->lineEdit_4->text().toInt();
        int y1  = ui->lineEdit_5->text().toInt();
        int side = ui->lineEdit_6->text().toInt();
        if (x1 > 0 && y1 > 0 && side > 0 && x1 <= 500 && y1 <= 500 && side <= 500)
        {
            figure->setCoord(x1, y1, side);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - coordinate x, 2-nd field - coordinate y, 3-rd field - side");
        }
    }
    else if(!strcmp(figures, "Rectangle"))
    {
        int x = ui->lineEdit_3->text().toInt();
        int y  = ui->lineEdit_4->text().toInt();
        int w = ui->lineEdit_5->text().toInt();
        int h = ui->lineEdit_6->text().toInt();
        if (x > 0 && y > 0 && w > 0 && h > 0 && x <= 500 && y <= 500 && w <= 500 && h <= 500)
        {
            figure->setCoord(x, y, w, h);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - coordinate x, 2-nd field - coordinate y, 3-rd field - width, 4-th field - height");
        }
    }
    else if(!strcmp(figures, "Rhombus"))
    {
        int x1 = ui->lineEdit_3->text().toInt();
        int y1 = ui->lineEdit_4->text().toInt();
        int d1  = ui->lineEdit_5->text().toInt();
        int d2 = ui->lineEdit_6->text().toInt();
        if (x1 > 0 && y1 > 0 && d1 > 0 && d2 > 0 && x1 <= 500 && y1 <= 500 && d1 <= 500 && d2 <= 500)
        {
            figure->setCoord(x1, y1, d1, d2);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - coordinate x1, 2-nd field - coordinate y1, 3-rd field - diagonal d1, 4-th field - diagonal d2.");
        }
    }
    else if(!strcmp(figures, "StarFive"))
    {
        int r  = ui->lineEdit_5->text().toInt();
        int R = ui->lineEdit_6->text().toInt();
        if (r > 0 && R > 0 && r <= 500 && R <= 500 && r < R)
        {
            figure->setCoord(r, R);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - radius r - inscribed circle radius, 2-nd field - radius R - circumscribed circle radius. r must be < R");
        }
    }
    else if(!strcmp(figures, "StarSix"))
    {
        int r  = ui->lineEdit_5->text().toInt();
        int R = ui->lineEdit_6->text().toInt();
        if (r > 0 && R > 0 && r <= 500 && R <= 500 && r < R)
        {
            figure->setCoord(r, R);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - radius r - inscribed circle radius, 2-nd field - radius R - circumscribed circle radius. r must be < R");
        }
    }
    else if(!strcmp(figures, "StarEight"))
    {
        int r  = ui->lineEdit_5->text().toInt();
        int R = ui->lineEdit_6->text().toInt();
        if (r > 0 && R > 0 && r <= 500 && R <= 500 && r < R)
        {
            figure->setCoord(r, R);
        }
        else
        {
            QMessageBox::warning(0,"Warning", "You have entered smth incorrect! You need to insert numbers from 1 to 500. 1-st field - radius r - inscribed circle radius, 2-nd field - radius R - circumscribed circle radius. r must be < R");
        }
    }
}

void MainWindow::on_radioButton_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_5->setText("x1:");
    ui->label_6->setText("y1:");
    ui->label_7->setText("x2:");
    ui->label_8->setText("y2:");
    ui->label_9->setText("x3:");
    ui->label_10->setText("y3:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Triangle();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_2_clicked()
{
    time= 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_8->setText("x1:");
    ui->label_9->setText("y1:");
    ui->label_10->setText("side:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Square();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_3_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(true);
    ui->label_10->setText("R:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Hexagon();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_4_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_7->setText("x1:");
    ui->label_8->setText("y1:");
    ui->label_9->setText("d1:");
    ui->label_10->setText("d2:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Rhombus();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_5_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_7->setText("x1:");
    ui->label_8->setText("y1:");
    ui->label_9->setText("w:");
    ui->label_10->setText("h:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Rectangle();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_6_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_9->setText("r:");
    ui->label_10->setText("R:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new StarFive();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_9->setText("r:");
    ui->label_10->setText("R:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new StarSix();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_8_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_9->setText("r:");
    ui->label_10->setText("R:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;  
    }
    figure = new StarEight();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_9_clicked()
{
    time = 0;
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_7->setText("x:");
    ui->label_8->setText("y:");
    ui->label_9->setText("w:");
    ui->label_10->setText("h:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Ellipse();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::on_radioButton_10_clicked()
{
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_8->setText("x:");
    ui->label_9->setText("y:");
    ui->label_10->setText("r:");
    if(figure)
    {
        scene->removeItem(figure);
        delete figure;
        figure = nullptr;
    }
    figure = new Circle();
    scene->addItem(figure);
    ui->label->setNum(figure->square());
    ui->label_2->setNum(figure->perimetr());
}

void MainWindow::slotRotate()
{
    time++;
    figure->rotating(time);
}

void MainWindow::slotMoveForward()
{
    figure->moving(1);
}

void MainWindow::slotMoveBack()
{
    figure->moving(2);
}

void MainWindow::slotMoveUp()
{
    figure->moving(3);
}

void MainWindow::slotMoveDown()
{
    figure->moving(4);
}

void MainWindow::slotScaleUp()
{
    scale += 0.001;
    figure->scaling(1, scale);
}

void MainWindow::slotScaleDown()
{
    if(scale != 1.0)
    {
        scale -= 0.001;
    }
    figure->scaling(2, scale);
}

void MainWindow::on_pushButton_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotMoveBack()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton->setText("<--");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotMoveBack()));
    }
    else
    {
        ui->pushButton->setText("Continue or stop");
        timer->start(25);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotMoveForward()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_2->setText("-->");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotMoveForward()));
    }
    else
    {
        ui->pushButton_2->setText("Continue or stop");
        timer->start(25);
    }
}

float MainWindow::scale = 1.0;

void MainWindow::on_pushButton_3_clicked()
{
    // +
    connect(timer, SIGNAL(timeout()), this, SLOT(slotScaleUp()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_3->setText("+");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotScaleUp()));
    }
    else
    {
        ui->pushButton_3->setText("continue or stop");
        timer->start(25);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    // -
    connect(timer, SIGNAL(timeout()), this, SLOT(slotScaleDown()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_4->setText("-");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotScaleDown()));
    }
    else
    {
        ui->pushButton_4->setText("continue or stop");
        timer->start(25);
    }

}


void MainWindow::on_pushButton_5_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotRotate()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_5->setText("rotating");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotRotate()));
    }
    else
    {
        ui->pushButton_5->setText("continue or stop");
        timer->start(25);
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotMoveUp()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_6->setText("up");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotMoveUp()));
    }
    else
    {
        ui->pushButton_6->setText("Continue or stop");
        timer->start(25);
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(slotMoveDown()));
    flag = !flag;
    if(flag)
    {
        ui->pushButton_7->setText("down");
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(slotMoveDown()));
    }
    else
    {
        ui->pushButton_7->setText("Continue or stop");
        timer->start(25);
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    if (!strcmp(figure->checkType(),"Triangle"))
    {
        slotLines("Triangle");
    }
    else if (!strcmp(figure->checkType(),"Square"))
    {
        slotLines("Square");
    }
    else if (!strcmp(figure->checkType(),"Hexagon"))
    {
        slotLines("Hexagon");
    }
    else if (!strcmp(figure->checkType(),"Ellipse"))
    {
        slotLines("Ellipse");
    }
    else if (!strcmp(figure->checkType(),"Circle"))
    {
        slotLines("Circle");
    }
    else if (!strcmp(figure->checkType(),"Rectangle"))
    {
        slotLines("Rectangle");
    }
    else if (!strcmp(figure->checkType(),"Rhombus"))
    {
        slotLines("Rhombus");
    }
    else if (!strcmp(figure->checkType(),"StarFive"))
    {
        slotLines("StarFive");
    }
    else if (!strcmp(figure->checkType(),"StarSix"))
    {
        slotLines("StarSix");
    }
    else if (!strcmp(figure->checkType(),"StarEight"))
    {
        slotLines("StarEight");
    }
}

