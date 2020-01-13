#ifndef IO_H
#define IO_H
#include <Util.h>

using namespace std;
class IO
{
public:
    input read_string(const vector<char *> data);
    std::vector<char *> parse_argument(int argc, char * argv[]);
    char* getCmdOption(char ** begin, char ** end, const std::string & option);
    void print_frenet_frame(const frenet &frame, const curve &c);
};
#endif // IO_H
