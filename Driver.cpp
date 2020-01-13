#include <Util.h>
#include <IO.h>
#include <Core.h>

IO io;
Core core;
point p;


int main(int argc, char * argv[])
{
    vector<char *> arguments = io.parse_argument(argc,argv);
    input data = io.read_string(arguments);
    core.process_points(data.points, data.target);
}
