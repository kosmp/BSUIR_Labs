#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <QString>

class StorageUnit
{
public:
    StorageUnit();
    QString group;
    int code;
    QString name;
    QString model;
    int cost;
    int count;
};

#endif // STORAGEUNIT_H
