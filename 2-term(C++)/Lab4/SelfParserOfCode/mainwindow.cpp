#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1500,500);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Parameter" << "Result");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_checkInFile_clicked()
{
    QString fileLine;
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "D://", "(*.cpp)");
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
        fileLine += line + '\n';
    }
    if (fileLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","File is empty. File is unused. Change data in the file and try again.");
        return;
    }
    file.close();
    for (int i = 0; fileLine[i] != '\0'; i++)
        if (fileLine[i] == '\t')
        {
            fileLine.remove(i, 1);
            fileLine.insert(i, "    ");
        }

    int linesCount = 1;
    for (int i = 0; i < fileLine.size(); i++)
        if (fileLine[i] == '\n')
            linesCount++;

    if (fileLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
        return;
    }
    text = fileLine;

    parseVar(fileLine);
    classStructArray(fileLine);
    funcPrototypes(fileLine);
    changeCoordVarOrArray(fileLine);
    countLocVarsAndCoords(fileLine);
    countOverloadedFuncAndCoords(fileLine);
    branchingDepth(fileLine);
    logicErrors(fileLine);
}


void MainWindow::on_pushButton_clicked()
{
    QString inputLine = ui->textEdit->toPlainText();

    int linesCount = 1;
    for (int i = 0; i < inputLine.size(); i++)
        if (inputLine[i] == '\n')
            linesCount++;

    if (inputLine.size() == 0)
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
        return;
    }
    bool find = false;
    for (int i = 0; inputLine[i] != '\0'; i++)
    {
        if (inputLine[i] == '\n')
            find = true;
        else
        {
            find = false;
            break;
        }
    }
    if (!find)
    {
        parseVar(inputLine);
        classStructArray(inputLine);
        funcPrototypes(inputLine);
        changeCoordVarOrArray(inputLine);
        countLocVarsAndCoords(inputLine);
        countOverloadedFuncAndCoords(inputLine);
        branchingDepth(inputLine);
        logicErrors(inputLine);
    }
    else
    {
        QMessageBox::warning(this, "Warning","Input field is empty.");
    }
}

void MainWindow::parseVar(QString text)
{
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Parameter" << "Result");
    ui->tableWidget->setRowCount(0);
    std::string sText = text.toStdString();
    const std::regex r("\\n[ \\t]*[A-Za-z_]*(::)?(static\\s)?(const\\s)?(unsigned\\s)?(string|size_t|char|bool|int|long int|long long int|float|double|auto)\\**&?\\s(\\**&?[a-z][_a-zA-Z]*((\\{.+\\};)|(\\{.+\\},\\s)|(\\(.+\\);)|(\\(.+\\),\\s)|(,\\s)|(\\s=\\s&?.+,\\s)|(\\s=\\s&?.+;)|;))+");
    std::smatch result;

    std::list<QString> storage;
    int count = 0;
    int countOfVar = 0;
    while (std::regex_search(sText, result, r))
    {
        std::string tmp = result[0];
        bool checkBrackets = false;
        for (int i = 0; i < (int)tmp.size(); i++)
        {
            if (tmp[i] == '(') checkBrackets = true;
            else if (tmp[i] == ')') checkBrackets = false;
            else if (tmp[i] == ',' && !checkBrackets)
                countOfVar++;
        }
        countOfVar++;
        storage.push_back(QString::fromStdString(result[0]));
        sText = result.suffix().str();
        count++;
    }
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString::number(countOfVar)));
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Count of variables:"));
    if (count != 0)
    {
        ui->tableWidget->setRowCount(count + 1);
        ui->tableWidget->setItem(1,0,new QTableWidgetItem("Variables:"));
    }
    for (int i = 0; i < count; i++)
    {
        QString tmp = storage.front();
        for (int i = 0; tmp[i] != '\0'; i++)
            if (tmp[i] == '\t')
                tmp.remove(i, 1);
        ui->tableWidget->setItem(i + 1,1,new QTableWidgetItem(tmp));
        storage.pop_front();
    }
}

void MainWindow::classStructArray(QString text)
{
    int sRows = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(sRows + 3);
    std::string sText = text.toStdString();
    const std::regex rClass("\\nclass\\s[A-Z][a-zA-z]*((\\s\\{)|(\\s:))");
    const std::regex rStruct("\\nstruct\\s[A-Z][a-zA-z]*((\\s\\{)|(\\s:))");
    std::smatch mClass;
    std::smatch mStruct;

    std::list<std::string> classNames;
    std::list<std::string> structNames;
    while (std::regex_search(sText, mClass, rClass))
    {
        std::string tmp = mClass[0];
        tmp.erase(0, 7);
        tmp.pop_back();
        tmp.pop_back();
        classNames.push_back(tmp);
        sText = mClass.suffix().str();
    }
    sText = text.toStdString();
    while (std::regex_search(sText, mStruct, rStruct))
    {
        std::string tmp = mStruct[0];
        tmp.erase(0, 8);
        tmp.pop_back();
        tmp.pop_back();
        structNames.push_back(tmp);
        sText = mStruct.suffix().str();
    }
    sText = text.toStdString();

    std::string classObjectNames;
    int size1 = (int)classNames.size();
    for (int i = 0; i < size1; i++)
    {
        std::string name = classNames.front();
        if (i == size1 - 1)
            classObjectNames += name;
        else
            classObjectNames += name + '|';
        classNames.pop_front();
    }

    std::string structObjectNames;
    int size2 = (int)structNames.size();
    for (int i = 0; i < size2; i++)
    {
        std::string name = structNames.front();
        if (i == size2 - 1)
            structObjectNames += name;
        else
            structObjectNames += name + '|';
        structNames.pop_front();
    }

    int countOfClassObjects = 0;
    if (classObjectNames.size() != 0)
    {
        const std::regex classObject("\\n[ \\t]*("+classObjectNames+")((\\**)|(&?))\\s((\\**)|(&?))(([a-zA-Z].*)((,\\s)|;|(\\s=\\s.+(;|(,\\s)))))+");
        std::smatch resultClass;
        while (std::regex_search(sText, resultClass, classObject))
        {
            std::string tmp = resultClass[0];
            bool checkBrackets = false;
            for (int i = 0; i < (int)tmp.size(); i++)
            {
                if (tmp[i] == '(') checkBrackets = true;
                else if (tmp[i] == ')') checkBrackets = false;
                else if (tmp[i] == ',' && !checkBrackets)
                    countOfClassObjects++;
            }
            countOfClassObjects++;
            sText = resultClass.suffix().str();
        }
        sText = text.toStdString();
    }
    ui->tableWidget->setItem(sRows, 0,new QTableWidgetItem("Classes' objects"));
    ui->tableWidget->setItem(sRows, 1,new QTableWidgetItem(QString::number(countOfClassObjects)));

    int countOfStructObjects = 0;
    if (structObjectNames.size() != 0)
    {
        const std::regex structObject("\\n[ \\t]*("+structObjectNames+")((\\**)|(&?))\\s((\\**)|(&?))(([a-zA-Z].*)((,\\s)|;|(\\s=\\s.+(;|(,\\s)))))+");
        std::smatch resultStruct;
        while (std::regex_search(sText, resultStruct, structObject))
        {
            std::string tmp = resultStruct[0];
            bool checkBrackets = false;
            for (int i = 0; i < (int)tmp.size(); i++)
            {
                if (tmp[i] == '(') checkBrackets = true;
                else if (tmp[i] == ')') checkBrackets = false;
                else if (tmp[i] == ',' && !checkBrackets)
                    countOfStructObjects++;
            }
            countOfStructObjects++;
            sText = resultStruct.suffix().str();
        }
        sText = text.toStdString();
    }
    sRows++;
    ui->tableWidget->setItem(sRows, 0,new QTableWidgetItem("Structs' objects"));
    ui->tableWidget->setItem(sRows, 1,new QTableWidgetItem(QString::number(countOfStructObjects)));

    int countOfArrays = 0;
    std::regex rArray;
    if (classObjectNames.size() != 0 && structObjectNames.size() != 0)
        rArray = "\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?("+classObjectNames+'|'+structObjectNames+"|size_t|char|bool|int|long int|long long int|float|double)\\**\\s(\\**[a-zA-Z_]+(\\[.*\\])+.*(;|(,\\s)|(=\\s.+(;|(,\\s)))))+";
    else if (classObjectNames.size() != 0)
        rArray = "\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?("+classObjectNames+"|size_t|char|bool|int|long int|long long int|float|double)\\**\\s(\\**[a-zA-Z_]+(\\[.*\\])+.*(;|(,\\s)|(=\\s.+(;|(,\\s)))))+";
    else if (structObjectNames.size() != 0)
        rArray = "\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?("+structObjectNames+"|size_t|char|bool|int|long int|long long int|float|double)\\**\\s(\\**[a-zA-Z_]+(\\[.*\\])+.*(;|(,\\s)|(=\\s.+(;|(,\\s)))))+";
    else
        rArray = "\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?(size_t|char|bool|int|long int|long long int|float|double)\\**\\s(\\**[a-zA-Z_]+(\\[.*\\])+.*(;|(,\\s)|(=\\s.+(;|(,\\s)))))+";

    std::smatch resultArrays;
    while (std::regex_search(sText, resultArrays, rArray))
    {
        std::string tmp = resultArrays[0];
        if (tmp.size() - 2 == ',')
            tmp.erase(tmp.size() - 2, 2);
        bool checkBrackets = false;
        for (int i = 0; i < (int)tmp.size(); i++)
        {
            if (tmp[i] == '{') checkBrackets = true;
            else if (tmp[i] == '}') checkBrackets = false;
            else if (tmp[i] == ',' && !checkBrackets)
                countOfArrays++;
        }
        countOfArrays++;
        sText = resultArrays.suffix().str();
    }
    sText = text.toStdString();

    sRows++;
    ui->tableWidget->setItem(sRows, 0,new QTableWidgetItem("Arrays"));
    ui->tableWidget->setItem(sRows, 1,new QTableWidgetItem(QString::number(countOfArrays)));
}

void MainWindow::funcPrototypes(QString text)
{
    std::string sText = text.toStdString();
    std::regex prototype("\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?(string|void|size_t|char|bool|int|long int|long long int|float|double|auto)\\**&{0,2}\\s\\**&{0,2}.+(::)?.*\\(.*\\) \\{");
    std::smatch result;

    std::list<QString> storage;
    int count = 0;
    while (std::regex_search(sText, result, prototype))
    {
        storage.push_back(QString::fromStdString(result[0]));
        sText = result.suffix().str();
        count++;
    }
    int sRows = ui->tableWidget->rowCount();
    if (count != 0)
        ui->tableWidget->setRowCount(sRows + count);
    else
        ui->tableWidget->setRowCount(sRows + 1);
    ui->tableWidget->setItem(sRows,0,new QTableWidgetItem("Functions' prototypes:"));
    for (int i = sRows; i < sRows + count; i++)
    {
        QString tmp = storage.front();
        tmp.remove(tmp.size() - 2, 2);
        if (tmp.size() - 1 != ';') tmp.push_back(';');
        for (int i = 0; tmp[i] != '\0'; i++)
            if (tmp[i] == '\t')
                tmp.remove(i, 1);
        ui->tableWidget->setItem(i, 1,new QTableWidgetItem(tmp));
        storage.pop_front();
    }
}

void MainWindow::changeCoordVarOrArray(QString text)
{
    std::string sText = text.toStdString();
    std::regex changeVarOrArray("\\n[ \\t]*(\\**&?[A-Za-z_]+(\\[.*\\])*\\s=\\s.+((,\\s)|;))+");
    std::smatch result;

    int countOfNewStr = 0;
    std::regex rFind("\\n");
    std::smatch m;
    while (std::regex_search(sText,m,rFind))
    {
        countOfNewStr++;
        sText = m.suffix().str();
    }
    sText = text.toStdString();

    while (std::regex_search(sText, result, changeVarOrArray))
    {
        std::string tmp = result[0];
        tmp.erase(0, 1);
        for (int i = 0; tmp[i] != '\0'; i++)
            if (tmp[i] == '\t')
                tmp.erase(i, 1);
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Changing of variable:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::fromStdString(tmp)));
        sText = result.suffix().str();

        int count = 0;
        std::string tmpText = sText;
        std::smatch mFind;
        while (std::regex_search(tmpText, mFind, rFind))
        {
            count++;
            tmpText = mFind.suffix().str();
        }
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Ind of str:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(countOfNewStr - count)));
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Str number:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number((countOfNewStr - count) + 1)));
    }
    sText = text.toStdString();
}

void MainWindow::countLocVarsAndCoords(QString text)
{
    std::string sText = text.toStdString();

    int countOfNewStr = 0;
    std::regex rFind("\\n");
    std::smatch m;
    while (std::regex_search(sText,m,rFind))
    {
        countOfNewStr++;
        sText = m.suffix().str();
    }
    sText = text.toStdString();

    std::stack<char> storage;
    const std::regex r("(\\n\\{)|(\\s\\{)|(\\n[ \\t]*[A-Za-z_]*(::)?(static\\s)?(const\\s)?(unsigned\\s)?(size_t|char|bool|int|long int|long long int|float|double|auto)\\**&?\\s(\\**&?[a-z][_a-zA-Z]*((\\{.+\\};)|(\\{.+\\},\\s)|(\\(.+\\);)|(\\(.+\\),\\s)|(,\\s)|(\\s=\\s&?[_A-Za-z\\.0-9\\(\\)]+,\\s)|(\\s=\\s&?[_A-Za-z\\.0-9\\(\\)]+;)|;))+)");
    // \\)\\s\\{
    //const std::regex rBracket("(\\n\\{)|(\\)\\s\\{)|(\\n\\})");
    std::smatch mFind;
    int countOfLocalVar = 0;
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1,0,new QTableWidgetItem("Count of local var:"));
    const int locVarInTable = ui->tableWidget->rowCount() - 1;
    while (std::regex_search(sText, mFind, r))
    {
        std::string tmp = mFind[0];
        if (tmp == "\n{" || tmp == " {")
        {
            storage.push('{');
            sText = mFind.suffix().str();
        }
        else if (tmp == "\n}")
        {
            storage.pop();
            sText = mFind.suffix().str();
        }
        else if (tmp != "\n{" && tmp != " {" && tmp != "\n}")
        {
            if (storage.size() != 0)
            {
                for (int i = 0; i < (int)tmp.size(); i++)
                {
                    if (tmp[i] == ',')
                        countOfLocalVar++;
                }
                countOfLocalVar++;

                int count = 0;
                std::string tmpText = sText;
                std::smatch mRes;
                for (int i = 0; tmpText[i] != tmp[1]; i++)
                    if (tmpText[i] == '\n')
                    {
                        tmpText.erase(i, 1);
                        i--;
                    }
                while (std::regex_search(tmpText, mRes, rFind))
                {
                    count++;
                    tmpText = mRes.suffix().str();
                }
                sText = text.toStdString();

                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Ind of line with local var:"));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(countOfNewStr - count)));
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Line number with local var:"));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number((countOfNewStr - count) + 1)));
            }
            sText = mFind.suffix().str();
        }
    }
    sText = text.toStdString();

    ui->tableWidget->setItem(locVarInTable,1,new QTableWidgetItem(QString::number(countOfLocalVar)));
}

void MainWindow::countOverloadedFuncAndCoords(QString text)
{
    std::string sText = text.toStdString();
    std::regex prototype("\\n[ \\t]*(static\\s)?(const\\s)?(unsigned\\s)?(string|void|size_t|char|bool|int|long int|long long int|float|double|auto)\\**&{0,2}\\s\\**&{0,2}.+(::)?.*\\(.*\\) \\{");
    std::smatch result;

    int countOfNewStr = 0;
    std::regex rFind("\\n");
    std::smatch m;
    while (std::regex_search(sText,m,rFind))
    {
        countOfNewStr++;
        sText = m.suffix().str();
    }
    sText = text.toStdString();

    std::vector<QString> names;
    std::vector<int> coords;
    while (std::regex_search(sText, result, prototype))
    {
        std::string tmp = result[0];
        sText = result.suffix().str();
        int count = 0;
        std::string tmpText = sText;
        std::smatch mFind;
        while (std::regex_search(tmpText, mFind, rFind))
        {
            count++;
            tmpText = mFind.suffix().str();
        }

        std::regex overload("\\s[A-Za-z_]+\\(");
        std::smatch m;
        if (std::regex_search(tmp, m, overload))
            tmp = m[0];

        names.push_back(QString::fromStdString(tmp));
        coords.push_back(countOfNewStr - count);
    }

    int x = 0;
    int countOfOverloaded = 0;
    std::vector<QString> buff;  // a a a
    for (int i = 0; i < (int)names.size() - 1; i++)
        for (int j = i + 1; j < (int)names.size(); j++)
        {
            if (names[i] == names[j])
            {
                bool check = true;
                int k = 0;
                for (; k < (int)buff.size(); k++)
                {
                    if (names[i] == buff[k])
                    {
                        check = false;  // уже смотрели эти совпадения
                        break;
                    }
                }
                if (check)
                {
                    countOfOverloaded++;
                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Ind of line with overloaded function:"));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(coords[j])));

                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Line number with overloaded function:"));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(coords[j] + 1)));

                    bool c = false;
                    for (int p = j; p < (int)names.size() - 1; p++)
                        for (int t = p + 1; t < (int)names.size(); t++)
                            if (names[p] == names[t])
                                c = true;

                    if ((j == (int)names.size() - 1 || names[j+1] != names[i]) && !c)
                    {
                        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Ind of line with overloaded function:"));
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(coords[i])));

                        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Line number with overloaded function:"));
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(coords[i] + 1)));
                    }
                }
                bool find = false;
                for (int p = j; p < (int)names.size() - 1; p++)
                    for (int t = p + 1; t < (int)names.size(); t++)
                        if (names[p] == names[t])
                            find = true;

                bool findDup = false;
                for (int m = 0; m < (int)buff.size(); m++)
                    if (buff[m] == names[j])
                        findDup = true;

                if ((j == (int)names.size() - 1 || !find) && !findDup)
                {
                    x++;
                    buff.push_back(names[i]);
                }
            }
        }
    if (countOfOverloaded > 0)
        countOfOverloaded += x;
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("CountOfOverloaded func:"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(countOfOverloaded)));
}

void MainWindow::branchingDepth(QString text)
{
        std::string str = text.toStdString();
        std::vector<int> depthArray;
        int currAmount = 0;
        std::stack<char> pos;
        for(int i = 0; i < str.size() - 5; ++i){
            if(str[i] != 'e' && str[i + 1] != 'l' && str[i + 2] != 's' && str[i + 3] != 'e'
                    && str[i + 4] == 'i' && str[i + 5] == 'f'){
                ++currAmount;
                pos.push('{');
            }
            if(str[i] == 'e' && str[i + 1] == 'l' && str[i + 2] == 's' && str[i + 3] == 'e'
                    && str[i + 4] == 'i' && str[i + 5] == 'f'){
                //++currAmount;
                pos.push('{');
            }
            if(!pos.empty() && str[i] == '}'){
                depthArray.push_back(currAmount);
                --currAmount;
                pos.pop();
            }
        }
        QString res;
        for(int i = 0; i < depthArray.size(); ++i){
            res += QString::number(depthArray[i]) + " ";
        }
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("branchingDepths:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(res));

}

void MainWindow::logicErrors(QString text)
{
    std::string sText = text.toStdString();
    std::regex constBoolVar("\\n[ \\t]*const\\sbool\\s[a-zA-Z]+[0-9_]*\\s=\\s((true)|(-?[1-9]+));");
    std::smatch res;

    int countOfNewStr = 0;
    std::regex rFind("\\n");
    std::smatch m;
    while (std::regex_search(sText,m,rFind))
    {
        countOfNewStr++;
        sText = m.suffix().str();
    }
    sText = text.toStdString();

    std::vector<std::string> storage;
    std::vector<int> indOfConstBoolTrue;
    while (std::regex_search(sText, res, constBoolVar))
    {
        std::string constBool = res[0];

        std::regex findName("[A-Za-z0-9_]+\\s=");
        std::smatch mFindName;
        if (std::regex_search(constBool, mFindName, findName))
        {
            std::string sFindName = mFindName[0];
            for (int i = 0; sFindName[i] != ' '; i++)
            {
                if (i == 0) constBool = "";
                constBool.push_back(sFindName[i]);
            }
            storage.push_back(constBool);
        }

        int count1 = 0;
        std::string tmpText = sText;
        tmpText.erase(0, 1);
        std::smatch mFind1;
        while (std::regex_search(tmpText, mFind1, rFind))
        {
            count1++;
            tmpText = mFind1.suffix().str();
        }
        int indOfConstBool = countOfNewStr - count1;
        indOfConstBoolTrue.push_back(indOfConstBool);

        sText = res.suffix().str();
    }

    std::string constBoolString;
    for (int i = 0; i < (int)storage.size(); i++)
    {
        std::string name = storage.back();

        if (i == (int)storage.size() - 1)
            constBoolString += name;
        else
            constBoolString += name + '|';
        storage.pop_back();
        i--;
    }

    sText = text.toStdString();

    std::regex fWhile("(while\\s\\((" + constBoolString + "|(true)|(false))\\)\\s\\{)|(while\\s\\((" + constBoolString + "|(true)|(false))\\)\\s.+;)");
    std::smatch mFind;
    while (std::regex_search(sText, mFind, fWhile))
    {
        std::string test = mFind[0];
        int count = 0;
        std::string tmpText = mFind.suffix().str();
        std::smatch res;
        while (std::regex_search(tmpText, res, rFind))
        {
            count++;
            tmpText = res.suffix().str();
        }
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Ind of line with logic err:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(countOfNewStr - count)));
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem("Line number with logic err:"));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number((countOfNewStr - count) + 1)));
        sText = mFind.suffix().str();
    }
}
