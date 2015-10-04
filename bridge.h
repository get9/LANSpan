#pragma once

#ifndef _LANSPAN_BRIDGE_H_
#define _LANSPAN_BRIDGE_H_

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

struct LanConfig {
    int32_t sender_id;
    int32_t assumed_root;
    int32_t distance;

    LanConfig(int32_t id) : sender_id(id), assumed_root(id), distance(-1) { }
};

struct Link {
    bool is_active;
    LanConfig best_config;

    Link(int32_t id) : is_active(false) {
        best_config = LanConfig(id);
    }
};

struct ConfigMessage {
    std::string receiver;
    LanConfig config;

    ConfigMessage(std::string recv, LanConfig cfg) : receiver(recv), config(cfg) { }
};

class Bridge {
public:
    Bridge();

    Bridge(int32_t id, std::vector<std::string> lans);

    // Sends config message to all connected nodes
    std::vector<ConfigMessage> broadcast() const;

    void receive(ConfigMessage msg);

    friend std::ostream& operator<<(std::ostream& s, const Bridge& b);

    bool is_root() const { return is_root_; }

    std::unordered_map<std::string, Link> links() const { return links_; }

private:
    int32_t id_;
    std::unordered_map<std::string, Link> links_;
    bool is_root_;

};

#endif
