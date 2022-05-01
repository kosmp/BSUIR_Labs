#ifndef NODE_H
#define NODE_H

#include <QString>

template<class T>
class Node
{
public:
    Node() {}
    T data;
    Node* next;
    Node* prev;
};

#endif // NODE_H
