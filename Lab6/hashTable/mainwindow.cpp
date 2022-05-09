#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("InsertItem");
    ui->comboBox->addItem("DeleteItem");
    ui->comboBox->addItem("FindIndOfStackWithMax");
    ui->comboBox->addItem("FindIndOfStackWithValue");
    ui->comboBox->addItem("Empty");
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->textEdit->setReadOnly(true);

    srand(time(NULL));
    for (int i = 0; i < 30; i++)
        a.insertItem(rand() % 354);
    print();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::print()
{
    ui->textEdit->setText(a.printTable());
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->comboBox->currentText() == "InsertItem")
    {
        QMessageBox::warning(this, "Message", "Insert in additional line1 int number so as to insert in hash table.");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number to insert in additional line1.");
            return;
        }
        ui->textEdit->clear();
        a.insertItem(num);
        print();
    }
    else if (ui->comboBox->currentText() == "DeleteItem")
    {
        QMessageBox::warning(this, "Message", "Insert in additional line1 int number so as to delete from hash table.");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number to delete in additional line1.");
            return;
        }
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","HashTable is empty");
            return;
        }
        ui->textEdit->clear();
        a.deleteItem(num);
        print();
        QMessageBox::warning(this, "Message","Item was removed if hashTable had such element.");
    }
    else if (ui->comboBox->currentText() == "FindIndOfStackWithMax")
    {
        if (a.empty())
        {
            QMessageBox::warning(this, "Message", "HashTable is empty.");
            return;
        }
        QMessageBox::warning(this, "Message", "Ind of stack with max value: " + QString::number(a.findStackWithMax()));
    }
    else if (ui->comboBox->currentText() == "FindIndOfStackWithValue")
    {
        QMessageBox::warning(this, "Message","Insert in additional line1 value to find in hashTable.");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter value to find in additional line1.");
            return;
        }

        if (a.empty())
        {
            QMessageBox::warning(this, "Message", "HashTable is empty.");
            return;
        }
        int indOfStack = a.findStackWithValue(num);
        if (indOfStack != -1)
            QMessageBox::warning(this, "Message", "Ind of stack with such value: " + QString::number(indOfStack));
        else
            QMessageBox::warning(this, "Message", "No such value");
    }
    else if (ui->comboBox->currentText() == "Empty")
    {
        if (a.empty())
            QMessageBox::warning(this, "Message", "True");
        else
            QMessageBox::warning(this, "Message", "False");
    }
}
