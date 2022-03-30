#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600,300);
    ui->label->setVisible(false);
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


void MainWindow::showResult(int& pos, int& linesCount, QString& inputLine)
{
    int col = 0;
    int row = 0;
    int countLine = 1;
    for (int i = 0; i < inputLine.size(); i++)
    {
        if (inputLine[i] == '\n' || inputLine.size() == i + 1)
        {
            if (pos < i + 2)
            {
                row = countLine;
                break;
            }
            else
                countLine++;
        }
    }
    int numOfEnd = 0;   // num of \n
    for (int i = 0; i < inputLine.size(); i++)
    {
        if (linesCount == 1)
        {
            col = pos;
            break;
        }
        if (inputLine[i] == '\n' || inputLine.size() == i + 1)
        {
            if (pos <= i + 1)   // = for situations if inputLine.size() == i + 1 and pos in the end
            {
                if (numOfEnd > 0)    // if = 0, then pos before first \n
                {
                    int indexOfPrev = -1;
                    int countOfEndsPrev = 0;
                    for (int i = 0; i < inputLine.size(); i++)  // searching index of prev \n
                    {
                        if (countOfEndsPrev == numOfEnd - 1)
                            indexOfPrev = i + 1;

                        if (inputLine[i] == '\n')
                            countOfEndsPrev++;
                    }
                    if (indexOfPrev >= 0)
                    {
                        col = pos - indexOfPrev;
                        break;
                    }
                }
                else
                {
                    col = pos;
                    break;
                }
            }
            numOfEnd++;
        }
    }
    QMessageBox::warning(this, "Warning","row: " + QString::number(row) + " col: " + QString::number(col));
    return;
}


void MainWindow::on_button_checkInFile_clicked()
{
    QString fileLine;
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "D://");
    if(filename.isEmpty())
    {
       QMessageBox::warning(this, "Warning","No such file.");
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        for (int i = 0; i < line.size(); i++)
            if (line[i] != '(' && line[i] != ')' && line[i] != '[' && line[i] != ']' && line[i] != '{' && line[i] != '}' && !(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] >= 'a' && line[i] <= 'z') && !(line[i] >= '0' && line[i] <= '9') && line[i] != '.' && line[i] != ',' && line[i] != ':' && line[i] != ';' && line[i] != '-' && line[i] != '!' && line[i] != '?')
            {
                QMessageBox::warning(this, "Warning","Incorrect data in the file. File is unused. Change data in the file and try again.");
                return;
            }
        fileLine += line + '\n';
    }
    if (fileLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty. File is unused. Change data in the file and try again.");
        return;
    }
    file.close();

    // checking
    int linesCount = 1;
    for (int i = 0; i < fileLine.size(); i++)
        if (fileLine[i] == '\n')
            linesCount++;

    if (fileLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
        return;
    }

    int pos = check_brackets(fileLine);
    if (pos == -1)
    {
        QMessageBox::warning(this, "Warning","SUCCESS");
        return;
    }

    if (check && pos != -1)
    {
        // output of position this i. closing bracket
        showResult(pos, linesCount, fileLine);
        return;
    }
    if (!check && pos != -1)
    {
        // output of position this i. opening bracket
        showResult(pos, linesCount, fileLine);
        return;
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString inputLine = ui->textEdit->toPlainText();
    for (int i = 0; i < inputLine.size(); i++)
        if (inputLine[i] != '\n' && inputLine[i] != '(' && inputLine[i] != ')' && inputLine[i] != '[' && inputLine[i] != ']' && inputLine[i] != '{' && inputLine[i] != '}' && !(inputLine[i] >= 'A' && inputLine[i] <= 'Z') && !(inputLine[i] >= 'a' && inputLine[i] <= 'z') && !(inputLine[i] >= '0' && inputLine[i] <= '9') && inputLine[i] != '.' && inputLine[i] != ',' && inputLine[i] != ':' && inputLine[i] != ';' && inputLine[i] != '-' && inputLine[i] != '!' && inputLine[i] != '?')
        {
            QMessageBox::warning(this, "Warning","Incorrect input. Change data and try again.");
            return;
        }
    int linesCount = 1;
    for (int i = 0; i < inputLine.size(); i++)
        if (inputLine[i] == '\n')
            linesCount++;

    if (inputLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
        return;
    }

    int pos = check_brackets(inputLine);
    if (pos == -1)
    {
        QMessageBox::warning(this, "Warning","SUCCESS");
        return;
    }

    if (check && pos != -1)
    {
        // output of position this i. closing bracket
        showResult(pos, linesCount, inputLine);
        return;
    }
    if (!check && pos != -1)
    {
        // output of position this i. opening bracket
        showResult(pos, linesCount, inputLine);
        return;
    }
}
