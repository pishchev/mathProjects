#include "solver.hpp"

double Solver::Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double)) const
{
    double result = this->strategy_->Calculate(func, x1, x2 , eps , dfunc);
    return result;
}