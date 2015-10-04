#include <iostream>
#include <vector>
#include <cstdlib>

#include "util.h"

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << argv[0] << "inputfile N [N ...]" << std::endl;
        std::exit(1);
    }

    auto bridges = std::vector<Bridge>();
    auto send_order = std::vector<int32_t>();
    parse_command_line(argc, argv, bridges, send_order);
    parse_input_file(argv[1], bridges);
}


