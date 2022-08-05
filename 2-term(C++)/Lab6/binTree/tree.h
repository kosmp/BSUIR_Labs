#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <QString>
#include "form.h"

struct TreeNode
{
    int key;
    QString data;
    TreeNode* left;
    TreeNode* right;
    char height;
    TreeNode(int k, QString newData)
    {
        key = k;
        left = right = 0;
        height = 1;
        data = newData;
    }
};

class Tree
{
public:
TreeNode* mainRoot = nullptr;
    void addInfoFromArray(std::pair<int, QString> arr[], int size)
    {
        for (int i = 0; i < size; i++)
            mainRoot = insert(mainRoot, arr[i].first, arr[i].second);
    }


    void changeWithMaxAndMinKeys(TreeNode* root)
    {
        QString tmp = getMinNode(root)->data;
        getMinNode(root)->data = getMaxNode(root)->data;
        getMaxNode(root)->data = tmp;
    }


    char height(TreeNode* p)
    {
        return p?p->height:0;
    }


    int bfactor(TreeNode* p)
    {
        return height(p->right)-height(p->left);
    }


    void fixheight(TreeNode* p)
    {
        char hl = height(p->left);
        char hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
    }


    TreeNode* rotateright(TreeNode* p)
    {
        TreeNode* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }


    TreeNode* rotateleft(TreeNode* q)
    {
        TreeNode* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }


    TreeNode* balance(TreeNode* p)
    {
        fixheight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // no need in balance
    }


    TreeNode* insert(TreeNode* p, int k, QString newData)
    {
        if(!p) return new TreeNode(k, newData);

        if(k < p->key)
        {
            p->left = insert(p->left, k, newData);
        }
        else
        {
            p->right = insert(p->right, k, newData);
        }

        return balance(p);
    }


    TreeNode* getMinNode(TreeNode* root) {
        while (root->left) {
            root = root->left;
        }
        return root;
    }


    TreeNode* getMaxNode(TreeNode* root) {
        while (root->right) {
            root = root->right;
        }
        return root;
    }


    TreeNode* getNodeByKey(TreeNode* root, int value) {
        while (root) {
            if (root->key > value) {
                root = root->left;
                continue;
            } else if (root->key < value) {
                root = root->right;
                continue;
            } else {
                return root;
            }
        }
        return NULL;
    }


    TreeNode* removeMin(TreeNode* p)
    {
        if (p->left == 0)
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }


    TreeNode* remove(TreeNode* p, int k)
    {
        if(!p) return 0;
        if(k < p->key)
            p->left = remove(p->left,k);
        else if(k > p->key)
            p->right = remove(p->right,k);
        else //  k == p->key
        {
            TreeNode* q = p->left;
            TreeNode* r = p->right;
            delete p;
            if(!r) return q;
            TreeNode* min = getMinNode(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }
};

#endif // TREE_H
