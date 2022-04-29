#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}


vector<char> powstr(vector<char>& str, int k);
int len(vector<char>& a);
bool k_bit(vector<char> str, int k);

bool k_bit(vector<char> str1, int k)
{
    vector<char> str = str1;
    int bit, i = 0;
    int lenstr = len(str);

    for (; i != k; i++)
    {
        bit = (str[lenstr - 1] - '0') % 2;
        str[lenstr - 1] = str[lenstr - 1] - bit;

        for (int j = lenstr - 1; j >= 0; j--)
        {
            if ((str[j] - '0') % 2 == 0)
            {
                str[j] = (str[j] - '0') / 2 + '0';
            }
            else
            {
                str[j] = (str[j] - '0') / 2 + '0';

                if (j != lenstr - 1)
                {
                    str[j + 1] = str[j + 1] + 5;
                }
            }
        }
    }

    return(bit);
}


int len(vector<char>& a)
{
    int len = 0;

    for (; a[len] != 'q'; len++);

    return(len);
}

vector<char> powstr(vector<char>& str, int k)
{
    vector<char> deg;

    deg.push_back('1');

    if (k == 0)
    {
        deg.push_back('q');
        return(deg);
    }

    for (int i = 0; i < k; i++)
    {
        deg.push_back('0');
    }

    for (int i = deg.size() - 1, j = len(str) - 1; i >= 0 && j >= 0; i--, j--)
    {
        deg[i] = str[j];
    }

    deg.push_back('q');
    return(deg);
}


void MainWindow::on_pushButton_clicked()
{
    n = ui->lineEdit->text().toInt();
    if (ui->lineEdit->text().size() == 0)
    {
         QMessageBox::warning(this, "Warning","Incorrect number.");
         return;
    }
    if (n > 10000)
    {
       QMessageBox::warning(this, "Warning","Incorrect number.");
    }
    else
    {
        vector<vector<char>> A;
        vector<char> temp;
        A.resize(10000, temp);
        vector<vector<char>> B;
        B.resize(10000, temp);

        for (int i = 0; i < 10000; i++)
        {
            A[i].resize(200, 'q');
            B[i].resize(200, 'q');
        }

        A[0][0] = '0';

        int counterB, counterA = 1, k = 1, counterBIN = 1, tmp;

        //std::cout << "Displays the n-th smallest bindecimal number." << std::endl;
        //std::cout << "enter n" << std::endl;

        //std::cin >> n;

        /*
        while (n < 1 || n > 10000 || std::cin.get() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX - 1, '\n');
            QMessageBox::warning(this, "Warning","Incorrect number.");
        }
        */

        while (n >= counterBIN)
        {
            tmp = counterB = 0;

            for (int i = 0; i < counterA; i++)
            {
                if (!k_bit(A[i], k))
                {
                    A[tmp] = A[i];
                    tmp++;
                }
            }

            counterA = tmp;

            for (int i = 0; i < counterA; i++)
            {
                B[i] = powstr(A[i], k - 1);
                counterB++;
            }

            for (int i = 0; i < counterB; i++)
            {
                A[counterA] = B[i];
                counterA++;
            }

            counterBIN += counterB;
            k++;
        }

        QString result;
        for (int i = 0; i < B[counterB - (counterBIN - n)].size(); i++)
        {
            if (B[counterB - (counterBIN - n)][i] == 'q')
            {
                break;
            }
            result.push_back((QChar)B[counterB - (counterBIN - n)][i]);
            ui->textEdit->setText(result);
            //std::cout << B[counterB - (counterBIN - n)][i];
        }
    }
}

