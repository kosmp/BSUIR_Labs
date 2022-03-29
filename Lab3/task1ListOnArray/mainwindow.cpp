#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 800);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Patronymic" << "DepartmentNumber" << "PosAtWork" << "DateStart");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    realDate();
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

MainWindow::~MainWindow()
{
    delete ui;
    delete listOfWorkers;
}

bool MainWindow::IsLeap(int year)
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
    yearBuff = yearCheck;   // year is ready
    int monthCheck = 10 * line[3].digitValue() + line[4].digitValue();
    if(monthCheck > 12 || monthCheck == 0)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Incorrect date in your file. Month must be <= 12 and >0");
        return false;
    }
    monthBuff = monthCheck; // month is ready
    int dayCheck = 10 * line[0].digitValue() + line[1].digitValue();
    dayBuff = dayCheck;

    if(IsLeap(yearBuff) == true)
        months[2] = 29;
    else
        months[2] = 28;

    if(dayCheck > months[monthCheck] || dayCheck == 0)
    {
        if (!mode)
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Number of day must be possible.");
        return false;
    }

    if (dayBuff > realDay && monthBuff == realMonth && yearBuff == realYear)
    {
        QMessageBox::warning(this, "Warning", "Date is bigger than current date.");
        return false;
    }
    else if (monthBuff > realMonth && yearBuff == realYear)
    {
        QMessageBox::warning(this, "Warning", "Date is bigger than current date.");
        return false;
    }
    else if (yearBuff > realYear)
    {
        QMessageBox::warning(this, "Warning", "Date is bigger than current date.");
        return false;
    }

    return true;
}

bool MainWindow::test(QString& line, bool mode)
{
    if(!checkDate(line)) return false;  // DATE
    int i = 11;
    if (!mode)  // mode just for correct messages
    if (line.size() < 23)
    {
        QMessageBox::warning(this, "Warning","Incorrect data in the file.");
        return false;
    }
    for (int j = 11; j < line.size(); j++)
    {
        if (j + 1 != line.size())
            if (line[j] == ' ' && line[j + 1] == ' ')
            {
                if (!mode)
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                return false;
            }
    }
    int count = 0;  // for situation if user entered only 1 letter as a city name.
    for (; i < line.size(); i++)    // NAME
    {
        if ((i + 1) == line.size())
        {
            if (!mode)
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
            QMessageBox::warning(this, "Warning","Incorrect name. Must be at least 2 letters.");
            return false;
        }
        if (count == 0)
        if (!(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect name. Must start with a capital letter.");
            return false;
        }
        if (count != 0)
        if (!(line.at(i) >= 97 && line.at(i) <= 122))
        {
            QMessageBox::warning(this, "Warning","Incorrect name.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // SURNAME
    {
        if ((i + 1) == line.size())
        {
            if (!mode)
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
            QMessageBox::warning(this, "Warning","Incorrect surname. Must be at least 2 letters.");
            return false;
        }
        if (count == 0)
        if (!(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect surname. Must start with a capital letter.");
            return false;
        }
        if (count != 0)
        if (!(line.at(i) >= 97 && line.at(i) <= 122))
        {
            QMessageBox::warning(this, "Warning","Incorrect surname.");
            return false;
        }
        count++;
    }
    count = 0;
    for (; i < line.size(); i++)    // PATRONYMIC
    {
        if ((i + 1) == line.size())
        {
            if (!mode)
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
            QMessageBox::warning(this, "Warning","Incorrect patronymic. Must be at least 2 letters.");
            return false;
        }
        if (count == 0)
        if (!(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic. Must start with a capital letter.");
            return false;
        }
        if (count != 0)
        if (!(line.at(i) >= 97 && line.at(i) <= 122))
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic.");
            return false;
        }
        count++;
    }
    for (; i < line.size(); i++)    // DEPARTMENTNUMBER
    {
        if ((i + 1) == line.size())
        {
            if (!mode)
                QMessageBox::warning(this, "Warning","Incorrect data in the file.");
            return false;
        }
        if (i != 11 && line.at(i) == ' ')
        {
            i = i + 1;
            break;    // department is ready
        }
        if(!(line.at(i) >= 48 && line.at(i) <= 57))
        {
            QMessageBox::warning(this, "Warning","Incorrect department number.");
            return false;
        }
    }
    count = 0;
    for (; i < line.size(); i++)    // POSATWORK
    {
        if (count >= 1 && line.at(i) == ' ')
            break;
        if (!(line.at(i) >= 97 && line.at(i) <= 122) && !(line.at(i) >= 65 && line.at(i) <= 90))
        {
            QMessageBox::warning(this, "Warning","Incorrect posAtWork. Must be only letters.");
            return false;
        }
        count++;
    }
    if (count == 0)
    {
        QMessageBox::warning(this, "Warning","Incorrect input.");
        return false;
    }
    return true;
}

void MainWindow::divideAndAdd(QString& line)
{
    int count = 1;
    QString tempName;
    QString tempSurname;
    QString tempPatronymic;
    QString tempDepartmentNumber;
    QString tempPosAtWork;
    for (int i = 11; i < line.size(); i++)
    {
        if (count == 1 && line.at(i) != ' ')
        tempName += line.at(i);
        if (count == 2 && line.at(i) != ' ')
        tempSurname += line.at(i);
        if (count == 3 && line.at(i) != ' ')
        tempPatronymic += line.at(i);
        if (count == 4 && line.at(i) != ' ')
        tempDepartmentNumber += line.at(i);
        if (count == 5 && line.at(i) != ' ')
        tempPosAtWork += line.at(i);
        if (line.at(i) == ' ')  count++;
    }
    QString tempDate = QString::number(dayBuff) + '.' + QString::number(monthBuff) + '.' + QString::number(yearBuff);
    if (dayBuff <= 9) tempDate.insert(0, '0');
    if (monthBuff <= 9) tempDate.insert(3, '0');
    if (QString::number(yearBuff).size() == 1)
    {
        tempDate.insert(6, '0');
        tempDate.insert(7, '0');
        tempDate.insert(8, '0');
    }
    else if (QString::number(yearBuff).size() == 2)
    {
        tempDate.insert(6, '0');
        tempDate.insert(7, '0');
    }
    else if (QString::number(yearBuff).size() == 3)
    {
        tempDate.insert(6, '0');
    }

    listOfWorkers->addToEnd(tempName, tempSurname, tempPatronymic, tempDepartmentNumber, tempPosAtWork, tempDate);
}

bool MainWindow::loadFromFile()
{
    QFile file(filename);
    QTextStream in(&file);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Warning","File can't be opened.");
        ui->tableWidget->clear();
        file.close();
        checkFile = false;
        return false;
    }
    if (checkFile)  listOfWorkers->delAll();   // if the same file
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if (!test(line, false))
        {
            file.close();
            QMessageBox::warning(this, "Warning","File is unused. Change data in the file. You can use empty or not empty .txt file.");
            ui->tableWidget->clear();
            listOfWorkers->delAll();
            checkFile = false;
            ui->comboBox->clear();
            ui->comboBox_2->clear();
            ui->comboBox_5->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_nameAdd->clear();
            ui->lineEdit_surnameAdd->clear();
            ui->lineEdit_patronymicAdd->clear();
            ui->lineEdit_departmentNumAdd->clear();
            ui->lineEdit_posAtWorkAdd->clear();
            ui->lineEdit_4->setInputMask("");
            return false;
        }
        checkFile = true;
        divideAndAdd(line);     // after test, where checkDate was called, dayBuff, monthBuff, yearBuff will be correct
    }
    file.close();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    ui->comboBox_2->addItem(QString::number(i + 1));
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    ui->comboBox->addItem(QString::number(i + 1));
    ui->comboBox_5->clear();
    if (listOfWorkers->getCount() > 0)
    {
        ui->comboBox_5->addItem("name");
        ui->comboBox_5->addItem("surname");
        ui->comboBox_5->addItem("patronymic");
        ui->comboBox_5->addItem("departmentNum");
        ui->comboBox_5->addItem("posAtWork");
        ui->comboBox_5->addItem("dateStart");
    }
    return true;
}

void MainWindow::fileReset()
{
    QFile file(filename);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "File wasn't opened!(saveToFile)";
        return;
    }
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    {
        QString line = listOfWorkers->getElem(i)->dateStart;
        line += ' ' + listOfWorkers->getElem(i)->name;
        line += ' ' + listOfWorkers->getElem(i)->surname;
        line += ' ' + listOfWorkers->getElem(i)->patronymic;
        line += ' ' + listOfWorkers->getElem(i)->departmentNum;
        line += ' ' + listOfWorkers->getElem(i)->posAtWork;
        if (i == 0)
            out << line;
        else
            out << "\r\n" << line;
    }
    file.close();
}

void MainWindow::textOutput()
{
    ui->tableWidget->setRowCount(listOfWorkers->getCount());
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Patronymic" << "DepartmentNumber" << "PosAtWork" << "DateStart");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfWorkers->getElem(row)->name));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfWorkers->getElem(row)->surname));
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfWorkers->getElem(row)->patronymic));
        ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfWorkers->getElem(row)->departmentNum));
        ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfWorkers->getElem(row)->posAtWork));
        ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfWorkers->getElem(row)->dateStart));
    }
}

void MainWindow::on_pushButton_openFile_clicked()
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
        listOfWorkers->delAll();
        textOutput();
        checkFile = false;
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        ui->comboBox_5->clear();
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_nameAdd->clear();
        ui->lineEdit_surnameAdd->clear();
        ui->lineEdit_patronymicAdd->clear();
        ui->lineEdit_departmentNumAdd->clear();
        ui->lineEdit_posAtWorkAdd->clear();
        ui->lineEdit_4->setInputMask("");
        return;
    }
    checkFile = true;
    QTextStream in(&file);
    QString test = in.readLine();
    if(test.size() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty(or first line is clear).");
    }
    file.close();
    if (loadFromFile()) // 'if' so as not to delete data from incorrect file
    {
        if (listOfWorkers->getCount() > 30)
        {
            QMessageBox::warning(this, "Warning","File is overloaded. Max 30 workers. Change data and try again.");
            ui->tableWidget->clear();
            listOfWorkers->delAll();
            textOutput();
            checkFile = false;
            ui->comboBox_2->clear();
            ui->comboBox->clear();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_nameAdd->clear();
            ui->lineEdit_surnameAdd->clear();
            ui->lineEdit_patronymicAdd->clear();
            ui->lineEdit_departmentNumAdd->clear();
            ui->lineEdit_posAtWorkAdd->clear();
            ui->lineEdit_4->setInputMask("");
            return;
        }
        if (listOfWorkers->getCount() > 1)
            quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();
    }
    textOutput();
}


void MainWindow::on_pushButton_showList_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    else if (listOfWorkers->getCount() == 0)
    {
        QMessageBox::warning(this, "Warning","File(and list) is empty.");
        return;
    }
    textOutput();
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
    if (listOfWorkers->getCount() == 1)    // divideAndAdd and in result count = 1, then it is first line in file.
        out << line;
    else
        out << "\r\n" << line;
    file.close();
}

void MainWindow::on_add_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","Error. File isn't opened.");
        return;
    }
    if (listOfWorkers->getCount() == 30)
    {
        QMessageBox::warning(this, "Warning","File is overloaded. Max 30 workers.");
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
    if (ui->lineEdit_nameAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big name");
        return;
    }
    if (ui->lineEdit_surnameAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big surname");
        return;
    }
    if (ui->lineEdit_patronymicAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big patronymic");
        return;
    }
    if (ui->lineEdit_posAtWorkAdd->text().size() > 30)
    {
        QMessageBox::warning(this, "Warning","Too big posAtWork");
        return;
    }

    QString tempName = ui->lineEdit_nameAdd->text();
    for (int i = 0; i < tempName.size(); i++)
        if (tempName[i] == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect name.");
            return;
        }
    line += ' ' + tempName;

    QString tempSurname = ui->lineEdit_surnameAdd->text();
    for (int i = 0; i < tempSurname.size(); i++)
        if (tempSurname[i] == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect surname.");
            return;
        }
    line += ' ' + tempSurname;

    QString tempPatronymic = ui->lineEdit_patronymicAdd->text();
    for (int i = 0; i < tempPatronymic.size(); i++)
        if (tempPatronymic[i] == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic.");
            return;
        }
    line += ' ' + tempPatronymic;

    line += ' ' + ui->lineEdit_departmentNumAdd->text();

    QString tempPosAtWork = ui->lineEdit_posAtWorkAdd->text();
    for (int i = 0; i < tempPosAtWork.size(); i++)
        if (tempPosAtWork[i] == ' ')
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic.");
            return;
        }
    line += ' ' + tempPosAtWork;
    if(test(line, true))
    {
        divideAndAdd(line);     // after test, where checkDate was called, dayBuff, monthBuff, yearBuff will be correct
        saveToFileAndAdd(line);
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();
        textOutput();
    }
    else
    {
        QMessageBox::warning(this, "Warning","Smth incorrect in your input. Name, surname, patronymic: 1-st capital letter and at least 2 letters; "
                                             "Department number: only digits (max 3); Position at work: only letters, at least 1 letter;");
        return;
    }
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    ui->comboBox->addItem(QString::number(i + 1));
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    ui->comboBox_2->addItem(QString::number(i + 1));

    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("name");
    ui->comboBox_5->addItem("surname");
    ui->comboBox_5->addItem("patronymic");
    ui->comboBox_5->addItem("departmentNum");
    ui->comboBox_5->addItem("posAtWork");
    ui->comboBox_5->addItem("dateStart");
}


void MainWindow::on_searchSurname_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString line = ui->lineEdit->text();
    if (line.size() < 2)
    {
        QMessageBox::warning(this, "Warning","Incorrect surname. Must be at least 2 letters without spaces.");
        return;
    }
    for (int i = 0; i < line.size(); i++)    // SURNAME check if letters
    {
        if (i >= 2 && line.at(i) == ' ')
        {
            for (int j = i + 1; j < line.size(); j++)
                if (line[j] != ' ')
                {
                    QMessageBox::warning(this, "Warning","Incorrect surname. Must be at least 2 letters without spaces.");
                    return;
                }
            line.remove(i, line.size() - i);
            break;
        }
        if (line.at(i) == ' ' && i < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect surname. Must be at least 2 letters without spaces.");
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
    for (int i = 0; i < listOfWorkers->getCount(); i++)
        if (listOfWorkers->getElem(i)->surname == line)
            found++;
    if (found)  ui->tableWidget->clear();
    else
    {
        QMessageBox::warning(this, "Warning","No such surname in the list.");
        return;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Patronymic" << "DepartmentNumber" << "PosAtWork" << "DateStart");
    ui->tableWidget->setRowCount(found);
    int row = 0;
    for (int i = 0; i < listOfWorkers->getCount(); i++)
        if (listOfWorkers->getElem(i)->surname == line)
        {
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfWorkers->getElem(i)->name));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfWorkers->getElem(i)->surname));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfWorkers->getElem(i)->patronymic));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfWorkers->getElem(i)->departmentNum));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfWorkers->getElem(i)->posAtWork));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfWorkers->getElem(i)->dateStart));
            row++;
        }
}


void MainWindow::on_searchDepartment_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString line = ui->lineEdit_2->text();
    if (line.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Incorrect department number: Must be at least 1 digit(max 3).");
        return;
    }
    int found = 0;
    for (int i = 0; i < listOfWorkers->getCount(); i++)
        if (listOfWorkers->getElem(i)->departmentNum == line)
            found++;
    if (found)  ui->tableWidget->clear();
    else
    {
        QMessageBox::warning(this, "Warning","No such department number in the list.");
        return;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Patronymic" << "DepartmentNumber" << "PosAtWork" << "DateStart");
    ui->tableWidget->setRowCount(found);
    int row = 0;
    for (int i = 0; i < listOfWorkers->getCount(); i++)
        if (listOfWorkers->getElem(i)->departmentNum == line)
        {
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfWorkers->getElem(i)->name));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfWorkers->getElem(i)->surname));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfWorkers->getElem(i)->patronymic));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfWorkers->getElem(i)->departmentNum));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfWorkers->getElem(i)->posAtWork));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfWorkers->getElem(i)->dateStart));
            row++;
        }
}

void MainWindow::realDate()
{
    char * ctime (const time_t * time);
    const time_t tm = time(nullptr);
    char dayCh[3];
    char monthCh[3];
    char yearCh[5];
    strftime(dayCh, 3, "%d", localtime(&tm));
    strftime(monthCh, 3, "%m", localtime(&tm));
    strftime(yearCh, 5, "%Y", localtime(&tm));
    realDay = (dayCh[0] - '0') * 10 + (dayCh[1] - '0');
    realMonth = (monthCh[0] - '0') * 10 + (monthCh[1] - '0');
    realYear = (yearCh[0] - '0') * 1000 + (yearCh[1] - '0') * 100 + (yearCh[2] - '0') * 10 + (yearCh[3] - '0');
}

int MainWindow::duration(int daySt, int monthSt, int yearSt)
{
    int days = 0;
    if (realYear == yearSt && realMonth == monthSt && realDay == daySt) return 0;
    if (realYear > yearSt || (realYear == yearSt && realMonth > monthSt) || (realMonth == monthSt && realDay > daySt))
    {
        bool startMonth = true;
        int j = monthSt;
        int buf = yearSt;
        if (realYear > yearSt)
        {
            for (int i = yearSt; i <= realYear; i++)
            {
                for (; j <= 12; j++)
                {
                    if (j == monthSt && startMonth)
                    {
                        startMonth = false;
                        days += months[monthSt] - daySt;
                    }
                    else if (yearSt == realYear && j == realMonth)
                    {
                        days += realDay;
                        break;
                    }
                    else
                    {
                        days += months[j];
                    }
                }
                yearSt++;
                if(IsLeap(yearSt))
                    months[2] = 29;
                else
                    months[2] = 28;

                j = 1;
            }
            yearSt = buf;
            if(IsLeap(yearSt))
                months[2] = 29;
            else
                months[2] = 28;

            return days;
        }
        else if (realYear == yearSt && realMonth > monthSt)
        {
            for (; j <= realMonth; j++)
            {
                 if (j == monthSt)
                 {
                     days += months[monthSt] - daySt;
                 }
                 else if (j == realMonth)
                 {
                     days += realDay;
                     break;
                 }
                 else
                 {
                     days += months[j];
                 }
            }
            return days;
        }
        else if (realMonth == monthSt && realDay > daySt)
        {
            return realDay - daySt;
        }
    }
}

void MainWindow::on_searchWorkExp_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    QString exp = ui->lineEdit_3->text();
    if (exp.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Incorrect experience. Must be at least 1 digit(max 4).");
    }
    int found = 0;

    for (int i = 0; i < listOfWorkers->getCount(); i++)
    {
        QString date = listOfWorkers->getElem(i)->dateStart;
        QString dayStart = date.at(0);
        dayStart += date.at(1);
        QString monthStart = date.at(3);
        monthStart += date.at(4);
        QString yearStart = date.at(6);
        yearStart += date.at(7);
        yearStart += date.at(8);
        yearStart += date.at(9);
        if (duration(dayStart.toInt(), monthStart.toInt(), yearStart.toInt()) >= exp.toInt())
            found++;
    }
    if (found)  ui->tableWidget->clear();
    else
    {
        QMessageBox::warning(this, "Warning","No such workers in the list.");
        return;
    }
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Surname" << "Patronymic" << "DepartmentNumber" << "PosAtWork" << "DateStart");
    ui->tableWidget->setRowCount(found);
    int row = 0;
    for (int i = 0; i < listOfWorkers->getCount(); i++)
    {
        QString date = listOfWorkers->getElem(i)->dateStart;
        QString dayStart = date.at(0);
        dayStart += date.at(1);
        QString monthStart = date.at(3);
        monthStart += date.at(4);
        QString yearStart = date.at(6);
        yearStart += date.at(7);
        yearStart += date.at(8);
        yearStart += date.at(9);
        if (duration(dayStart.toInt(), monthStart.toInt(), yearStart.toInt()) >= exp.toInt())
        {
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(listOfWorkers->getElem(i)->name));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(listOfWorkers->getElem(i)->surname));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(listOfWorkers->getElem(i)->patronymic));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(listOfWorkers->getElem(i)->departmentNum));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(listOfWorkers->getElem(i)->posAtWork));
            ui->tableWidget->setItem(row,5,new QTableWidgetItem(listOfWorkers->getElem(i)->dateStart));
            row++;
        }
    }
}

void MainWindow::on_delete_Button_clicked()
{
    if (checkFile)
    {
        if (listOfWorkers->getCount() == 0)
        {
            QMessageBox::warning(this, "Warning","Error. File is empty.");
            return;
        }
        listOfWorkers->del(ui->comboBox->currentText().toInt() - 1);
        fileReset();
        textOutput();

        ui->comboBox->clear();
        for (int i = 1; i <= listOfWorkers->getCount(); i++)
        ui->comboBox->addItem(QString::number(i));
        ui->comboBox_2->clear();
        for (int i = 1; i <= listOfWorkers->getCount(); i++)
            ui->comboBox_2->addItem(QString::number(i));
    }
    else
        QMessageBox::warning(this, "Warning","Error. File isn't opened.");
}

void MainWindow::quicksort(DoubleList*& list, int left, int right)
{
    int i, j;
    QChar x;

    i = left; j = right;
    x = list->getElem((left + right) / 2)->name[0];
    do {
       while ((list->getElem(i)->name[0] < x) && (i < right)) i++;
       while ((x < list->getElem(j)->name[0]) && (j > left)) j--;

       if (i <= j)
       {
           QString y;
           y = list->getElem(i)->dateStart;
           list->getElem(i)->dateStart = list->getElem(j)->dateStart;
           list->getElem(j)->dateStart = y;
           y = list->getElem(i)->name;
           list->getElem(i)->name = list->getElem(j)->name;
           list->getElem(j)->name = y;
           y = list->getElem(i)->surname;
           list->getElem(i)->surname = list->getElem(j)->surname;
           list->getElem(j)->surname = y;
           y = list->getElem(i)->patronymic;
           list->getElem(i)->patronymic = list->getElem(j)->patronymic;
           list->getElem(j)->patronymic = y;
           y = list->getElem(i)->departmentNum;
           list->getElem(i)->departmentNum = list->getElem(j)->departmentNum;
           list->getElem(j)->departmentNum = y;
           y = list->getElem(i)->posAtWork;
           list->getElem(i)->posAtWork = list->getElem(j)->posAtWork;
           list->getElem(j)->posAtWork = y;
           i++; j--;
       }
    } while (i <= j);

    if (left < j) quicksort(list, left, j);
    if (i < right) quicksort(list, i, right);
}

void MainWindow::on_change_Button_clicked()
{
    if (!checkFile)
    {
        QMessageBox::warning(this, "Warning","File isn't opened.");
        return;
    }
    if (listOfWorkers->getCount() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty.");
        ui->lineEdit_4->clear();
        return;
    }
    QString line = ui->lineEdit_4->text();
    if (currTextParam == "dateStart")
    {
        if(!checkDate(line, true))
        {
            QMessageBox::warning(this, "Warning","Incorrect date.");
            ui->lineEdit_4->clear();
            return;
        }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->dateStart = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    if (currTextParam == "name")
    {
        if (line.size() < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect name. Must be at least 2 letters. Capital and lowercase.");
            ui->lineEdit_4->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect name. Too big name.");
            ui->lineEdit_4->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
        {
            if (i == 0)
               if (!(line[i] >= 65 && line[i] <= 90))
               {
                   QMessageBox::warning(this, "Warning","Incorrect name. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                   ui->lineEdit_4->clear();
                   return;
               }
            if (i != 0)
                if (!(line[i] >= 97 && line[i] <= 122))
                {
                    QMessageBox::warning(this, "Warning","Incorrect name. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                    ui->lineEdit_4->clear();
                    return;
                }
        }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->name = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "surname")
    {
        if (line.size() < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect surname. Must be at least 2 letters. Capital and lowercase.");
            ui->lineEdit_4->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect surname. Too big surname.");
            ui->lineEdit_4->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
        {
            if (i == 0)
               if (!(line[i] >= 65 && line[i] <= 90))
               {
                   QMessageBox::warning(this, "Warning","Incorrect surname. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                   ui->lineEdit_4->clear();
                   return;
               }
            if (i != 0)
                if (!(line[i] >= 97 && line[i] <= 122))
                {
                    QMessageBox::warning(this, "Warning","Incorrect surname. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                    ui->lineEdit_4->clear();
                    return;
                }
        }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->surname = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "patronymic")
    {
        if (line.size() < 2)
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic. Must be at least 2 letters. Capital and lowercase.");
            ui->lineEdit_4->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect patronymic. Too big patronymic.");
            ui->lineEdit_4->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
        {
            if (i == 0)
               if (!(line[i] >= 65 && line[i] <= 90))
               {
                   QMessageBox::warning(this, "Warning","Incorrect patronymic. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                   ui->lineEdit_4->clear();
                   return;
               }
            if (i != 0)
                if (!(line[i] >= 97 && line[i] <= 122))
                {
                    QMessageBox::warning(this, "Warning","Incorrect patronymic. Must be only letters without spaces anywhere. With 1-st capital letter. Other - lowercase.");
                    ui->lineEdit_4->clear();
                    return;
                }
        }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->patronymic = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "departmentNum")
    {
        if (line.size() == 0)
        {
            QMessageBox::warning(this, "Warning","Incorrect departmentNum.");
            ui->lineEdit_4->clear();
            return;
        }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->departmentNum = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
    else if (currTextParam == "posAtWork")
    {
        if (line.size() == 0)
        {
            QMessageBox::warning(this, "Warning","Incorrect posAtWork. Must be at least 1 letter.");
            ui->lineEdit_4->clear();
            return;
        }
        if (line.size() > 30)
        {
            QMessageBox::warning(this, "Warning","Incorrect posAtWork. Too big tariff posAtWork.");
            ui->lineEdit_4->clear();
            return;
        }
        for (int i = 0; i < line.size(); i++)
            if (!(line[i] >= 65 && line[i] <= 90) && !(line[i] >= 97 && line[i] <= 122))
            {
                QMessageBox::warning(this, "Warning","Incorrect posAtWork. Must be only letters without spaces anywhere.");
                ui->lineEdit_4->clear();
                return;
            }
        // change
        listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->posAtWork = line;
        quicksort(listOfWorkers, 0, listOfWorkers->getCount() - 1);
        fileReset();    // was before quicksort
        ui->tableWidget->clear();
        textOutput();
    }
}


void MainWindow::on_comboBox_5_currentTextChanged(const QString &currText)
{
    if (checkFile && listOfWorkers->getCount() != 0)
    {
        if (currText == "dateStart")
        {
            ui->lineEdit_4->setInputMask("99.99.9999");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->dateStart);
        }
        else if (currText == "name")
        {
            ui->lineEdit_4->setInputMask("");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->name);
        }
        else if (currText == "surname")
        {
            ui->lineEdit_4->setInputMask("");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->surname);
        }
        else if (currText == "patronymic")
        {
             ui->lineEdit_4->setInputMask("");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->patronymic);
        }
        else if (currText == "departmentNum")
        {
            ui->lineEdit_4->setInputMask("999");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->departmentNum);
        }
        else if (currText == "posAtWork")
        {
            ui->lineEdit_4->setInputMask("");
            ui->lineEdit_4->setText(listOfWorkers->getElem(ui->comboBox_2->currentText().toInt() - 1)->posAtWork);
        }
        currTextParam = currText;
    }
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &currText)
{
    if (currText.size() == 0)   ui->lineEdit_4->clear();
    if (checkFile && currText.size() != 0)
    {
        if (currTextParam == "dateStart")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->dateStart);
        else if (currTextParam == "name")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->name);
        else if (currTextParam == "surname")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->surname);
        else if (currTextParam == "patronymic")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->patronymic);
        else if (currTextParam == "departmentNum")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->departmentNum);
        else if (currTextParam == "posAtWork")
            ui->lineEdit_4->setText(listOfWorkers->getElem(currText.toInt() - 1)->posAtWork);
    }
}

