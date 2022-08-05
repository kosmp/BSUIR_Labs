#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Key" << "Data");
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->comboBox->addItem("Add");
    ui->comboBox->addItem("Remove");
    ui->comboBox->addItem("Find info by key");
    ui->comboBox->addItem("Print preorder");
    ui->comboBox->addItem("Print postorder");
    ui->comboBox->addItem("Print inorder");

    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Key" << "Data");
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->resizeRowsToContents();
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Form::~Form()
{
    delete ui;
}

void Form::print(const TreeNode* root)
{
    ui->tableWidget_2->setRowCount(rows);
    ui->tableWidget_2->setItem(rows - 1, 0, new QTableWidgetItem(QString::number(root->key)));
    ui->tableWidget_2->setItem(rows - 1, 1, new QTableWidgetItem(root->data));
    rows++;
}

void Form::preorderPrint(TreeNode *root)
{
    if (root == NULL)
    {
       return;
    }
    print(root);
    //cout << root->data << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}


void Form::postorderPrint(TreeNode *root)
{
    if (root == NULL)
    {
       return;
    }
    postorderPrint(root->left);
    postorderPrint(root->right);
    print(root);
    //cout << root->data << " ";
}


void Form::inorderPrint(TreeNode *root)
{
    if (root == NULL)
    {
       return;
    }
    inorderPrint(root->left);
    print(root);
    //cout << root->data << " ";
    inorderPrint(root->right);
}

void Form::slot()
{
    for (int i = 0; i < 5; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(arr[i].first)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(arr[i].second));
    }
}


void Form::on_pushButton_2_clicked()
{
    ui->pushButton_2->setVisible(false);
    tree.addInfoFromArray(arr, 5);
    QMessageBox::warning(this, "Message","Done");
}


void Form::on_pushButton_3_clicked()
{
    ui->pushButton_3->setVisible(false);

    if (tree.mainRoot == nullptr)
    {
        QMessageBox::warning(this, "Message","No root in the tree.");
        ui->pushButton_3->setVisible(true);
        return;
    }

    TreeNode* a = tree.getMaxNode(tree.mainRoot);
    TreeNode* b = tree.getMinNode(tree.mainRoot);
    if (a != nullptr && b != nullptr)
    {
        QString tmp = a->data;
        a->data = b->data;
        b->data = tmp;
        QMessageBox::warning(this, "Message","Done");
    }
    else
    {
        QMessageBox::warning(this, "Message","No max and min nodes in the tree.");
    }
}


void Form::on_pushButton_clicked()
{
    if (ui->comboBox->currentText() == "Add")
    {
        QMessageBox::warning(this, "Message","Insert in additional line1 key(int number) to push and int additional line2 data to push.");
        int key = -1;
        key = ui->lineEdit->text().toInt();
        QString data = ui->lineEdit_2->text();
        if (ui->lineEdit->text().size() == 0 || ui->lineEdit_2->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You entered smth incorrect.");
            return;
        }

        tree.mainRoot = tree.insert(tree.mainRoot, key, data);
        QMessageBox::warning(this, "Message","Done. New node in the tree.");
    }
    else if (ui->comboBox->currentText() == "Remove")
    {
        QMessageBox::warning(this, "Message","Insert in additional line1 key(int number) so as to remove this node in the tree.");
        int key = -1;
        key = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You entered smth incorrect.");
            return;
        }

        if (tree.mainRoot == nullptr)
        {
            QMessageBox::warning(this, "Message","No root in the tree.");
            return;
        }

        tree.mainRoot = tree.remove(tree.mainRoot, key);
        QMessageBox::warning(this, "Message","Node was removed from the tree, if it had node with such key.");
    }
    else if (ui->comboBox->currentText() == "Find info by key")
    {
        QMessageBox::warning(this, "Message","Insert in additional line1 key(int number) so as to find this node in the tree.");
        int key = -1;
        key = ui->lineEdit->text().toInt();

        if (ui->lineEdit->text().size() == 0)
        {
            QMessageBox::warning(this, "Message","You entered smth incorrect.");
            return;
        }

        if (tree.mainRoot == nullptr)
        {
            QMessageBox::warning(this, "Message","No root in the tree.");
            return;
        }

        TreeNode* a = tree.getNodeByKey(tree.mainRoot, key);
        QString data;
        if (a != nullptr)
        {
            data = a->data;
            QMessageBox::warning(this, "Message", data);
        }
        else
        {
            QMessageBox::warning(this, "Message", "No such node in the tree.");
        }
    }
    else if (ui->comboBox->currentText() == "Print preorder")
    {
        rows = 1;
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Key" << "Data");
        if (tree.mainRoot != nullptr)
        {
            preorderPrint(tree.mainRoot);
        }
        else
        {
            QMessageBox::warning(this, "Message","No root");
            return;
        }
        QMessageBox::warning(this, "Message","Done");
    }
    else if (ui->comboBox->currentText() == "Print postorder")
    {
        rows = 1;
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Key" << "Data");
        if (tree.mainRoot != nullptr)
        {
            postorderPrint(tree.mainRoot);
        }
        else
        {
            QMessageBox::warning(this, "Message","No root");
            return;
        }
        QMessageBox::warning(this, "Message","Done");
    }
    else if (ui->comboBox->currentText() == "Print inorder")
    {
        rows = 1;
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "Key" << "Data");
        if (tree.mainRoot != nullptr)
        {
            inorderPrint(tree.mainRoot);
        }
        else
        {
            QMessageBox::warning(this, "Message","No root");
            return;
        }
        QMessageBox::warning(this, "Message","Done");
    }
}

