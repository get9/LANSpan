#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>

#include "util.h"
#include "bridge.h"
#include "lancontroller.h"

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t" << argv[0] << " inputfile N [N ...]" << std::endl;
        std::exit(1);
    }

    auto bridges = std::vector<Bridge>();
    auto send_order = std::list<int32_t>();
    parse_command_line(argc, argv, bridges, send_order);

    // Run algorithm to find MST
    LanController controller(bridges);
    controller.find_mst(send_order);
    std::cout << controller << std::endl;
}


