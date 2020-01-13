#ifndef NUMERICALMETHODS_H
#define NUMERICALMETHODS_H

#include "Util.h"

class NumericalMethods
{
public:
    double eucledian_distance(const point A, const point B);
    double cross_product(const point A, const point B);
    void poly_fit_points(const vector<point> &points, vector<double> &coeff, int order);
    frenet steepest_gradient_descent(const curve &c, point &target, int init_index, float alpha, int max_iter);

private:
    double evaluate(const double x, const double a1, const double a2, const double a3);
    double gradient(const double x, const double p, const double q, const double a1, const double a2, const double a3);
    double residual(const double x, const double p, const double q, const double a1, const double a2, const double a3);
};

#endif // NUMERICALMETHODS_H
