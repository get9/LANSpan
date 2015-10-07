#pragma once

#ifndef _LANSPAN_LANCONTROLLER_H_
#define _LANSPAN_LANCONTROLLER_H_

#include <vector>
#include <map>
#include <iostream>
#include <list>

#include "bridge.h"

class LanController {
public:
    LanController();

    LanController(std::vector<Bridge> bridges);

    void find_mst(std::list<int32_t> msg_send_order);

    std::vector<Bridge> bridges() const {
        return bridges_;
    }

    friend std::ostream& operator<<(std::ostream& s, const LanController& l);

private:
    std::vector<Bridge> bridges_;
    std::map<std::string, std::vector<Bridge*>> bridges_for_lan_;

};

#endif
