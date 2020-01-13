#include "Core.h"
#include "IO.h"

NumericalMethods compute;
IO print;

/**
 * Processes the input points and generates the Frenet coodinates.
 * This is the master-fuction triggering all the sub-modules required for solving the problem
 *
 * @param points List of way-points obtained as input
 * @param target Cartesian coordinate of input point
 * @return void
 */
void Core::process_points(vector<point> points, point target)
{
    curve c  = obtain_curve(points);                              //obtain the equation of the curve

    int closest_point = find_nearest_point(c, target);            //find the point among the input waypoints that lies closest to the input/target point

    frenet frame = distance_to_curve(c, target, closest_point);   //find the closest point to the input/target point on the continuous curve and get the distance

    geodetic_distance(c, frame, closest_point);                   //find the distance to the closest point on the continuous curve from the curve's origin

    print.print_frenet_frame(frame,c);                            //print output to console
}


/**
 * Fits a polygon to the points obtained as input.
 * For now, a second order polynomial has been approximated
 * (Can be switched to higher order polynomial, or B-spline... if required)
 *
 * @param points List of way-points obtained as input
 * @return curve describing the coefficients of the polynomial
 */
curve Core::obtain_curve(const vector<point> &points)
{
    curve c; vector<double> coeff;
    compute.poly_fit_points(points, coeff, ORDER);

    c.points = points;
    c.order = ORDER;
    c.coefficients = coeff;
    return c;
}


/**
 * Find the waypoint nearest to the target
 *
 * @param curve Describes the coefficients of the polynomial
 * @param target The input point for which the Frenet frame is to be obtained
 * @return index of the point (among the input way points) which lies nearest to the target
 */
int Core::find_nearest_point(const curve &c, const point &target)
{
    int min_index = NEGATIVE_ONE;
    double min_dist = VERY_LARGE_NUMBER;
    double dist;
    double prev_dist;
    for(int i = 0; i < c.points.size(); i++)
    {
        dist = compute.eucledian_distance(c.points[i], target);
        if(dist < min_dist)
        {
            min_index = i;
            min_dist = dist;
        }

        if((i > 0) && (dist > prev_dist))
        {
            return min_index;
        }

        prev_dist = dist;

    }

    return min_index;
}


/**
 * Find the closest distance of the target point from the curve
 *
 * @param curve Describes the coefficients of the polynomial
 * @param target The input point for which the Frenet frame is to be obtained
 * @param min_index Index of the point (among the input way points) which lies nearest to the target
 * @return frenet frame of the target point
 */
frenet Core::distance_to_curve(const curve &c, point &target, int min_index)
{
    float alpha = ALPHA;
    int max_iteration = MAXIMUM_ITERATION;
    frenet frame = compute.steepest_gradient_descent(c, target, min_index, alpha, max_iteration);
    return frame;
}


/**
 * Compute the distance of the closest point to the target from the origin, along the curve
 *
 * @param curve Describes the coefficients of the polynomial
 * @param frame Frenet frame of the target (the geodetic distance is updated here)
 * @param min_index Index of the point (among the input way points) which lies nearest to the target
 * @return void
 */
void Core::geodetic_distance(const curve &c, frenet &frame, int min_index)
{
    int last_index = NEGATIVE_ONE;
    double dist_end = 0.0f;
    bool compute_distance = false;
    float cross_prod;
    if((min_index >= 0) && (min_index < c.points.size()))
    {
        float dist_1 = compute.eucledian_distance(c.points[min_index - 1], frame.cartesian_point);
        float dist_2 = compute.eucledian_distance(c.points[min_index], frame.cartesian_point);

        if(dist_1 < dist_2)
        {
            last_index = min_index - 1;
            dist_end = dist_1;
            cross_prod = compute.cross_product(c.points[min_index - 1], frame.cartesian_point);
        }
        else
        {
            last_index = min_index;
            dist_end = dist_2;
            cross_prod = compute.cross_product(c.points[min_index], frame.cartesian_point);
        }

        compute_distance = true;

    }
    else if(min_index == 0)
    {
        last_index = 0;
        frame.geodetic_distance = compute.eucledian_distance(c.points[0],frame.cartesian_point);
        cross_prod = compute.cross_product(c.points[0], frame.cartesian_point);
    }
    else
    {
        //we are doomed
        _fatal_("Invalid index ("<<min_index<<") for point-on-curve closest to the target point. Can't proceed.")
    }


    if(compute_distance)
    {
        double dist = 0.0f;

        for(int i = 1; i <= last_index; i++)
        {
            dist += compute.eucledian_distance(c.points[i], c.points[i-1]);
        }

        dist+=dist_end;
        frame.geodetic_distance = dist;
    }

    if(cross_prod > 0)
        frame.direction = true;
    else
        frame.direction = false;
}



