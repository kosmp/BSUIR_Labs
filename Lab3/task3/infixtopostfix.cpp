#include "infixtopostfix.h"

InfixToPostfix::InfixToPostfix()
{

}

int InfixToPostfix::priority(QChar a)
{
    int temp;
    if (a == '*' || a == '/')
        temp = 2;
    else  if (a == '+' || a == '-')
        temp = 1;
    return temp;
}

QString InfixToPostfix::convert(QString infixLine)
{
    Stack<QChar> opStack;
    QString postfixLine;
    for (int i = 0; i < infixLine.size(); i++)
    {
        if (infixLine[i] == '(')
            opStack.push(infixLine[i]);
        else if (infixLine[i] == ')')
        {
              while (opStack.top() != '(')
                  postfixLine.append(opStack.pop());
              opStack.pop();    // и удалили найденную скобку
        }
        else if (infixLine[i] >= 'a' && infixLine[i] <= 'z')
            postfixLine.push_back(infixLine[i]);
        else if (infixLine[i] == '+' || infixLine[i] == '-' || infixLine[i] == '*' || infixLine[i] == '/')
        {
            if (opStack.isEmpty() || opStack.top() == '(')
                opStack.push(infixLine[i]);
            else if (priority(opStack.top()) < priority(infixLine[i])) // если входящий оператор имеет более высокий приоритет, чем вершина opStack. (infixLine[i] == '*' || infixLine[i] == '/') && (opStack.top() == '+' || opStack.top() == '-')
                opStack.push(infixLine[i]);
            else if (priority(opStack.top()) >= priority(infixLine[i])  || opStack.top() == '(' || opStack.top() == ')') // если входящий оператор имеет более низкий или равный приоритет, чем вершина opStack. ((infixLine[i] == '+' || infixLine[i] == '-') && (opStack.top() == '*' || opStack.top() == '/' || infixLine[i] == '+' || infixLine[i] == '-')) || opStack.top() == '(' || opStack.top() == ')'
            {
                while (!opStack.isEmpty() && priority(opStack.top()) >= priority(infixLine[i]) && opStack.top() != '(')
                    postfixLine.append(opStack.pop());
                opStack.push(infixLine[i]);
            }
        }
    }
    while(!opStack.isEmpty())   // выталкиваем оставшиеся в результат
        postfixLine.append(opStack.pop());
    return postfixLine;
}

double InfixToPostfix::calcPostfix(QString line, double a, double b, double c, double d, double e)
{
    Stack<double> operandStack;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] >= 'a' && line[i] <= 'e')
        {
            if (line[i] == 'a') operandStack.push(a);
            else if (line[i] == 'b') operandStack.push(b);
            else if (line[i] == 'c') operandStack.push(c);
            else if (line[i] == 'd') operandStack.push(d);
            else if (line[i] == 'e') operandStack.push(e);
        }
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
        {
            if (operandStack.Count() >= 2)
            {
                double operand2 = operandStack.pop();
                double operand1 = operandStack.pop();
                operandStack.push(doMath(line[i], operand1, operand2));
            }
        }
    }
    return operandStack.pop();
}

double InfixToPostfix::doMath(QChar op, double op1, double op2)
{
    if (op == "*")
        return (double)op1 * (double)op2;
    else if (op == "/")
        return (double)op1 / (double)op2;
    else if (op == "+")
        return (double)op1 + (double)op2;
    else
        return (double)op1 - (double)op2;
}
