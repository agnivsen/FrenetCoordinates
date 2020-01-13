# IVEX - Frenet Coordinates
This project converts a point from cartesian coordinates to its equivalent representation in Frenet coordinate system, given a set of input points describing the waypoints of a curve traced out by a hypothetical mobile vehicle/robot.

# Software

## Dependencies
  * CMAKE 2.6
  * Eigen 3.3

## Build Instructions
In the source directory: 
  * mkdir build
  * cd build
  * cmake ..
  * make
  
## Running the code
./FrenetSol -m /path/to/input/points/ -x X-coordinates-of-input-point -y Y-coordinates-of-input-point

### Example:
    ./FrenetSol -m /random/directory/reference_points.pb.txt -x 1.0 -y 2.0
    
    
# Assumptions
The program developed here derived the Frenet coordinates with some assumptions. They are listed below:

1. The waypoints provided are sequential and starts from the origin
2. Works only for 2D points
3. It is assumed that the curve describing the provided points can be approximated properly with a second order polynomial equation. This may not be true for all cases, but generalizing the proposed approach to higher order polynomial/B-Spline is trivial
4. The cartesian coordinates of the waypoints provided are not noisy and does not contain outliers. Mechanism for robust handling of noisy data has not been implemented in this project
5. The waypoints does not represent a self-intersecting curve

# Brief Description
The algorithm works using the following steps
1. Given a set of input points, it fits a second order polynomial to the points (Eigen is used for this)
2. From the input target point (for which the Frenet coordinate is to be determied), it finds the closest waypoint (from the input data). However, this closest waypoint is not guaranteed to be the closest points on the curve from the target
3. A steepest gradient descent method is used to arrive at the actual closest point, starting from the initial estimate derived in step 2 (implemented from scratch)
4. The distance of the closest point derived in step 3 to the target should be along the normal to the curve. The orientation of the target w.r.t the curve is derived by a cross product with the vector along the direction of motion


