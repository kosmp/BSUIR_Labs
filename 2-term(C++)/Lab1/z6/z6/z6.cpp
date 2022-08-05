#include <iostream>

class Expression
{
public:
    virtual void evaluate() {}
};

class Number : public Expression
{
    void func() {}
};

class BinaryOperation : public Expression
{
    void func() {}
};

bool check_equals(Expression const* left, Expression const* right)
{
    return *((size_t**)left) == *((size_t**)right);
}

int main()
{
    Expression* left = new Number();
    Expression* right = new Number();
    std::cout << std::boolalpha << check_equals(left, right);
}