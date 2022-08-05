#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700,450);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::check_brackets(QString line)
{
    check = false;
    Stack<QChar> brackets;
    Stack<int> indicesOfOpen;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '[' || line[i] == '(' || line[i] == '{')
        {
            brackets.push(line[i]);
            indicesOfOpen.push(i);
            continue;
        }
        if (line[i] == ']' && brackets.pop() != '[')
        {
            check = true;
            return i + 1;    // first closing without opening
        }
        if (line[i] == ']')
            indicesOfOpen.pop();
        if (line[i] == ')' && brackets.pop() != '(')
        {
            check = true;
            return i + 1;    // first closing without opening
        }
        if (line[i] == ')')
            indicesOfOpen.pop();
        if (line[i] == '}' && brackets.pop() != '{')
        {
            check = true;
            return i + 1;    // first closing without opening
        }
        if (line[i] == '}')
            indicesOfOpen.pop();
    }
    if (!brackets.isEmpty())    // we have at least 1 opening bracket without pair. Need to find the first opening without closing
    {
        while (indicesOfOpen.Count() != 1)
        {
            indicesOfOpen.pop();
        }
        check = false;
        return indicesOfOpen.pop() + 1; // first opening without closing
    }
    if (brackets.isEmpty())
        return -1;     // success
}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit_2->clear();
    QString inputLine = ui->textEdit->toPlainText();

    int linesCount = 1;
    for (int i = 0; i < inputLine.size(); i++)
        if (inputLine[i] == '\n')
            linesCount++;
    if (linesCount > 255)
    {
        QMessageBox::warning(this, "Warning","Too many rows. Max 255.");
        return;
    }

    if (inputLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
        return;
    }

    int spacesInLine = 0;
    int counter = 1;
    for (int i = 0; i < inputLine.size(); i++)
    {
        if (inputLine[i] == '\n' || inputLine.size() == i + 1)
        {
            if (counter == 1)
            if (i + 1 >= 255)
            {
                QMessageBox::warning(this, "Warning","Too big lines.");
                return;
            }
            if (counter != 1)
            if (i + 1 - i >= 255)
            {
                QMessageBox::warning(this, "Warning","Too big lines.");
                return;
            }
            if (spacesInLine != 5)
            {
                QMessageBox::warning(this, "Warning","Incorrect input. Must be 5 spaces between data.");
                return;
            }
            spacesInLine = 0;
            counter++;
        }
        if (inputLine[i] == ' ')
        {
            if (spacesInLine >= 2)
                if (inputLine[i - 1] == ' ')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input. Two spaces are together.");
                    return;
                }
            if (i + 1 == inputLine.size())
            {
                QMessageBox::warning(this, "Warning","Incorrect input.");
                return;
            }
            spacesInLine++;
        }
    }
    int inc = 0;
    for (int i = 0; i < inputLine.size(); i++)
    {
        if (inputLine[i] == '\n' || inputLine.size() == i + 1)
        {
            QString line;
            QString a;
            QString b;
            QString c;
            QString d;
            QString e;
            int indSpace;
            for (int i = 0 + inc; inputLine[i] != ' '; i++)
            {
                line += inputLine[i];
                if (!(inputLine[i] >= 'a' && inputLine[i] <= 'e') && inputLine[i] != '(' && inputLine[i] != ')' && inputLine[i] != '+' && inputLine[i] != '-' && inputLine[i] != '*' && inputLine[i] != '/' && inputLine[i] != ' ')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input. Change data and try again. Can be letters from a to e, (, ), +, -, *, /.");
                    return;
                }
                if (inputLine[i + 1] == ' ')
                    indSpace = i + 1;
            }
            int countDots = 0;
            for (int i = indSpace + 1; inputLine[i] != ' '; i++)        // a
            {
                a += inputLine[i];
                if (inputLine[indSpace + 1] == '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i] == '.')    countDots++;
                if (countDots > 1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }

                if (!(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i + 1] == ' ')
                    indSpace = i + 1;
            }
            countDots = 0;
            for (int i = indSpace + 1; inputLine[i] != ' '; i++)        // b
            {
                b += inputLine[i];
                if (inputLine[indSpace + 1] == '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i] == '.')    countDots++;
                if (countDots > 1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }

                if (!(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i + 1] == ' ')
                    indSpace = i + 1;
            }
            countDots = 0;
            for (int i = indSpace + 1; inputLine[i] != ' '; i++)        // c
            {
                c += inputLine[i];
                if (inputLine[indSpace + 1] == '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i] == '.')    countDots++;
                if (countDots > 1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }

                if (!(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i + 1] == ' ')
                    indSpace = i + 1;
            }
            countDots = 0;
            for (int i = indSpace + 1; inputLine[i] != ' '; i++)        // d
            {
                d += inputLine[i];
                if (inputLine[indSpace + 1] == '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i] == '.')    countDots++;
                if (countDots > 1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }

                if (!(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i + 1] == ' ')
                    indSpace = i + 1;
            }
            countDots = 0;
            for (int i = indSpace + 1; inputLine[i] != '\n' && inputLine.size() != i; i++)       // e
            {
                e += inputLine[i];
                if (inputLine[indSpace + 1] == '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                if (inputLine[i] == '.')    countDots++;
                if (countDots > 1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }

                if (!(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.')
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
            }
            try
            {
                if (check_brackets(line) != -1)
                {
                    QMessageBox::warning(this, "Warning","Incorrect input.");
                    return;
                }
                QString readyPostfix = conv.convert(line);
                double result = conv.calcPostfix(readyPostfix, a.toDouble(), b.toDouble(), c.toDouble(), d.toDouble(), e.toDouble());
                ui->textEdit_2->append(readyPostfix + ' ' + QString::number(result));
                inc = i + 1;
            }  catch (_exception) {
                QMessageBox::warning(this, "Warning","Smth incorrect.");
                return;
            }
        }
    }
}

