#pragma once

#ifndef _LANSPAN_LANCONTROLLER_H_
#define _LANSPAN_LANCONTROLLER_H_

#include <vector>
#include <unordered_map>

#include "bridge.h"

class LanController {
public:
    LanController();

    LanController(std::vector<Bridge> bridges);

    void find_mst(std::list<int32_t> msg_send_order);

    decltype(bridges_) bridges() const { return bridges_; }

private:
    std::vector<Bridge> bridges_;
    std::unordered_map<std::string, std::vector<Bridge*>> bridges_for_lan_;

};

#endif
