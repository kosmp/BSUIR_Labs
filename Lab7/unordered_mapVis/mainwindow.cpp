#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(850, 440);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->textEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::print()
{
    ui->textEdit->clear();
    QString table;
    unordered_map<int, std::string>::iterator iter = um.begin();
    while (iter != um.end())
    {
        table += " (Hash: " + QString::number((*iter).cached_hash) + ", Key: " + QString::number((*iter).kv->first) + ", Data: " + QString::fromStdString((*iter).kv->second) + ") ";
        unordered_map<int, std::string>::iterator tmp = iter;
        ++tmp;
        if (tmp == um.end()) break;
        if ((*tmp).cached_hash != (*iter).cached_hash)  // new hash - new str
            table += '\n';
        iter++;
    }
    ui->textEdit->setText(table);
}


void MainWindow::on_loadFactorButton_clicked()
{
    float res = um.load_factor();
    QMessageBox::information(this, "Message", QString::number(res));
}


void MainWindow::on_sizeButton_clicked()
{
    size_t res = um.size();
    QMessageBox::information(this, "Message", QString::number(res));
}


void MainWindow::on_EmptyButton_clicked()
{
    bool res = um.empty();
    if (res)
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_clearButton_clicked()
{
    um.clear();
    ui->textEdit->clear();
    QMessageBox::information(this, "Message", "Cleared");
}


void MainWindow::on_insertButton_clicked()
{
    int line = ui->lineEditInsert->text().toInt();
    if (ui->lineEditInsert->text().size() == 0)
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

    if (um.contains(line))
    {
        QMessageBox::information(this, "Message", "Such key is already there.");
        return;
    }

    um.insert(std::make_pair(line, lineData));
    print();
}


void MainWindow::on_eraseButton_clicked()
{
    int line = ui->lineEditErase->text().toInt();
    if (ui->lineEditErase->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to erase.");
        return;
    }

    if (!um.contains(line))
    {
        QMessageBox::information(this, "Message", "No Such key.");
        return;
    }
    um.erase(line);
    print();
}


void MainWindow::on_containsButton_clicked()
{
    int line = ui->lineEditContains->text().toInt();
    if (ui->lineEditContains->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to find.");
        return;
    }

    if (um.contains(line))
        QMessageBox::information(this, "Message", "true");
    else
        QMessageBox::information(this, "Message", "false");
}


void MainWindow::on_operatorButton_clicked()
{
    int line = ui->lineEditKeyOperator->text().toInt();
    if (ui->lineEditKeyOperator->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in line integer key to use in [ ].");
        return;
    }

    std::string lineData = ui->lineEditDataOperator->text().toStdString();
    if (ui->lineEditDataOperator->text().size() == 0)
    {
        QMessageBox::information(this, "Message", "Insert in data line string to use.");
        return;
    }

    um[line] = lineData;
    print();
}

