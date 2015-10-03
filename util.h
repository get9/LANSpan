#pragma once

#ifndef _LANSPAN_UTIL_H_
#define _LANSPAN_UTIL_H_

#include <vector>
#include <string>

void read_input(const char* filename, std::vector<Bridge>& bridges);

std::vector<std::string> split(const std::string str, const char delim);

#endif
