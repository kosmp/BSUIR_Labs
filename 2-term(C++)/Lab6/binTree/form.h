#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <tree.h>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void print(const TreeNode* root);
    int rows = 1;
    void preorderPrint(TreeNode *root);
    void postorderPrint(TreeNode *root);
    void inorderPrint(TreeNode *root);

private:
    Ui::Form *ui;
    Tree tree;
    std::pair<int, QString> arr[5] {{23, "ab"}, {4, "cd"}, {17, "hd"}, {9, "fd"}, {27, "ng"}};

public slots:
    void slot();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
};

#endif // FORM_H
