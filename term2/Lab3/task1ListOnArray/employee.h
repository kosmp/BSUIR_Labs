#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
public:
    Employee();
    QString name;
    QString surname;
    QString patronymic;
    QString departmentNum;
    QString posAtWork;
    QString dateStart;
    int next;
    int prev;
};

#endif // EMPLOYEE_H
