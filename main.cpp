#include <iostream>
#include <vector>
#include <cstdlib>

#include "util.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << argv[0] << "[inputfile]" << std::endl;
        std::exit(1);
    }

    auto bridges = std::vector<Bridge>();
    read_input(argv[1], bridges);
}


