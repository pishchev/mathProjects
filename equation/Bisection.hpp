#pragma once
#include "solver.hpp"

class Bisection : public Strategy
{
public:
    double Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const override;
};
