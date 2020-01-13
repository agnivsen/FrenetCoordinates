#include <IO.h>



input IO::read_string(const vector<char *> data)
{
    ifstream infile(data[0]);
    string line;
    vector<point> points;
    input ip;

    double x,y;
    int up = 0;

    while(getline(infile, line))
    {
        if(!(line.compare("points {")==0 || (line.compare("}")==0)))
        {
            string X = line.substr(5);

           if(up==0)
           {
               x = std::stof(X.c_str());
           }
           else
           {
               y = std::stof(X);
           }

           up++;

           if(up == 2)
           {
               point A;
               A.x = x; A.y = y;
               points.push_back(A);
               up = 0;
           }
        }

    }

    ip.points = points;
    ip.target.x = stof(data[1]);
    ip.target.y = stof(data[2]);


    return ip;
}


char* IO::getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
        { return *itr; }
    return 0;
}

std::vector<char *> IO::parse_argument(int argc, char * argv[])
{
    std::vector<char *> arguments;
    bool data_check = false;
    bool x_check = false;
    bool y_check = false;

    char * point_path = getCmdOption(argv, argv + argc, "-m");
    if (point_path)
    {
        _log_("Path to input points:"<<point_path)
        data_check = true;
        arguments.push_back(point_path);
    }
    char * x_coord = getCmdOption(argv, argv + argc, "-x");
    if (x_coord)
    {
        x_check = true;
        arguments.push_back(x_coord);
    }

    char * y_coord = getCmdOption(argv, argv + argc, "-y");
    if (y_coord)
    {
        y_check = true;
        arguments.push_back(y_coord);
    }

    if(!(data_check && x_check && y_check))
    {
        _fatal_("Usage: ./FrenetSol -m /path/to/input/points/ -x X-coordinates-of-input-point -y Y-coordinates-of-input-point")
    }

    return arguments;
}

void IO::print_frenet_frame(const frenet &frame, const curve &c)
{
    _info_(PRECISION<<"Equation decsribing the curve: y = ("<<c.coefficients[2]<<")x^2 + ("<<c.coefficients[1]<<")x + ("<<c.coefficients[0]<<")")
    _info_("The input point ("<<frame.cartesian_point.x<<","<<frame.cartesian_point.y<<") lies at a distance of "<<frame.geodetic_distance<<" units along the curve, to the <"<<(frame.direction?"LEFT":"RIGHT")<<"> of the direction of motion, at a lateral distance of "<<(frame.direction?"-":"+")<<frame.lateral_distance<<" from the curve")

}
