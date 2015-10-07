#pragma once

#ifndef _LANSPAN_UTIL_H_
#define _LANSPAN_UTIL_H_

#include <vector>
#include <string>
#include <list>

#include "bridge.h"

void parse_command_line(int argc, char** argv, std::vector<Bridge>& bridges, std::list<int32_t>& send_order);

void parse_input_file(const char* filename, std::vector<Bridge>& bridges);

std::vector<std::string> split_space(const std::string str);

#endif
