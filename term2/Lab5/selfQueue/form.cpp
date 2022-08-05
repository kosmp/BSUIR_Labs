#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setFixedSize(600, 400);
    ui->comboBox->addItem("size");
    ui->comboBox->addItem("operator=");
    ui->comboBox->addItem("empty");
    ui->comboBox->addItem("front");
    ui->comboBox->addItem("back");
    ui->comboBox->addItem("push");
    ui->comboBox->addItem("pop");
    ui->comboBox->addItem("swap");

    for (int i = 0; i < 10; i++)
    {
        b.push(i + 1);
        ui->listWidget_2->addItem(QString::number(b.back()));
    }
}

Form::~Form()
{
    delete ui;
    if (arr != nullptr)
        delete[] arr;
}

void Form::slot()
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
        a.push(rand() % 25);

    arr = new int[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = a.front();
        ui->listWidget->addItem(QString::number(arr[i]));
        a.pop();
    }

    for (int i = 0; i < 10; i++)
        a.push(arr[i]);
}

void Form::on_pushButton_clicked()
{
    if (a.size() == 1)
    {
        QMessageBox::warning(this, "Message","Only 1 element in the queue");
        return;
    }
    if (a.empty())
    {
        QMessageBox::warning(this, "Message","Queue is empty.");
        return;
    }

    ui->listWidget->clear();
    int minInd = 0;
    int min = arr[0];
    for (int i = 0; i < a.size(); i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            minInd = i;
        }
    }

    int* buff = new int[a.size() - 1];
    bool check = false;
    for (int i = 0; i < a.size(); i++)
    {
        if (i == minInd)
            check = true;
        if (!check && i != minInd)
            buff[i] = arr[i];
        if (check && i != minInd)
            buff[i - 1] = arr[i];
    }

    int size = a.size();
    for (int i = 0; i < size; i++)
        a.pop();
    a.push(min);
    for (int i = 0; i < size - 1; i++)
        a.push(buff[i]);

    ui->listWidget->addItem(QString::number(min));
    for (int i = 0; i < size - 1; i++)
        ui->listWidget->addItem(QString::number(buff[i]));
    QMessageBox::warning(this, "Message","Done");
    delete[] buff;
}


void Form::on_pushButton_2_clicked()
{
    if (ui->comboBox->currentText() == "size")
    {
        QMessageBox::warning(this, "Message", QString::number(a.size()));
    }
    else if (ui->comboBox->currentText() == "operator=")
    {
        ui->listWidget->clear();
        a = b;

        delete[] arr;
        int size = a.size();
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = a.front();
            ui->listWidget->addItem(QString::number(arr[i]));
            a.pop();
        }
        for (int i = 0; i < size; i++)
            a.push(arr[i]);
        QMessageBox::warning(this, "Message","Done");
    }
    else if (ui->comboBox->currentText() == "empty")
    {
        if (a.empty())
            QMessageBox::warning(this, "Message","true");
        else
            QMessageBox::warning(this, "Message","false");
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
    else if (ui->comboBox->currentText() == "push")
    {
        QMessageBox::warning(this, "Message","Enter in additional line digit to push in queue.");
        int num = -1;
        num = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You didn't enter number to push in additional line.");
            return;
        }

        ui->listWidget->clear();
        a.push(num);

        delete[] arr;
        int size = a.size();
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = a.front();
            ui->listWidget->addItem(QString::number(arr[i]));
            a.pop();
        }

        for (int i = 0; i < size; i++)
            a.push(arr[i]);
    }
    else if (ui->comboBox->currentText() == "pop")
    {
        if (a.empty())
        {
            QMessageBox::warning(this, "Message","Queue is empty.");
            return;
        }

        ui->listWidget->clear();
        int size = a.size();
        a.pop();

        delete[] arr;
        arr = new int[size - 1];
        for (int i = 1; i < size; i++)
        {
            arr[i-1] = a.front();
            ui->listWidget->addItem(QString::number(arr[i-1]));
            a.pop();
        }

        for (int i = 0; i < size-1; i++)
            a.push(arr[i]);
    }
    else if (ui->comboBox->currentText() == "swap")
    {
        ui->listWidget->clear();
        ui->listWidget_2->clear();
        a.swap(b);

        int size = a.size();
        delete[] arr;
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = a.front();
            ui->listWidget->addItem(QString::number(arr[i]));
            a.pop();
        }
        for (int i = 0; i < size; i++)
            a.push(arr[i]);

        int sizeB = b.size();
        int* tmpArr = new int[sizeB];
        for (int i = 0; i < sizeB; i++)
        {
            tmpArr[i] = b.front();
            ui->listWidget_2->addItem(QString::number(tmpArr[i]));
            b.pop();
        }

        for (int i = 0; i < sizeB; i++)
            b.push(tmpArr[i]);
        QMessageBox::warning(this, "Message","Done");
    }
}

