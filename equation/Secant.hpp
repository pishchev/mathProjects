#pragma once
#include "solver.hpp"

class Secant : public Strategy
{
    double Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const;
};
