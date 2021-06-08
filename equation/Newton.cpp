#include "Newton.hpp"

double Newton::Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const
{
    double x = (x1 + x2) /2;
    double Fx1 = func(x);
    if (abs(Fx1) < eps)return x;
    double xi = x - Fx1 / dfunc(x);

    for (size_t i = 0; i < max_iter; i++)
    {
        x = xi;
        xi = x - func(x) / dfunc(x);

        if (std::isnan(xi) || std::isnan(x))
        {
            return nan("3");
        }

        if (std::abs(xi - x) < eps)
        {
            if (xi < x1 || xi > x2)
            {
                return nan("3");
            }

            return xi;
        }
    }
    return nan("3");
}
