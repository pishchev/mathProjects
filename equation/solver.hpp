#pragma once
#include <iostream>

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual double Calculate(double (*func)(double), double x1, double x2, double eps , double(*dfunc)(double) ) const = 0;
protected:
    size_t max_iter = 1000000;
};
class Solver
{
private:
    std::shared_ptr<Strategy> strategy_;
 
public:
    Solver(std::shared_ptr<Strategy> strategy) : strategy_(strategy){}
    double  Calculate(double (*func)(double), double x1, double x2, double eps, double(*dfunc)(double) = nullptr) const;
};