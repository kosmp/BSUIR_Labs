#include <iostream>

class Expression;
class Number;
class BinaryOperation;

class Expression
{
public:
    virtual double evaluate() const = 0;
};

class Number : public Expression
{
public:
    Number(double value) : value(value) { if (value >= 1000000000000000) exit(102); }
    double evaluate() const 
    {
        return value;
    }
private:
    double value;
};

class BinaryOperation : public Expression
{
public:
    BinaryOperation(Expression const* left, char op, Expression const* right) : left(left), op(op), right(right) { evaluate(); }
    ~BinaryOperation()
    {
        delete left;
        delete right;
    }
    double evaluate() const
    {
        double leftOperand = left->evaluate();
        double rightOperand = right->evaluate();
        if (op == '+') return leftOperand + rightOperand;
        else if (op == '-') return leftOperand - rightOperand;
        else if (op == '*') return leftOperand * rightOperand;
        else if (op == '/') return leftOperand / rightOperand;
        else exit(101);
    }
private:
    Expression const* left;
    Expression const* right;
    char op;
};

void function()
{
    Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '+', sube);
    std::cout << expr->evaluate() << std::endl;
    delete expr;
}

bool check_equals(Expression const* left, Expression const* right)
{
    return *((size_t**)left) == *((size_t**)right);
}

int main()
{
    function();
    Expression* sube = new BinaryOperation(new BinaryOperation(new Number(4.5), '*', new Number(5)), '*', new BinaryOperation(new Number(4.5), '*', new Number(5)));
    std::cout << sube->evaluate() << std::endl;
    Expression* expr = new BinaryOperation(new Number(3), '+', sube);

    std::cout << check_equals(sube, expr);
}