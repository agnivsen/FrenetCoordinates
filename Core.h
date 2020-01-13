#ifndef CORE_H
#define CORE_H

#include "Util.h"
#include "NumericalMethods.h"



class Core
{
public:
    void process_points(vector<point> points, point target);

private:
    curve obtain_curve(const vector<point> &points);
    int find_nearest_point(const curve &c, const point &target);
    frenet distance_to_curve(const curve &c, point &target, int min_index);
    void geodetic_distance(const curve &c, frenet &frame, int min_index);
};

#endif // CORE_H
