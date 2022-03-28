#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 750);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Date" << "Code" << "City" << "Time" << "Tariff" << "TelNumberThisCity" << "TelNumberSubscriber");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete listOfConv;
}

void MainWindow::calculateMonths()
{
    if(IsLeap() == true)
        months[2] = 29;
    else
        months[2] = 28;
    months[1] = 31;
    months[3] = 31;
    months[4] = 30;
    months[5] = 31;
    months[6] = 30;
    months[7] = 31;
    months[8] = 31;
    months[9] = 30;
    months[10] = 31;
    months[11] = 30;
    months[12] = 31;
}

bool MainWindow::IsLeap()
{
    if (!(year % 4))
    {
        if (!(year % 100))
        {
            if (!(year % 400))
                return true;
            else
                return false;
        }
        else
            return true;
     }
     else
        return false;
}

void MainWindow::divideAndAdd(QString& line)
{
    int count = 1;
    QString tempCode;
    QString tempCity;
    QString tempTime;
    QString tempTariff;
    QString tempTelNumberThisCity;
    QString tempTelNumberSubscriber;
    for (int i = 11; i < line.size(); i++)
    {
        if (count == 1 && line.at(i) != ' ')
        tempCode += line.at(i);
        if (count == 2 && line.at(i) != ' ')
        tempCity += line.at(i);
        if (count == 3 && line.at(i) != ' ')
        tempTime += line.at(i);
        if (count == 4 && line.at(i) != ' ')
        tempTariff += line.at(i);
        if (count == 5 && line.at(i) != ' ')
        tempTelNumberThisCity += line.at(i);
        if (count == 6 && line.at(i) != ' ')
        tempTelNumberSubscriber += line.at(i);
        if (line.at(i) == ' ')  count++;
    }
    QString tempDate = QString::number(day) + '.' + QString::number(month) + '.' + QString::number(year);
    if (day <= 9) tempDate.insert(0, '0');
    if (month <= 9) tempDate.insert(3, '0');
    if (QString::number(year).size() == 1)
    {
        tempDate.insert(6, '0');
        tempDate.insert(7, '0');
        tempDate.insert(8, '0');
    }
    else if (QString::number(year).size() == 2)
    {
        tempDate.insert(6, '0');
        tempDate.insert(7, '0');
    }
    else if (QString::number(year).size() == 3)
    {
        tempDate.insert(6, '0');
    }

    listOfConv->addToEnd(tempDate, tempCode, tempCity, tempTime, tempTariff, tempTelNumberThisCity, tempTelNumberSubscriber);
}

bool MainWindow::checkDate(QString &line, bool mode)
{
    if (line.size() != 10)  // mode just only for correct messages
    if (line[10] != ' ')
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Smth Incorrect in your file.");
        return false;
    }
    if(line[0] < 48 || line[0] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[1] < 48 || line[1] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[2] != '.')
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[3] < 48 || line[3] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[4] < 48 || line[4] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[5] != '.')
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[6] < 48 || line[6] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line.at(7) < 48 || line.at(7) > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[8] < 48 || line[8] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    if(line[9] < 48 || line[9] > 57)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file.");
        return false;
    }
    int yearCheck = 1000 * line[6].digitValue() + 100 * line[7].digitValue() + 10 * line[8].digitValue() + line[9].digitValue();
    if (yearCheck == 0)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file. Year can't be 0.");
        return false;
    }
    year = yearCheck;   // year is ready
    int monthCheck = 10 * line[3].digitValue() + line[4].digitValue();
    if(monthCheck > 12 || monthCheck == 0)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file. Month must be <= 12 and >0");
        return false;
    }
    month = monthCheck; // month is ready
    int dayCheck = 10 * line[0].digitValue() + line[1].digitValue();
    day = dayCheck;
    calculateMonths();
    if(dayCheck > months[monthCheck] || dayCheck == 0)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Number of day must be possible.");
        return false;
    }
    return true;
}

bool MainWindow::test(QString& line, bool mode)
{
    if(!checkDate(line)) return false;  // DATE
    int i = 11;
    if (!mode)  // mode just for correct messages
    if (line.size() <= 30)
    {
        QMessageBox::warning(this, "Warning","Incorrect data in the file.");
        return false;
    }
    for (; i < line.size(); i++)    // CODE
    {
        if ((i + 1) == line.size())
        {
            QMessageBox::warning(this, "Warning","Incorrect data in the file.");
            return false;
        }
        if (i != 11 && line.at(i) == ' ')
        {
            i = i + 1;
            break;    // code is ready
        }
        if(!(line.at(i) >= 48 && line.at(i) <= 57))
        {
            QMessageBox::warning(this, "Warning","Incorrect code.");
            return false;
        }
    }
    int count = 0;  // for situation if user entered only 1 letter as a city name.
    for (; i < line.size(); i++)    // CITY
    {
        if ((i + 1) == line.size())
        {
            QMessageBox::warning(this, "Warning","Incorrect data in the file.");
            return false;
        }
        if (count >= 2 && line.at(i) == ' ')
        {
            i = i + 1;
            break;
        }
        if (line.at(i) == ' ' && count < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect city. Must be at least 2 letters.");
            return false;
        }
        if (count == 0)
        if (!(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect city. Must start with a capital letter.");
            return false;
        }
        if (count != 0)
        if (!(line.at(i) >= 97 && line.at(i) <= 122))
        {
            QMessageBox::warning(this, "Warning","Incorrect city.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // TIME
    {
        if ((i + 1) == line.size())
        {
            QMessageBox::warning(this, "Warning","Incorrect data in the file.");
            return false;
        }
        if (count == 0 && line.at(i) == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect time. At least 1 number.");
            return false;
        }
        if (count > 0 && line.at(i) == ' ')
        {
            i = i + 1;
            break;
        }
        if(!(line.at(i) >= 48 && line.at(i) <= 57))
        {
            QMessageBox::warning(this, "Warning","Incorrect time.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // TARIFF
    {
        if ((i + 1) == line.size())
        {
            QMessageBox::warning(this, "Warning","Incorrect data in the file.");
            return false;
        }
        if (count >= 1 && line.at(i) == ' ')
        {
            i = i + 1;
            break;
        }
        if (!(line.at(i) >= 97 && line.at(i) <= 122) && !(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect tariff. Must be only letters.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // TelNumberThisCity
    {
        if ((i + 1) == line.size())
        {
            QMessageBox::warning(this, "Warning","Incorrect tel input.");
            return false;
        }
        if (count >= 6 && line.at(i) == ' ' )
        {
            i = i + 1;
            break;
        }
        if (count < 6 && line.at(i) == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect TelNumberThisCity. Must be 7 digits.");
            return false;
        }
        if (!(line.at(i) >= 48 && line.at(i) <= 57))
        {
            QMessageBox::warning(this, "Warning","Incorrect TelNumberThisCity. Must be only digits.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // TelNumberSubscriber
    {
        if (count >= 6 && (line.at(i) == ' ' || (i + 1) == line.size()))
            break;
        if (count < 6 && (line.at(i) == ' ' || (i + 1) == line.size()))
        {
            QMessageBox::warning(this, "Warning","Incorrect TelNumberSubscriber. Must be 7 digits.");
            return false;
        }
        if (!(line.at(i) >= 48 && line.at(i) <= 57))
        {
            QMessageBox::warning(this, "Warning","Incorrect TelNumberSubscriber. Must be only digits.");
            return false;
        }
        count++;
    }
    return true;
}

void MainWindow::loadFromFile()
{
    QFile file(filename);
    QTextStream in(&file);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File can't be opened.");
        ui->tableWidget->clear();
        file.close();
        checkFile = false;
        return;
    }
    if (checkFile)  listOfConv->delAll();   // if the same file
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if (!test(line, false))
        {
            file.close();
            QMessageBox::warning(this, "Warning","File is unused. Change data in the file. You can use empty or not empty .txt file.");
            ui->tableWidget->clear();
            listOfConv->delAll();
            checkFile = false;
            ui->comboBox->clear();
            ui->comboBox_2->clear();
            ui->comboBox_5->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_codeAdd->clear();
            ui->lineEdit_cityAdd->clear();
            ui->lineEdit_timeAdd->clear();
            ui->lineEdit_tariffAdd->clear();
            ui->lineEdit_telThisCityAdd->clear();
            ui->lineEdit_telSubAdd->clear();
            ui->lineEdit->setInputMask("");
            return;
        }
        checkFile = true;
        divideAndAdd(line);
    }
    file.close();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox->addItem(QString::number(i + 1));
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox_2->addItem(QString::number(i + 1));
    ui->comboBox_5->clear();
    if (listOfConv->getCount() > 0)
    {
        ui->comboBox_5->addItem("date");
        ui->comboBox_5->addItem("code");
        ui->comboBox_5->addItem("city");
        ui->comboBox_5->addItem("time");
        ui->comboBox_5->addItem("tariff");
        ui->comboBox_5->addItem("telThisCity");
        ui->comboBox_5->addItem("telSub");
    }
}

void MainWindow::deleteFromFile()
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Warning","File wasn't opened!");
        return;
    }
    QTextStream out(&file);
    for (int j = 0; j < listOfConv->getCount(); j++)    // the list is already ready(without element, that was deleted)
    {
        QString line = listOfConv->getElem(j + 1)->date;
        line += ' ' + listOfConv->getElem(j + 1)->code;
        line += ' ' + listOfConv->getElem(j + 1)->city;
        line += ' ' + listOfConv->getElem(j + 1)->time;
        line += ' ' + listOfConv->getElem(j + 1)->tariff;
        line += ' ' + listOfConv->getElem(j + 1)->telNumThisCity;
        line += ' ' + listOfConv->getElem(j + 1)->telNumSubscriber;
        out << line << "\r\n";
    }

    file.close();
}

void MainWindow::saveToFileAndAdd(QString& line)
{
    QFile file(filename);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "File wasn't opened!(saveToFile)";
        return;
    }
    if (listOfConv->getCount() == 1)    // divideAndAdd and in result count = 1, then it is first line in file.
        out << line;
    else
        out << "\r\n" << line;
    file.close();
}

void MainWindow::textOutput()
{
    ui->tableWidget->setRowCount(listOfConv->getCount());
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Date" << "Code" << "City" << "Time" << "Tariff" << "TelNumberThisCity" << "TelNumberSubscriber");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfConv->getElem(row + 1)->date));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfConv->getElem(row + 1)->code));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfConv->getElem(row + 1)->city));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfConv->getElem(row + 1)->time));
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfConv->getElem(row + 1)->tariff));
        ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfConv->getElem(row + 1)->telNumThisCity));
        ui->tableWidget->setItem(row,6,new QTableWidgetItem(listOfConv->getElem(row + 1)->telNumSubscriber));
    }
}

void MainWindow::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, "Open a File", "D://");
    if(filename.isEmpty())
    {
        QMessageBox::warning(this, "Warning","No such file.");
        checkFile = false;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        ui->tableWidget->clear();
        listOfConv->delAll();
        textOutput();
        checkFile = false;
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->comboBox_5->clear();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_codeAdd->clear();
        ui->lineEdit_cityAdd->clear();
        ui->lineEdit_timeAdd->clear();
        ui->lineEdit_tariffAdd->clear();
        ui->lineEdit_telThisCityAdd->clear();
        ui->lineEdit_telSubAdd->clear();
        ui->lineEdit->setInputMask("");
        return;
    }
    checkFile = true;
    QTextStream in(&file);
    QString test = in.readLine();
    if(test.size() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty(or first line is clear).");
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_codeAdd->clear();
        ui->lineEdit_cityAdd->clear();
        ui->lineEdit_timeAdd->clear();
        ui->lineEdit_tariffAdd->clear();
        ui->lineEdit_telThisCityAdd->clear();
        ui->lineEdit_telSubAdd->clear();
        ui->lineEdit->setInputMask("");
    }
    file.close();
    loadFromFile();
    if (listOfConv->getCount() > 1)
    quicksort(listOfConv, 1, listOfConv->getCount());
    fileReset();
    textOutput();
}

void MainWindow::on_pushButton_5_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    else if (listOfConv->getCount() == 0)
    {
        QMessageBox::warning(this, "Warning","File(and list) is empty.");
        return;
    }
    textOutput();
}


void MainWindow::on_add_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","Error. File isn't opened.");
        return;
    }
    QString line;
    QString date = ui->dateEdit->text();
    if(checkDate(date, true))
        line += date;
    else
    {
        QMessageBox::warning(this, "Warning","Incorrect date to add.");
        return;
    }
    if (ui->lineEdit_cityAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big city name");
        return;
    }
    if (ui->lineEdit_tariffAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big tariff name");
        return;
    }
    line += ' ' + ui->lineEdit_codeAdd->text();
    line += ' ' + ui->lineEdit_cityAdd->text();
    line += ' ' + ui->lineEdit_timeAdd->text();
    line += ' ' + ui->lineEdit_tariffAdd->text();
    line += ' ' + ui->lineEdit_telThisCityAdd->text();
    line += ' ' + ui->lineEdit_telSubAdd->text();
    if(test(line, true))
    {
        divideAndAdd(line);
        saveToFileAndAdd(line);
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();
        textOutput();
    }
    else
        QMessageBox::warning(this, "Warning","Smth incorrect in your input. Code: at least 1 digit; City: 1-st capital letter and at least 2 letters; "
                                             "Time: only digits; Tariff: only letters, at least 1 letter; TelNumberThisCity: only 7 digits;"
                                             " TelNumberSubscriber: only 7 digits;");
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox->addItem(QString::number(i + 1));
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox_2->addItem(QString::number(i + 1));
}


void MainWindow::on_deleteElem_Button_clicked()
{
    if (checkFile)
    {
        if (listOfConv->getCount() == 0)
        {
            QMessageBox::warning(this, "Warning","Error. File is empty.");
            return;
        }
        listOfConv->del(ui->comboBox_2->currentText().toInt());
        deleteFromFile();
        textOutput();

        ui->comboBox->clear();
        ui->comboBox_2->clear();
        for (int i = 0; i < listOfConv->getCount(); i++)
        ui->comboBox->addItem(QString::number(i + 1));
        for (int i = 0; i < listOfConv->getCount(); i++)
        ui->comboBox_2->addItem(QString::number(i + 1));
    }
    else
        QMessageBox::warning(this, "Warning","Error. File isn't opened.");
}

void MainWindow::on_deleteConvWithTel_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","Error. File isn't opened.");
        return;
    }
    QString line = ui->lineEdit_2->text();
    bool found = false;
    for (int i = 1; i <= listOfConv->getCount(); i++)
        if (listOfConv->getElem(i)->telNumThisCity == line)
        {
            listOfConv->del(i);
            found = true;
        }
    if (!found)
    {
        QMessageBox::warning(this, "Warning","Error. Tel number haven't found.");
        return;
    }
    ui->tableWidget->clear();
    deleteFromFile();
    textOutput();

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox->addItem(QString::number(i + 1));
    for (int i = 0; i < listOfConv->getCount(); i++)
    ui->comboBox_2->addItem(QString::number(i + 1));
}


void MainWindow::on_searchCity_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString line = ui->lineEdit_4->text();
    if (line.size() < 2)
    {
        QMessageBox::warning(this, "Warning","Incorrect city. Must be at least 2 letters without spaces.");
        return;
    }
    for (int i = 0; i < line.size(); i++)    // CITY check if letters
    {
        if (i >= 2 && line.at(i) == ' ')
        {
            for (int j = i + 1; j < line.size(); j++)
                if (line[j] != ' ')
                {
                    QMessageBox::warning(this, "Warning","Incorrect city. Must be at least 2 letters without spaces.");
                    return;
                }
            line.remove(i, line.size() - i);
            break;
        }
        if (line.at(i) == ' ' && i < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect city. Must be at least 2 letters without spaces.");
            return;
        }
        if (!(line[0] >= 65 && line[0] <= 90))
        {
            QMessageBox::warning(this, "Warning","Error. Must start with a capital letter.");
            return;
        }
        if(i != 0)
            if (!(line[i] >= 97 && line[i] <= 122))
            {
                QMessageBox::warning(this, "Warning","Error. Incorrect input.");
                return;
            }
    }
    int found = 0;
    for (int i = 1; i <= listOfConv->getCount(); i++)
        if (listOfConv->getElem(i)->city == line)
            found++;
    if (found)  ui->tableWidget->clear();
    else
    {
        QMessageBox::warning(this, "Warning","No such city in the list.");
        return;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Date" << "Code" << "City" << "Time" << "Tariff" << "TelNumberThisCity" << "TelNumberSubscriber");
    ui->tableWidget->setRowCount(found);
    int row = 0;
    for (int i = 1; i <= listOfConv->getCount(); i++)
        if (listOfConv->getElem(i)->city == line)
        {
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfConv->getElem(i)->date));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfConv->getElem(i)->code));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfConv->getElem(i)->city));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfConv->getElem(i)->time));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfConv->getElem(i)->tariff));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfConv->getElem(i)->telNumThisCity));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(listOfConv->getElem(i)->telNumSubscriber));
            row++;
        }
}

void MainWindow::on_searchTel_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString line = ui->lineEdit_3->text();
    if (line.size() != 7)
    {
        QMessageBox::warning(this, "Warning","Incorrect TelNumberSubscriber. Must be 7 digits.");
        return;
    }
    int found = 0;
    for (int i = 1; i <= listOfConv->getCount(); i++)
        if (listOfConv->getElem(i)->telNumSubscriber == line)
            found++;
    if (found)  ui->tableWidget->clear();
    else
    {
        QMessageBox::warning(this, "Warning","No such TelNumberSubscriber in the list.");
        return;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Date" << "Code" << "City" << "Time" << "Tariff" << "TelNumberThisCity" << "TelNumberSubscriber");
    ui->tableWidget->setRowCount(found);
    int row = 0;
    for (int i = 1; i <= listOfConv->getCount(); i++)
        if (listOfConv->getElem(i)->telNumSubscriber == line)
        {
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfConv->getElem(i)->date));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfConv->getElem(i)->code));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfConv->getElem(i)->city));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfConv->getElem(i)->time));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfConv->getElem(i)->tariff));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfConv->getElem(i)->telNumThisCity));
            ui->tableWidget->setItem(row,6,new QTableWidgetItem(listOfConv->getElem(i)->telNumSubscriber));
            row++;
        }
}

void MainWindow::fileReset()
{
    QFile file(filename);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "File wasn't opened!";
        return;
    }
    for (int i = 1; i <= listOfConv->getCount(); i++)
    {
        QString line = listOfConv->getElem(i)->date;
        line += ' ' + listOfConv->getElem(i)->code;
        line += ' ' + listOfConv->getElem(i)->city;
        line += ' ' + listOfConv->getElem(i)->time;
        line += ' ' + listOfConv->getElem(i)->tariff;
        line += ' ' + listOfConv->getElem(i)->telNumThisCity;
        line += ' ' + listOfConv->getElem(i)->telNumSubscriber;
        if (i == 1)
            out << line;
        else
            out << "\r\n" << line;
    }
    file.close();
}

void MainWindow::on_change_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString line = ui->lineEdit->text();
    if (currTextParam == "date")
    {
        if(!checkDate(line, true))
        {
            QMessageBox::warning(this, "Warning","Incorrect date.");
            ui->lineEdit->clear();
            return;
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->date = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "code")
    {
        if (line.size() == 0)
        {
            QMessageBox::warning(this, "Warning","Incorrect code.");
            ui->lineEdit->clear();
            return;
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->code = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "city")
    {
        if (line.size() < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect city. Must be at least 2 letters. Capital and lowercase.");
            ui->lineEdit->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect city. Too big city name.");
            ui->lineEdit->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
        {
            if (i == 0)
               if (!(line[i] >= 65 && line[i] <= 90))
               {
                   QMessageBox::warning(this, "Warning","Incorrect city. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                   ui->lineEdit->clear();
                   return;
               }
            if (i != 0)
                if (!(line[i] >= 97 && line[i] <= 122))
                {
                    QMessageBox::warning(this, "Warning","Incorrect city. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                    ui->lineEdit->clear();
                    return;
                }
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->city = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "time")
    {
        if (line.size() == 0)
        {
            QMessageBox::warning(this, "Warning","Incorrect time.");
            ui->lineEdit->clear();
            return;
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->time = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "tariff")
    {
        if (line.size() == 0)
        {
            QMessageBox::warning(this, "Warning","Incorrect tariff. Must be at least 1 digit.");
            ui->lineEdit->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect tariff. Too big tariff name.");
            ui->lineEdit->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
            if (!(line[i] >= 65 && line[i] <= 90) && !(line[i] >= 97 && line[i] <= 122))
            {
                QMessageBox::warning(this, "Warning","Incorrect tariff. Must be only letters without spaces anywhere.");
                ui->lineEdit->clear();
                return;
            }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->tariff = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "telThisCity")
    {
        if (line.size() != 7)
        {
            QMessageBox::warning(this, "Warning","Incorrect telNumberThisCity.");
            ui->lineEdit->clear();
            return;
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->telNumThisCity = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "telSub")
    {
        if (line.size() != 7)
        {
            QMessageBox::warning(this, "Warning","Incorrect telNumberSubscriber.");
            ui->lineEdit->clear();
            return;
        }
        // change
        listOfConv->getElem(ui->comboBox->currentText().toInt())->telNumSubscriber = line;
        quicksort(listOfConv, 1, listOfConv->getCount());
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
}


void MainWindow::on_comboBox_5_currentTextChanged(const QString &currText)
{
    if (checkFile)
    {
        if (currText == "date")
        {
            ui->lineEdit->setInputMask("99.99.9999");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->date);
        }
        else if (currText == "code")
        {
            ui->lineEdit->setInputMask("999");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->code);
        }
        else if (currText == "city")
        {
            ui->lineEdit->setInputMask("");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->city);
        }
        else if (currText == "time")
        {
            ui->lineEdit->setInputMask("999");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->time);
        }
        else if (currText == "tariff")
        {
            ui->lineEdit->setInputMask("");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->tariff);
        }
        else if (currText == "telThisCity")
        {
            ui->lineEdit->setInputMask("9999999");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->telNumThisCity);
        }
        else if (currText == "telSub")
        {
            ui->lineEdit->setInputMask("9999999");
            ui->lineEdit->setText(listOfConv->getElem(ui->comboBox->currentText().toInt())->telNumSubscriber);
        }
        currTextParam = currText;
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &currText)
{
    if (checkFile)
    {
        if (currTextParam == "date")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->date);
        else if (currTextParam == "code")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->code);
        else if (currTextParam == "city")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->city);
        else if (currTextParam == "time")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->time);
        else if (currTextParam == "tariff")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->tariff);
        else if (currTextParam == "telThisCity")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->telNumThisCity);
        else if (currTextParam == "telSub")
            ui->lineEdit->setText(listOfConv->getElem(currText.toInt())->telNumSubscriber);
    }
}

void MainWindow::quicksort(DoubleList*& list, int left, int right)
{
    int i, j;
    QChar x;

    i = left; j = right;
    x = list->getElem((left + right) / 2)->city[0];
    do {
       while ((list->getElem(i)->city[0] < x) && (i < right)) i++;
       while ((x < list->getElem(j)->city[0]) && (j > left)) j--;

       if (i <= j)
       {
           QString y;
           y = list->getElem(i)->date;
           list->getElem(i)->date = list->getElem(j)->date;
           list->getElem(j)->date = y;
           y = list->getElem(i)->code;
           list->getElem(i)->code = list->getElem(j)->code;
           list->getElem(j)->code = y;
           y = list->getElem(i)->city;
           list->getElem(i)->city = list->getElem(j)->city;
           list->getElem(j)->city = y;
           y = list->getElem(i)->time;
           list->getElem(i)->time = list->getElem(j)->time;
           list->getElem(j)->time = y;
           y = list->getElem(i)->tariff;
           list->getElem(i)->tariff = list->getElem(j)->tariff;
           list->getElem(j)->tariff = y;
           y = list->getElem(i)->telNumThisCity;
           list->getElem(i)->telNumThisCity = list->getElem(j)->telNumThisCity;
           list->getElem(j)->telNumThisCity = y;
           y = list->getElem(i)->telNumSubscriber;
           list->getElem(i)->telNumSubscriber = list->getElem(j)->telNumSubscriber;
           list->getElem(j)->telNumSubscriber = y;
           i++; j--;
       }
    } while (i <= j);

    if (left < j) quicksort(list, left, j);
    if (i < right) quicksort(list, i, right);
}
