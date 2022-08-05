#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <functional>
#include <list>

template <class Key, class Value, class Compare = std::less<Key>>
class Tree
{
public:
    using value_type = std::pair<const Key, Value>;
    using key_compare = Compare;
    struct Node;
    std::list<Node*> listOfNodes;

    struct Node
    {
        std::pair<const Key, Value>* kv;
        Node* left;
        Node* right;
        Node* parent;
        char height;
        Node(Key k, Value newData, Node* prev)
        {
            parent = prev;
            kv = new std::pair<const Key, Value>(k, newData);
            //kv.first = k;
            //kv.second = newData;
            left = right = 0;
            height = 1;
        }

        ~Node()
        {
            delete kv;
        }
    };

    Node* mainRoot = nullptr;

    char height(Node* p)
    {
        return p ? p->height : 0;
    }


    int bfactor(Node* p)
    {
        return height(p->right) - height(p->left);
    }


    void fixheight(Node* p)
    {
        char hl = height(p->left);
        char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    Node* rotateright(Node* node)
    {
        Node* x = node->left;
        node->left = x->right;

        if (x->right != nullptr)
        {
            x->right->parent = node;
        }
        if (x != nullptr) x->parent = node->parent;
        if (node->parent == nullptr)    //root
        {
            this->mainRoot = x;
        }
        /*
        else if (node == node->parent->left) //left subtree
        {
            node->parent->left = x;
        }
        else //right subtree
        {
            node->parent->right = x;
        }
        */

        x->right = node;
        if (node != nullptr) node->parent = x;
        fixheight(node);
        fixheight(x);
        return x;
    }

    Node* rotateleft(Node* node)
    {
        Node* y = node->right;
        node->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = node;
        }
        if (y != nullptr) y->parent = node->parent;
        if (node->parent == nullptr) {			//root
            this->mainRoot = y;
        }
        /*
        else if (node == node->parent->left) //left subtree
        {
            node->parent->left = y;
        }
        else //right subtree
        {
            node->parent->right = y;
        }
        */

        y->left = node;
        if (node != nullptr) node->parent = y;

        fixheight(node);
        fixheight(y);
        return y;
    }

    /* WITHOUT parent in Node, old.
    Node* rotateright(Node* p)
    {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;

        fixheight(p);
        fixheight(q);
        return q;
    }

    Node* rotateleft(Node* q)
    {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;

        fixheight(q);
        fixheight(p);
        return p;
    }
    */


    Node* balance(Node* p)
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

    Node* insert(Key k, Value newData, Node* prev, Node* p)
    {
        if (!p)
        {
            Node* newNode = new Node(k, newData, prev);
            insertToList(listOfNodes, newNode);
            if (prev == nullptr)
                mainRoot = newNode;
            return newNode;
        }

        key_compare comparator1;
        if (comparator1(k, p->kv->first))
        {
            bool checkDup = false;
            if (p->left == nullptr)
            {
                if (p->kv->first == k)    // duplicate
                {
                    checkDup = true;
                }
                prev = p;
            }
            else
            {
                prev = nullptr;
            }
            if (checkDup == false)
                p->left = insert(k, newData, prev, p->left);
            else
                p->left = nullptr;
        }
        else
        {
            bool checkDup = false;
            if (p->right == nullptr)
            {
                if (p->kv->first == k)    // duplicate
                {
                    checkDup = true;
                }
                prev = p;
            }
            else
            {
                if (p->kv->first == k)    // duplicate
                {
                    return balance(p);
                }
                prev = nullptr;
            }
            if (checkDup == false)
                p->right = insert(k, newData, prev, p->right);
            else
                p->right = nullptr;
        }

        return balance(p);
    }

    Node* getMinNode(Node* root) {
        while (root->left) {
            root = root->left;
        }
        return root;
    }


    Node* getMaxNode(Node* root) {
        while (root->right) {
            root = root->right;
        }
        return root;
    }

    Node* getNodeByKey(Node* root, Key value) {
        while (root) {
            key_compare comparator;
            if (comparator(value, root->kv->first))
            {
                root = root->left;
                continue;
            }
            else if (comparator(root->kv->first, value))
            {
                root = root->right;
                continue;
            }
            else
            {
                return root;
            }
        }
        return NULL;
    }


    Node* removeMin(Node* p)
    {
        if (p->left == 0)
            return p->right;
        p->left = removeMin(p->left);
        return balance(p);
    }


    Node* remove(Key k, Node* p)
    {
        if (!p) return 0;
        key_compare comparator1;
        std::greater<Key> comparator2;
        if (comparator1(k, p->kv->first))
            p->left = remove(k, p->left);
        else if (comparator2(k, p->kv->first))
            p->right = remove(k, p->right);
        else //  k == p->key
        {
            Node* q = p->left;
            Node* r = p->right;
            removeFromList(listOfNodes, p);
            if (!r)
            {
                if (q != nullptr && p->parent == nullptr)
                {
                    q->parent = nullptr;
                    mainRoot = q;
                }
                else if (q != nullptr)
                {
                    q->parent = p->parent;
                }
                else if (q == nullptr && p->parent == nullptr)
                {
                    mainRoot = nullptr;
                }
                return q;
            }
            Node* min = getMinNode(r);
            if (min->right != nullptr)
                min->right->parent = min->parent;
            if (min->left != nullptr)
                min->left->parent = min->parent;
            min->right = removeMin(r);
            min->left = q;
            if (min->right != nullptr)
                min->right->parent = min;
            if (min->left != nullptr)
                min->left->parent = min;
            min->parent = p->parent;
            delete p;
            if (min->parent == nullptr)
                mainRoot = min;
            return balance(min);
        }
        return balance(p);
    }

    void insertToList(std::list<Node*>& list, Node* node)
    {
        if (list.empty())
        {
            list.push_back(node);
        }
        else
        {
            auto it = list.begin();
            while (it != list.end() && key_compare().operator()((*it)->kv->first, node->kv->first))
                ++it;
            list.insert(it, node);
        }
    }

    void removeFromList(std::list<Node*>& list, Node* node)
    {
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (*it == node)
            {
                list.erase(it);
                return;
            }
        }
    }
};

template <class Key, class Value, class Compare = std::less<Key>>
class map : public Tree<Key, Value, Compare>
{
public:
    using Tree = Tree<Key, Value, Compare>;
    using Node = typename Tree::Node;
    using value_type = std::pair<const Key, Value>;
    using key_compare = Compare;

protected:
    typename Tree::Node* root = nullptr;

public:
    struct iterator1    // basic iterator
    {
    public:
        Node* node = nullptr;
        Tree* tree = nullptr;

        iterator1() { }

        iterator1(const iterator1& iter) : node(iter.node), tree(iter.tree) { }

        iterator1(Node* node, Tree* tree) : node(node), tree(tree) { }

        iterator1& operator=(const iterator1& other)
        {
            node = other.node;
            tree = other.tree;
            return *this;
        }

        value_type& operator*()
        {
            return *node->kv;
        }

        value_type operator->()
        {
            return node->kv;
        }

        iterator1& operator++()
        {
            if (node->right != nullptr)
            {
                node = tree->getMinNode(node->right);
            }
            else
            {
                Key key = node->kv->first;
                node = node->parent;
                while (node != nullptr && key_compare().operator()(node->kv->first, key))
                {
                    node = node->parent;
                }
            }

            return *this;
        }

        iterator1 operator++(int)
        {
            auto it = *this;
            if (node->right != nullptr)
            {
                node = tree->getMinNode(node->right);
            }
            else
            {
                Key key = node->kv->first;
                node = node->parent;
                while (node != nullptr && key_compare().operator()(node->kv->first, key))
                {
                    node = node->parent;
                }
            }

            return it;
        }

        iterator1& operator--()
        {
            if (node == nullptr) {
                node = tree->getMaxNode(tree->mainRoot);
            }
            else if (node->left != nullptr) {
                node = tree->getMaxNode(node->left);
            }
            else
            {
                Key key = node->kv->first;
                node = node->parent;
                while (node != nullptr && key_compare().operator()(key, node->kv->first))
                {
                    node = node->parent;
                }
            }

            return *this;
        }

        iterator1 operator--(int)
        {
            auto it = *this;
            if (node == nullptr) {
                node = tree->getMaxNode(tree->mainRoot);
            }
            else if (node->left != nullptr)
            {
                node = tree->getMaxNode(node->left);
            }
            else
            {
                Key key = node->kv->first;
                node = node->parent;
                while (key_compare().operator()(key, node->kv->first) && node != nullptr)
                {
                    node = node->parent;
                }
            }

            return it;
        }

        bool operator==(const iterator1& other) { return node == other.node; }

        bool operator!=(const iterator1& other) { return node != other.node; }
    };

    struct iterator2    // based on list, according to condition
    {
    protected:
        typename std::list<Node*>::iterator it;
    public:
        iterator2() { }

        iterator2(typename std::list<Node*>::iterator it) : it(it) { }

        iterator2(const iterator2& iter) : it(iter.it) { }

        iterator2& operator=(const iterator2& other)
        {
            it = other.it;
            return *this;
        }

        iterator2& operator++()
        {
            ++it;
            return *this;
        }

        iterator2 operator++(int)
        {
            auto iter = *this;
            ++it;
            return iter;
        }

        iterator2& operator--()
        {
            --it;
            return *this;
        }

        iterator2 operator--(int)
        {
            auto iter = *this;
            --it;
            return iter;
        }

        bool operator==(const iterator2& other) { return other.it == it; }

        bool operator!=(const iterator2& other) { return other.it != it; }

        value_type& operator*() { return *(*it)->kv; }

        value_type operator->() { return (*it)->kv; }
    };

    Value& operator[](const Key& key)
    {
        iterator1 it = find(key);
        if (it.node != nullptr)
        {
            return it.node->kv->second;
        }
        else
        {
            insert(std::make_pair(key, ""));
            iterator1 it = find(key);
            return it.node->kv->second;
        }
    }

    Value& at(const Key& key)
    {
        iterator1 it = find(key);
        if (it.node != nullptr)
            return it.node->kv->second;
    }

    iterator1 find(const Key& key)
    {
        iterator1 res;
        if (root != nullptr)
            res.node = Tree::getNodeByKey(root, key);
        return res;
    }

    void erase(const Key& key)
    {
        root = Tree::remove(key, root);
    }

    void insert(const std::pair<const Key, Value>& p)
    {
        root = Tree::insert(p.first, p.second, nullptr, root);
    }

    size_t count(const Key& key)
    {
        iterator1 it = find(key);
        if (it.node != nullptr)
            return 1;
        else
            return 0;
    }

    iterator1 begin()
    {
        iterator1 res(Tree::getMinNode(root), nullptr);
        return res;
    }

    iterator1 end()
    {
        iterator1 res (Tree::getMaxNode(root)->right, nullptr);
        return res;
    }

    iterator2 l_begin()
    {
        return Tree::listOfNodes.begin();
    }

    iterator2 l_end()
    {
        return Tree::listOfNodes.end();
    }
};

#endif // MAP_H
