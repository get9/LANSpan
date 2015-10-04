#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "util.h"

void parse_command_line(int argc, char** argv, std::vector<Bridge>& bridges,
        std::vector<int32_t>& send_order)
{
    parse_input_file(argv[1], bridges);

    // Parse rest of line for ordering
    for (auto i = 2; i < argc; ++i) {
        send_order.push_back(std::stoi(std::string(argv[i])));
    }
}

void parse_input_file(char* filename, std::vector<Bridge>& bridges)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[error]: Could not open file " << filename << std::endl;
        std::exit(1);
    }
    auto line = std::string();

    // For every line in input file
    while (std::getline(file, line)) {
        auto elements = split(line);
        int32_t bridge_num = std::stoi(elements[0]);
        auto lans = std::vector<std::string>();

        // Move lan parts from line into a separate vector
        std::move(elements.begin()+1, elements.end(), std::back_inserter(lans));
        bridges.push_back(Bridge(bridge_num, lans));
    }
}

std::vector<std::string> split(const std::string str, const char delim)
{
    auto v = std::vector<std::string>();
    auto ss = std::stringstream(str);
    auto unit = std::string();
    while (std::getline(ss, unit, delim)) {
        v.push_back(unit);
    }
    return v;
}
