#pragma once
#include "solver.hpp"

class Newton : public Strategy
{
    double Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const;

    double delt = 1e-14;

    double dF(double (*F)(double), double x) const;
};
