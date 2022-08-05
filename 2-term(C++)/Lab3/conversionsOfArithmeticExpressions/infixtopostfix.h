#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

#include <stack.h>
#include <QString>

class InfixToPostfix
{
public:
    InfixToPostfix();
    QString convert(QString infixLine);
    double calcPostfix(QString line, double a, double b, double c, double d, double e);
    double doMath(QChar op, double op1, double op2);
private:
    int priority(QChar a);
};

#endif // INFIXTOPOSTFIX_H
