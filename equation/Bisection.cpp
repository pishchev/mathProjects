#include "Bisection.hpp"

double Bisection::Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const
{
    double Fx1 = func(x1);
    double Fx2 = func(x2);

    if (abs(Fx1) < eps)return x1;
    if (abs(Fx2) < eps)return x2;

    double xi = 0;
    double Fxi = 0;

	for( size_t i = 0 ; i< max_iter ; i ++)
	{
        double dx = (x2 - x1) / 2;
        xi = x1 + dx;

        Fxi = func(xi);

        if (std::signbit(Fx1) != std::signbit(Fxi))
        {
            x2 = xi;
        }
        else
        {
            x1 = xi;
        }

        if (std::isnan(x1) || std::isnan(x2))
        {
            return nan("3");
        }
		
        if (std::abs(x2 - x1) < eps)
        {
        	if (std::abs(Fxi) < std::abs(func(xi+2*eps)) && std::abs(Fxi) < std::abs(func(xi - 2 * eps)))
        	{
                return xi;
        	}
            return nan("1");
        }
	}
	
    return nan("1");
}
