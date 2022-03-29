#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <employee.h>
#include <QMessageBox>

class DoubleList
{
public:
    DoubleList();
    ~DoubleList();
    int maxLen;
    Employee** arr;
    int count;

    void addToEnd(const QString& name, const QString& surname, const QString& patronymic, const QString& departmentNum, const QString& posAtWork, const QString& dateStart);
    int getCount();
    void del(int pos);  // pos from 0
    Employee* getElem(int pos); // pos from 0
    void delAll();
};

#endif // DOUBLELIST_H
