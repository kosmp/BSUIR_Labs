#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(700,500);
    this->setFixedSize(700,500);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,700,500);
    fileInit();
    table();
    Date today;
    today.realDate();
    QString realDate;
    if(today.day < 10) realDate += "0";
    realDate += QString::number(today.day);
    realDate += ".";
    if(today.month < 10) realDate += "0";
    realDate += QString::number(today.month);
    realDate += ".";
    if (today.year < 10)
    {
        realDate += "000";
    }
    else if (today.year < 100)
    {
        realDate += "00";
    }
    else if (today.year < 1000)
    {
        realDate += "0";
    }
    realDate += QString::number(today.year);
    ui->label->setText(realDate);
}

MainWindow::~MainWindow()
{
    delete[] dates;
    delete ui;
}

void MainWindow::table()
{
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 80);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Dates in file" << "Next date" << "Days between");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < ui->tableWidget->rowCount(); row++)
    {
        QString date1;
        if (dates[row].day < 10)
        {
            date1 += "0";
        }
        date1 += QString::number(dates[row].day);
        date1 += ".";
        if (dates[row].month < 10)
        {
            date1 += "0";
        }
        date1 += QString::number(dates[row].month);
        date1 += ".";
        if (dates[row].year < 10)
        {
            date1 += "000";
        }
        else if (dates[row].year < 100)
        {
            date1 += "00";
        }
        else if (dates[row].year < 1000)
        {
            date1 += "0";
        }
        date1 += QString::number(dates[row].year);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(date1));
        QString date2;
        Date nextDay = dates[row].NextDay();
        if (nextDay.day < 10)
        {
            date2 += "0";
        }
        date2 += QString::number(nextDay.day);
        date2 += ".";
        if (nextDay.month < 10)
        {
            date2 += "0";
        }
        date2 += QString::number(nextDay.month);
        date2 += ".";
        if (nextDay.year < 10)
        {
            date2 += "000";
        }
        else if (nextDay.year < 100)
        {
            date2 += "00";
        }
        else if (nextDay.year < 1000)
        {
            date2 += "0";
        }
        date2 += QString::number(nextDay.year);
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(date2));
        if (row + 1 != ui->tableWidget->rowCount())
        {
            QString column3 = QString::number(dates[row].Duration(dates[row+1]));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(column3));
        }
    }
}

void MainWindow::fileInit()
{
    QFile file(directory1);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File wasn't opened!";
        QMessageBox::warning(this, "Warning", "File wasn't opened!");
        exit(123);
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        in.readLine();
        i++;
    }
    file.close();
    file.open(QIODevice::ReadOnly);
    delete[] dates;
    dates = new Date[i+1];
    i = 0;
    while(!in.atEnd())
    {
        qDebug() << "Reading";
        QString line = in.readLine();
        if(line.size() != 10)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Or file is empty. In file must be correct dates. Correct information in file and try again.");
            exit(123);
        }
        if(line.at(0) < 48 || line.at(0) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(1) < 48 || line.at(1) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(2) != '.')
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(3) < 48 || line.at(3) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(4) < 48 || line.at(4) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(5) != '.')
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(6) < 48 || line.at(6) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(7) < 48 || line.at(7) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(8) < 48 || line.at(8) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        if(line.at(9) < 48 || line.at(9) > 57)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Incorrect format of dates. And the dates should be in a column. Correct information and try again.");
            exit(123);
        }
        int yearCheck = 1000 * line.at(6).digitValue() + 100 * line.at(7).digitValue() + 10 * line.at(8).digitValue() + line.at(9).digitValue();
        if (yearCheck == 0)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Year can't be 0. Correct file and try again.");
            exit(123);
        }
        dates[i].year = yearCheck;
        int monthCheck = 10 * line.at(3).digitValue() + line.at(4).digitValue();
        if(monthCheck > 12 || monthCheck == 0)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Month must be <= 12 and >0");
            exit(123);
        }
        dates[i].month = monthCheck;
        int dayCheck = 10 * line.at(0).digitValue() + line.at(1).digitValue();
        dates[i].day = dayCheck;
        dates[i].calculateMonths();
        if(dayCheck > dates[i].months[monthCheck] || dayCheck == 0)
        {
            QMessageBox::warning(this, "Warning", "Error. Smth incorrect in your file. Number of day must be possible.");
            exit(123);
        }
        i++;
    }
    file.close();
    ui->comboBox->clear();
    for (int j = 0; j < i; j++)
    {
        ui->comboBox->addItem(QString::number(j+1));
    }
}

void MainWindow::fileAddDate()
{
    QFile file(directory1);
    QTextStream out(&file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "File wasn't opened!";
        QMessageBox::warning(this, "Warning", "File wasn't opened!");
        return;
    }
    QString line = ui->lineEdit_3->text();
    bool checkDate = true;
    if(line.size() != 10)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(0) < 48 || line.at(0) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(1) < 48 || line.at(1) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(2) != '.')
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(3) < 48 || line.at(3) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(4) < 48 || line.at(4) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(5) != '.')
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(6) < 48 || line.at(6) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(7) < 48 || line.at(7) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(8) < 48 || line.at(8) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(line.at(9) < 48 || line.at(9) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    int yearCheck = 1000 * line.at(6).digitValue() + 100 * line.at(7).digitValue() + 10 * line.at(8).digitValue() + line.at(9).digitValue();
    int monthCheck = 10 * line.at(3).digitValue() + line.at(4).digitValue();
    int dayCheck = 10 * line.at(0).digitValue() + line.at(1).digitValue();
    if (yearCheck == 0 || monthCheck > 12 || monthCheck == 0 || dayCheck > 31)
    {
        if(checkDate)
        QMessageBox::warning(this, "Warning","You entered smth incorrect");
        return;
    }
    if (checkDate) out << line << "\r\n";
    file.close();
}

void MainWindow::changeData()
{
    int bytes = currentToChange * 12;
    QFile file(directory1);
    QTextStream out(&file);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "File wasn't opened!";
        QMessageBox::warning(this, "Warning", "File wasn't opened!");
        return;
    }
    bool checkDate = true;
    if(currentComboBox.size() != 10)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[0] < 48 || currentComboBox[0] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[1] < 48 || currentComboBox[1] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[2] != '.')
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[3] < 48 || currentComboBox[3] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[4] < 48 || currentComboBox[4] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[5] != '.')
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[6] < 48 || currentComboBox[6] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[7] < 48 || currentComboBox[7] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[8] < 48 || currentComboBox[8] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if(currentComboBox[9] < 48 || currentComboBox[9] > 57)
    {
        if (checkDate)
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        checkDate = false;
    }
    if (checkDate)
    {
        out.seek(bytes);
        int yearCheck = 1000 * currentComboBox.at(6).digitValue() + 100 * currentComboBox.at(7).digitValue() + 10 * currentComboBox.at(8).digitValue() + currentComboBox.at(9).digitValue();
        if (yearCheck == 9999 || yearCheck == 0)
        {
            QMessageBox::warning(this, "Warning","You entered smth incorrect. Impossible input. Exists universally recognized format of date.");
            return;
        }
        dates[currentToChange].year = yearCheck;
        int monthCheck = 10 * currentComboBox.at(3).digitValue() + currentComboBox.at(4).digitValue();
        if(monthCheck > 12 || monthCheck == 0)
        {
            QMessageBox::warning(this, "Warning","You entered smth incorrect. Impossible input. Try again");
            return;
        }
        dates[currentToChange].month = monthCheck;
        int dayCheck = 10 * currentComboBox.at(0).digitValue() + currentComboBox.at(1).digitValue();
        dates[currentToChange].calculateMonths();
        dates[currentToChange].day = dayCheck;
        if (dates[currentToChange].day > dates[currentToChange].months[dates[currentToChange].month] || dayCheck == 0)
        {
            QMessageBox::warning(this, "Warning","You entered smth incorrect. Impossible input. Try again");
            return;
        }
        out << currentComboBox;
        out.seek(0);
    }
    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    QString birthDay = ui->lineEdit->text();
    if(birthDay.size() != 10)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(0) < 48 || birthDay.at(0) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(1) < 48 || birthDay.at(1) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(2) != '.')
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(3) < 48 || birthDay.at(3) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(4) < 48 || birthDay.at(4) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(5) != '.')
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(6) < 48 || birthDay.at(6) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(7) < 48 || birthDay.at(7) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(8) < 48 || birthDay.at(8) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    if(birthDay.at(9) < 48 || birthDay.at(9) > 57)
    {
        QMessageBox::warning(this, "Warning","You entered date in the wrong format. True format: dd.mm.yyyy");
        return;
    }
    int tempYear = birthDay.at(6).digitValue() * 1000 + birthDay.at(7).digitValue() * 100 + birthDay.at(8).digitValue() * 10 + birthDay.at(9).digitValue();
    int tempMonth = birthDay.at(3).digitValue() * 10 + birthDay.at(4).digitValue();
    int tempDay = birthDay.at(0).digitValue() * 10 + birthDay.at(1).digitValue();
    Date current;
    current.realDate();
    current.calculateMonths();
    if (tempYear <= 1870)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect. Incorrect date of birthday. Year can't be <= 1870, because you couldn't be here.");
        return;
    }
    if ((tempYear == 2022 && tempMonth > current.month) || (tempYear == 2022 && tempMonth == current.month && tempDay > current.day))
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect. Incorrect date of birthday");
        return;
    }
    if (tempYear == 0 || tempYear > 2022)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect. Year of your birthday can't be > of current year ");
        return;
    }
    if (tempMonth == 0 || tempMonth > 12)
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect. Month of date can't be = 0 or > 12.");
        return;
    }
    birthDayDate.year = tempYear;
    birthDayDate.month = tempMonth;
    birthDayDate.calculateMonths();
    if (tempDay == 0 || tempDay > birthDayDate.months[birthDayDate.month])
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect. Number of days can't be like that you entered.");
        return;
    }
    birthDayDate.day = tempDay;
    ui->label_5->setText(birthDay);
    birthDayCheck = true;
}


void MainWindow::on_radioButton_clicked()
{
    if(birthDayCheck)
    {
        Date real;
        real.realDate();
        QString text = QString::number(real.DaysTillYourBirthday(birthDayDate));
        ui->label_6->setText(text);
    }
    else
    {
        QMessageBox::warning(this, "Warning","You can see this only after entering correct birthday date in the field.");
    }
}


void MainWindow::on_radioButton_2_clicked()
{
    Date real;
    real.realDate();
    QString text = QString::number(real.WeekNumber());
    ui->label_7->setText(text);
}


void MainWindow::on_radioButton_3_clicked()
{
    QString date;
    Date real;
    real.realDate();
    Date nextDay = real.NextDay();
    if (nextDay.day < 10)
    {
        date += "0";
    }
    date += QString::number(nextDay.day);
    date += ".";
    if (nextDay.month < 10)
        date += "0";
    date += QString::number(nextDay.month);
    date += ".";
    if (nextDay.year < 10)
        date += "000";
    else if (nextDay.year < 100)
        date += "00";
    else if (nextDay.year < 1000)
        date += "0";
    date += QString::number(nextDay.year);
    ui->label_8->setText(date);
}


void MainWindow::on_radioButton_4_clicked()
{
    QString date;
    Date real;
    real.realDate();
    Date prevDay = real.PreviousDay();
    if (prevDay.day < 10)
        date += "0";
    date += QString::number(prevDay.day);
    date += ".";
    if (prevDay.month < 10)
        date += "0";
    date += QString::number(prevDay.month);
    date += ".";
    if (prevDay.year < 10)
        date += "000";
    else if (prevDay.year < 100)
        date += "00";
    else if (prevDay.year < 1000)
        date += "0";
    date += QString::number(prevDay.year);
    ui->label_9->setText(date);
}


void MainWindow::on_radioButton_5_clicked()
{
    Date real;

    QString text;
    if(real.IsLeap())
        text = "Year is leap.";
    else
        text = "Year isn't leap.";
    ui->label_10->setText(text);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString directory = ui->lineEdit_2->text();
    QFile file(directory);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File wasn't opened!";
        QMessageBox::warning(this, "Warning","File wasn't opened!");
    }
    else
    {
        file.close();
        directory1 = ui->lineEdit_2->text();
        ui->tableWidget->clear();
        i=0;
        directory1 = directory;
        fileInit();
        table();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString line = ui->lineEdit_3->text();
    if(line.size() == 10)
        fileAddDate();
    else
    {
        QMessageBox::warning(this, "Warning","You entered smth incorrect.");
        return;
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->lineEdit_4->clear();
    currentComboBox.clear();
    currentToChange = index;
    if (dates[index].day < 10)
        currentComboBox += "0";
    currentComboBox += QString::number(dates[index].day);
    currentComboBox += ".";
    if (dates[index].month < 10)
        currentComboBox += "0";
    currentComboBox += QString::number(dates[index].month);
    currentComboBox += ".";
    if (dates[index].year < 10)
        currentComboBox += "000";
    else if (dates[index].year < 100)
        currentComboBox += "00";
    else if (dates[index].year < 1000)
        currentComboBox += "0";
    currentComboBox += QString::number(dates[index].year);
    ui->lineEdit_4->setText(currentComboBox);
}


void MainWindow::on_pushButton_4_clicked()
{
    currentComboBox = ui->lineEdit_4->text();
    changeData();
}


void MainWindow::on_pushButton_5_clicked()
{
    i = 0;
    fileInit();
    ui->tableWidget->clear();
    table();
}

