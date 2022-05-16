#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600, 400);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showButton_clicked()
{
    ui->textEdit->clear();
    if (countOfElemInMap == 0)
    {
        QMessageBox::information(this, "Message", "Map is empty.");
        return;
    }
    QString result;
    map<int, std::string>::iterator1 iter = m.begin();
    while (iter != m.end())
    {
        result += " (" + QString::number((*iter).first) + ", " + QString::fromStdString((*iter).second) + ") ";
        iter++;
    }
    ui->textEdit->setText(result);
}


void MainWindow::on_countButton_clicked()
{
    int line = ui->lineEditCount->text().toInt();
    if (ui->lineEditCount->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to check.");
        return;
    }

    QMessageBox::information(this, "Message", QString::number(m.count(line)));
}


void MainWindow::on_insertButton_clicked()
{
    int line = ui->lineEditInsertKey->text().toInt();
    if (ui->lineEditInsertKey->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to insert.");
        return;
    }

    std::string lineData = ui->lineEditInsertData->text().toStdString();
    if (ui->lineEditInsertData->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in data line string to insert.");
        return;
    }

    if (countOfElemInMap != 0 && m.find(line) == m.end())
    countOfElemInMap++;

    if (countOfElemInMap == 0)
    {
        countOfElemInMap++;
    }
    m.insert(std::make_pair(line, lineData));
}


void MainWindow::on_removeButton_clicked()
{
    int line = ui->lineEditEraseKey->text().toInt();
    if (ui->lineEditEraseKey->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to erase.");
        return;
    }

    if (countOfElemInMap == 0 || m.find(line) == m.end())
    {
        QMessageBox::information(this, "Message", "No such key.");
        return;
    }
    m.erase(line);
    countOfElemInMap--;
}


void MainWindow::on_findButton_clicked()
{
    int line = ui->lineEditFindKey->text().toInt();
    if (ui->lineEditFindKey->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to find.");
        return;
    }

    map<int, std::string>::iterator1 iter = m.find(line);
    if (countOfElemInMap == 0 || iter == m.end())
    {
        QMessageBox::information(this, "Message", "No such key.");
        return;
    }

    QMessageBox::information(this, "Message", "Key: " + QString::number((*iter).first) + ", Data: " + QString::fromStdString((*iter).second));
}


void MainWindow::on_atButton_clicked()
{
    int line = ui->lineEditFindKey->text().toInt();
    if (ui->lineEditFindKey->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to find.");
        return;
    }

    map<int, std::string>::iterator1 iter = m.find(line);
    if (countOfElemInMap == 0 || iter == m.end())
    {
        QMessageBox::information(this, "Message", "No such key.");
        return;
    }

    std::string res = m.at(line);

    QMessageBox::information(this, "Message", "Data: " + QString::fromStdString(res));
}

