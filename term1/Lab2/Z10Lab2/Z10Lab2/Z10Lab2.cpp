#include <iostream>
using namespace std;

double sinx(double x)
{
    double n = x;
    double sum = 0;
    int i = 1;
        double k;
    do
    {
        sum += n;
        n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
        i++;
        if (n > 0)
        {
            k = n;
        }
        else 
        {
            k = -n;
        }
    } while (k > 0.000000001);

    return sum;
}

double cosx(double x)
{
    double n = 1;
    double sum = 0;
    int i = 1;
    double k;
    do
    {

        sum += n;
        n *= -1.0 * x * x / ((2 * i - 1) * (2 * i));
        i++;
        if (n > 0)
        {
            k = n;
        }
        else
        {
            k = -n;
        }
    } while (k > 0.000000001);

    return sum;
}

double lnnx(double x)
{
    double n = x - 1;
    double sum = 0;
    int i = 1;
    double k;
    do
    {
        sum += n;
        n *= -1.0 * x / ((2 * i));
        i++;
        if (n > 0)
        {
            k = n;
        }
        else
        {
            k = -n;
        }
    } while (k > 0.000000001);
    return sum;
}


int main()
{
    double x;
    cin >> x;
    double lnx;
    if (x < 0)
    {
        x = -x;
    }

    double y = (x - 1) / (x + 1);
    if (x > 2)
    {
        lnx = lnnx(y - 1) - lnnx(y + 1);
    }
    else if (x > 0 && x <= 2)
    {
        lnx = lnnx(x);
    }


    if (sinx(x) < cosx(x) && sinx(x) < lnx)
    {
        cout << "sinx is min" << endl;
    }
    else if (cosx(x) < sinx(x) && cosx(x) < lnx)
    {
        cout << "cosx is min" << endl;
    }
    else if (lnx < sinx(x) && lnx < cosx(x))
    {
        cout << "lnx is min" << endl;
    }
    

}

