#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->comboBox->addItem("size");
    ui->comboBox->addItem("empty");
    ui->comboBox->addItem("push_back");
    ui->comboBox->addItem("pop_back");
    ui->comboBox->addItem("push_front");
    ui->comboBox->addItem("pop_front");
    ui->comboBox->addItem("clear");
    ui->comboBox->addItem("front");
    ui->comboBox->addItem("back");
    ui->comboBox->addItem("resize");
}

Form::~Form()
{
    delete ui;
}

void Form::slot()
{
    for (int i = 1; i <= 20; i++)
    {
        a.push_back(i);
        ui->listWidget->addItem(QString::number(a.back()));
    }
}

void Form::on_pushButton_clicked()
{
    if (ui->comboBox->currentText() == "size")
    {
        QMessageBox::warning(this, "Message", QString::number(a.size()));
    }
    else if (ui->comboBox->currentText() == "empty")
    {
        if (a.empty())
            QMessageBox::warning(this, "Message","true");
        else
            QMessageBox::warning(this, "Message","false");
    }
    else if (ui->comboBox->currentText() == "push_back")
    {
        QMessageBox::warning(this, "Message","You need to enter integer number to push in additional line");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number to push in additional line.");
            return;
        }
        if (num > 100000000)
        {
            QMessageBox::warning(this, "Message","Too big value.");
            return;
        }

        ui->listWidget->clear();
        a.push_back(num);

        deque<int>::iterator iter(a.begin());
        for (; iter != a.end(); iter++)
        {
            ui->listWidget->addItem(QString::number(*iter));
        }
        ui->listWidget->addItem(QString::number(*iter));
    }
    else if (ui->comboBox->currentText() == "pop_back")
    {
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","Deque is empty.");
            return;
        }

        ui->listWidget->clear();
        int size = a.size();
        a.pop_back();

        deque<int>::iterator iter(a.begin());
        for (; iter != a.end(); iter++)
        {
            ui->listWidget->addItem(QString::number(*iter));
        }
        if (size != 1)
            ui->listWidget->addItem(QString::number(*iter));
    }
    else if (ui->comboBox->currentText() == "push_front")
    {
        QMessageBox::warning(this, "Message","You need to enter integer number to push in additional line");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number to push in additional line.");
            return;
        }
        if (num > 100000000)
        {
            QMessageBox::warning(this, "Message","Too big value.");
            return;
        }

        ui->listWidget->clear();
        a.push_front(num);

        deque<int>::iterator iter(a.begin());
        for (; iter != a.end(); iter++)
        {
            ui->listWidget->addItem(QString::number(*iter));
        }
        ui->listWidget->addItem(QString::number(*iter));
    }
    else if (ui->comboBox->currentText() == "pop_front")
    {
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","Deque is empty.");
            return;
        }

        ui->listWidget->clear();
        int size = a.size();
        a.pop_front();

        deque<int>::iterator iter(a.begin());
        for (; iter != a.end(); iter++)
        {
            ui->listWidget->addItem(QString::number(*iter));
        }
        if (size != 1)
            ui->listWidget->addItem(QString::number(*iter));
    }
    else if (ui->comboBox->currentText() == "clear")
    {
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","Deque is empty.");
            return;
        }

        ui->listWidget->clear();
        a.clear();
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","Now deque is clear");
            return;
        }
    }
    else if (ui->comboBox->currentText() == "front")
    {
        if (a.size() != 0)
            QMessageBox::warning(this, "Message", QString::number(a.front()));
        else
            QMessageBox::warning(this, "Message","Queue is empty");
    }
    else if (ui->comboBox->currentText() == "back")
    {
        if (a.size() != 0)
            QMessageBox::warning(this, "Message", QString::number(a.back()));
        else
            QMessageBox::warning(this, "Message","Queue is empty");
    }
    else if (ui->comboBox->currentText() == "resize")
    {
        QMessageBox::warning(this, "Message","Insert in additional line count to resize. Insert in additional line2 value for case, if count > size.");
        int count = -1;
        count = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number in additional line.");
            return;
        }
        if (count > 1000)
        {
            QMessageBox::warning(this, "Message","Too big size. It's useless");
            return;
        }

        int value = -1;
        value = ui->lineEdit_2->text().toInt();

        if (ui->lineEdit_2->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter value in additional line2 (digit).");
            return;
        }
        if (value > 100000000)
        {
            QMessageBox::warning(this, "Message","Too big value.");
            return;
        }

        if (count <= 0)
        {
            QMessageBox::warning(this, "Message","Count <= 0. Enter other count.");
            return;
        }

        if (count == a.size())
        {
            QMessageBox::warning(this, "Message","Count == size");
            return;
        }
        ui->listWidget->clear();

        a.resize(count, value);

        deque<int>::iterator iter(a.begin());
        for (; iter != a.end(); iter++)
        {
            ui->listWidget->addItem(QString::number(*iter));
        }
        ui->listWidget->addItem(QString::number(*iter));
    }
}

