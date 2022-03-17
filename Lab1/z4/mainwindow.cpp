#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,500);
    this->setFixedSize(1000,500);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,1000,500);
    ui->tableWidget_2->setColumnCount(1);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->resizeRowsToContents();
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "");
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete[] things;
    delete[] thingsLines;
    delete ui;
}

void MainWindow::sortByCode()
{
    ui->tableWidget_2->clear();
    QString* tempLines = new QString[i+1];
    for (int j = 0; j < i; j++)
        tempLines[j] = thingsLines[j];
    StorageUnit* tempThings = new StorageUnit[i+1];
    for (int j = 0; j < i; j++)
        tempThings[j] = things[j];
    for (int a = 1; a < i; a++)
        for (int b = i - 1; b >= a; b--)
            if (tempThings[b-1].code > tempThings[b].code)
            {
                int t = tempThings[b-1].code;
                tempThings[b-1].code = tempThings[b].code;
                tempThings[b].code = t;
                QString k = tempLines[b-1];
                tempLines[b-1] = tempLines[b];
                tempLines[b] = k;
            }
    delete[] tempThings;
    ui->tableWidget_2->setRowCount(i);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods are sorted by code");

    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(tempLines[row]));
    delete[] tempLines;
}

void MainWindow::sortByCost()
{
    ui->tableWidget_2->clear();
    QString* tempLines = new QString[i+1];
    for (int j = 0; j < i; j++)
        tempLines[j] = thingsLines[j];
    StorageUnit* tempThings = new StorageUnit[i+1];
    for (int j = 0; j < i; j++)
        tempThings[j] = things[j];
    for (int a = 1; a < i; a++)
        for (int b = i - 1; b >= a; b--)
            if (tempThings[b-1].cost > tempThings[b].cost)
            {
                int t = tempThings[b-1].cost;
                tempThings[b-1].cost = tempThings[b].cost;
                tempThings[b].cost = t;
                QString k = tempLines[b-1];
                tempLines[b-1] = tempLines[b];
                tempLines[b] = k;
            }
    delete[] tempThings;

    ui->tableWidget_2->setRowCount(i);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods are sorted by cost");

    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(tempLines[row]));
    delete[] tempLines;
}

void MainWindow::sortByName()
{
    ui->tableWidget_2->clear();
    QString* tempLines = new QString[i+1];
    for (int j = 0; j < i; j++)
        tempLines[j] = thingsLines[j];
    StorageUnit* tempThings = new StorageUnit[i+1];
    for (int j = 0; j < i; j++)
    {
        tempThings[j] = things[j];
        tempThings[j].name[0] = tempThings[j].name[0].toLower();
    }

    for (int a = 1; a < i; a++)
        for (int b = i - 1; b >= a; b--)
            if (tempThings[b-1].name[0] > tempThings[b].name[0])
            {
                QString t = tempThings[b-1].name;
                tempThings[b-1].name = tempThings[b].name;
                tempThings[b].name = t;
                QString k = tempLines[b-1];
                tempLines[b-1] = tempLines[b];
                tempLines[b] = k;
            }
    delete[] tempThings;
    ui->tableWidget_2->setRowCount(i);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods are sorted by name");

    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(tempLines[row]));
    delete[] tempLines;
}

void MainWindow::searchName()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info to see info");
    QString name = ui->lineEdit_4->text();
    for (int j = 0; j < name.size(); j++)
        if (!((name[j] >= 65 && name[j] <= 90) || (name[j] >= 97 && name[j] <= 122)))
        {
            ui->tableWidget_2->clear();
            QMessageBox::warning(this, "Warning","You entered smth incorrect.");
            return;
        }
    if (name.size() == 0)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect.");
        return;
    }
    QString* arr1 = new QString[i+1];
    int counter = 0;
    for (int j = 0; j < i; j++)
        if (things[j].name == name)
        {
            arr1[counter] = thingsLines[j];
            counter++;
        }
    ui->tableWidget_2->setRowCount(counter);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods which is " << name);
    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(arr1[row]));
    delete[] arr1;
}

void MainWindow::searchModel()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info to see info");
    QString model = ui->lineEdit_5->text();
    for (int j = 0; j < model.size(); j++)
        if (!((model[j] >= 65 && model[j] <= 90) || (model[j] >= 97 && model[j] <= 122)))
        {
            ui->tableWidget_2->clear();
            QMessageBox::warning(this, "Warning","You entered smth incorrect.");
            return;
        }
    if (model.size() == 0)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect.");
        return;
    }
    QString* arr1 = new QString[i+1];
    int counter = 0;
    for (int j = 0; j < i; j++)
        if (things[j].model == model)
        {
            arr1[counter] = thingsLines[j];
            counter++;
        }
    ui->tableWidget_2->setRowCount(counter);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods which is " << model);
    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(arr1[row]));
    delete[] arr1;
}

void MainWindow::showThings()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info to see info");
    QString lineEdit_3 = ui->lineEdit_3->text();
    for (int j = 0; j < lineEdit_3.size(); j++)
        if (!(lineEdit_3[j] >= 48 && lineEdit_3[j] <= 57))
        {
            QMessageBox::warning(this, "Warning","You entered smth incorrect.");
            return;
        }
    if (lineEdit_3.toInt() > 100000)
    {
        QMessageBox::warning(this, "Warning","Incorrect input. Must be <= 100000");
        return;
    }

    if (lineEdit_3.size() == 0)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect.");
        return;
    }
    QString* arr1 = new QString[i+1];
    int k = 0;
    for (int j = 0; j < i; j++)
        if (things[j].count < lineEdit_3.toInt())
        {
            arr1[k] = things[j].name;
            k++;
        }
    ui->tableWidget_2->setRowCount(k);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Goods which < " << lineEdit_3);
    for (int row = 0; row < ui->tableWidget_2->rowCount(); row++)
        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(arr1[row]));
    delete[] arr1;
}

void MainWindow::textOutput()
{
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setColumnWidth(0, 400);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Goods (in order: Group Code Name Model Cost Count)");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < ui->tableWidget->rowCount(); row++)
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(thingsLines[row]));
}

bool MainWindow::test(QString& line)
{
    int countOfSpaces = 0;
    int posOfSpace[5];
    for (int j = 0; j < line.size(); j++)
    {
        if(line.at(j) == ' ')
        {
            posOfSpace[countOfSpaces] = j;
            countOfSpaces++;
        }
    }
    bool checkSt = false;
    for (int j = 0; j == ' '; j++)  // пробелы в начале
        checkSt = true;
    if (countOfSpaces != 5 || line.size() < 10 || checkSt)
        return false;
    int startSymbol = posOfSpace[0] + 1;
    int endSymbol = posOfSpace[1];
    for (int j = 0; j < posOfSpace[0]; j++)
        if (!((line.at(j) >= 65 && line.at(j) <= 90) || (line.at(j) >= 97 && line.at(j) <= 122)))
            return false;
    QString test1;
    for (; startSymbol < endSymbol; startSymbol++)
    {
        test1 += line.at(startSymbol);
        if (!(line.at(startSymbol) >= 48 && line.at(startSymbol) <= 57))
            return false;
    }
    if (test1.toInt() > 100000)
    {
        QMessageBox::warning(this, "Warning","Incorrect input. Code must be <= 100000");
        return false;
    }

    for (startSymbol = posOfSpace[1] + 1, endSymbol = posOfSpace[2]; startSymbol < endSymbol; startSymbol++)
        if (!((line.at(startSymbol) >= 65 && line.at(startSymbol) <= 90) || (line.at(startSymbol) >= 97 && line.at(startSymbol) <= 122)))
            return false;
    for (startSymbol = posOfSpace[2] + 1, endSymbol = posOfSpace[3]; startSymbol < endSymbol; startSymbol++)
        if (!((line.at(startSymbol) >= 65 && line.at(startSymbol) <= 90) || (line.at(startSymbol) >= 97 && line.at(startSymbol) <= 122)))
            return false;
    QString test2;
    for (startSymbol = posOfSpace[3] + 1, endSymbol = posOfSpace[4]; startSymbol < endSymbol; startSymbol++)
    {
        test2 += line.at(startSymbol);
        if (!(line.at(startSymbol) >= 48 && line.at(startSymbol) <= 57))
            return false;
    }
    if (test2.toInt() > 100000)
    {
        QMessageBox::warning(this, "Warning","Incorrect input. Cost must be <= 100000");
        return false;
    }

    QString test3;
    for (startSymbol = posOfSpace[4] + 1; startSymbol < line.size(); startSymbol++)
    {
        test3 += line.at(startSymbol);
        if (!(line.at(startSymbol) >= 48 && line.at(startSymbol) <= 57))
            return false;
    }
    if (test3.toInt() > 100000)
    {
        QMessageBox::warning(this, "Warning","Incorrect input. Count must be <= 100000");
        return false;
    }

    return true;
}

void MainWindow::loadFromFile()
{
    // "D:/qt projects/z4/storage.txt"
    i = 0;
    if (things)
    delete[] things;
    QFile file(filename);
    QTextStream in(&file);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File wasn't opened!";
    }
    int countOfLines = 0;
    while(!in.atEnd())
    {
        in.readLine();
        countOfLines++;
    }
    file.close();
    file.open(QIODevice::ReadOnly);
    things = new StorageUnit[countOfLines+1];
    if (thingsLines)
    delete[] thingsLines;
    thingsLines = new QString[countOfLines+1];
    bool problem = true;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if (line.size() > 0)
        {
            qDebug() << "Reading: " << line;
            if (test(line))
            {
                pushInArray(line, i);
                qDebug() << "i "<< i;
                i++;
            }
            else
            {
                QMessageBox::warning(this, "Warning","Incorrect input. File contains incorrect info. So as to use normally this app, correct info in this file before starting. Acсording to this rules: group code name model cost count in each next line");
                exit(123);
            }

        }
    }
    file.close();
    if(!problem)
    {
        QMessageBox::warning(this, "Warning","Incorrect input. File contains incorrect info. So as to use normally this app, correct info in this file before starting. Acсording to this rules: group code name model cost count in each next line");
        exit(123);
    }

    ui->comboBox->clear();
    for (int j = 0; j < i; j++)
    {
        ui->comboBox->addItem(QString::number(j+1));
    }
    ui->comboBox_2->clear();
    for (int j = 0; j < i; j++)
    {
        ui->comboBox_2->addItem(QString::number(j+1));
    }
    ui->tableWidget->clear();
    textOutput();
}

void MainWindow::deleteFromFile(int problem, bool check)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    QTextStream out(&file);
    if (check)
    {
        for (int j = 0; j <= i; j++)
            if (j != problem - 1)
                out << thingsLines[j] << "\r\n";
    }
    else
    {
        for (int j = 0; j < i; j++)
            if (j != problem)
                out << thingsLines[j] << "\r\n";
    }

    file.close();
    loadFromFile();
}

void MainWindow::saveToFile()
{
    QFile file(filename);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "File wasn't opened!";
        //exit(101);
    }
    QString line = ui->lineEdit->text();
    if (test(line))
        out << line << "\r\n";
    file.close();
    loadFromFile();
}

void MainWindow::pushInArray(QString line, int index1)
{
    thingsLines[index1] = line;
    int countOfSpaces = 0;
    int posOfSpace[5];
    for (int j = 0; j < line.size(); j++)
    {
        if(line.at(j) == ' ')
        {
            posOfSpace[countOfSpaces] = j;
            countOfSpaces++;
        }
    }
    QString tempLine;
    for (int j = 0; j < posOfSpace[0]; j++)
        tempLine += line.at(j);
    things[index1].group = tempLine;
    int startSymbol = posOfSpace[0] + 1;
    int endSymbol = posOfSpace[1];
    tempLine.clear();
    for (; startSymbol < endSymbol; startSymbol++)
        tempLine += line.at(startSymbol);
    things[index1].code = tempLine.toInt();
    tempLine.clear();
    for (startSymbol = posOfSpace[1] + 1, endSymbol = posOfSpace[2]; startSymbol < endSymbol; startSymbol++)
        tempLine += line.at(startSymbol);
    things[index1].name = tempLine;
    tempLine.clear();
    for (startSymbol = posOfSpace[2] + 1, endSymbol = posOfSpace[3]; startSymbol < endSymbol; startSymbol++)
        tempLine += line.at(startSymbol);
    things[index1].model = tempLine;
    tempLine.clear();
    for (startSymbol = posOfSpace[3] + 1, endSymbol = posOfSpace[4]; startSymbol < endSymbol; startSymbol++)
        tempLine += line.at(startSymbol);
    things[index1].cost = tempLine.toInt();
    tempLine.clear();
    for (startSymbol = posOfSpace[4] + 1; startSymbol < line.size(); startSymbol++)
        tempLine += line.at(startSymbol);
    things[index1].count = tempLine.toInt();
}

void MainWindow::changeData()
{
    currentComboBox = ui->lineEdit_2->text();
    if (test(currentComboBox))
        pushInArray(currentComboBox, currentToChange);
    else
        QMessageBox::warning(this, "Warning","Incorrect input");
    QFile file(filename);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "File wasn't opened!";
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    for (int t = 0; t < i; t++)
        out << thingsLines[t] << "\r\n";
    file.close();
    loadFromFile();
}

void MainWindow::on_pushButton_clicked()
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    QString line = ui->lineEdit->text();
    if(test(line))
        saveToFile();
    else
        QMessageBox::warning(this, "Warning","Incorrect input");
}


void MainWindow::on_pushButton_2_clicked()
{
    QString current = ui->comboBox->currentText();
    if (i == 0) QMessageBox::warning(this, "Warning", "Empty file");
    deleteFromFile(current.toInt(), true);
}


void MainWindow::on_pushButton_3_clicked()
{
    changeData();
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index < 0) index = 0;
    ui->lineEdit_2->clear();
    currentComboBox.clear();
    currentToChange = index;
    currentComboBox += things[index].group;
    currentComboBox += ' ';
    currentComboBox += QString::number(things[index].code);
    currentComboBox += ' ';
    currentComboBox += things[index].name;
    currentComboBox += ' ';
    currentComboBox += things[index].model;
    currentComboBox += ' ';
    currentComboBox += QString::number(things[index].cost);
    currentComboBox += ' ';
    currentComboBox += QString::number(things[index].count);
    if (i != 0)
    ui->lineEdit_2->setText(currentComboBox);
}


void MainWindow::on_pushButton_4_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "Open a File", "D://");
    if(filename.isEmpty())
    {
       QMessageBox::warning(this, "Warning","File is empty");
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    QTextStream in(&file);
    QString test = in.readLine();
    qDebug() << test;
    if(test.size() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty");
    }
    file.close();
    loadFromFile();
    textOutput();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString filenameNew = QFileDialog::getSaveFileName(this , tr("Save a file"), "", tr("Text file (*.txt)"));
    if (filename.isEmpty())
          return;
    else
    {
        QFile file(filenameNew);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        if (filenameNew != filename)
        {
            qDebug() << "Test";
            filename = filenameNew;
            std::fstream ourfile;
            ourfile.open(filename.toStdString(), std::ios::out);
            for (int j = 0; j < i; j++)
                ourfile << thingsLines[j].toStdString() << "\r\n";
        }
        else
        {
            std::fstream ourfile;
            ourfile.open(filename.toStdString(), std::ios::out);
            ourfile << "Group 1412 name model 4124 532";
        }

    }
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    showThings();
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    searchName();
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Enter in relevant fields info");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    searchModel();
}


void MainWindow::on_pushButton_9_clicked()
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    sortByCode();
}


void MainWindow::on_pushButton_10_clicked()
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    sortByName();
}

void MainWindow::on_pushButton_11_clicked()
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    file.close();
    sortByCost();
}

