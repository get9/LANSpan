#pragma once

#ifndef _LANSPAN_BRIDGE_H_
#define _LANSPAN_BRIDGE_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

struct LanConfig {
    int32_t sender_id;
    int32_t assumed_root;
    int32_t distance;

    LanConfig() : sender_id(0), assumed_root(0), distance(0) { }

    LanConfig(int32_t id) : sender_id(id), assumed_root(id), distance(0) { }

    friend std::ostream& operator<<(std::ostream& s, const LanConfig& c) {
        return s << "(" << c.sender_id << ", " << c.distance
                 << ", " << c.assumed_root << ")";
    }
};

struct Link {
    bool is_active;
    LanConfig config;

    Link(int32_t id) : is_active(true) {
        config = LanConfig(id);
    }

    friend std::ostream& operator<<(std::ostream& s, const Link& l) {
        return s << l.config << (l.is_active ? " *" : " ");
    }
};

// We get operator= for free!
struct ConfigMessage {
    std::string lan;
    LanConfig config;

    ConfigMessage(std::string l, LanConfig cfg) : lan(l), config(cfg)
    { }
};

class Bridge {
public:
    Bridge();

    Bridge(int32_t id, std::vector<std::string> lans);

    // Sends config message to all connected nodes
    std::vector<ConfigMessage> broadcast() const;

    // Explicit call to receive a message
    void receive(ConfigMessage msg);

    friend std::ostream& operator<<(std::ostream& s, const Bridge& b);

    std::map<std::string, std::shared_ptr<Link>> links() const {
        return links_;
    }

    const int32_t id() const { return id_; }

private:
    const int32_t id_;
    std::map<std::string, std::shared_ptr<Link>> links_;
    LanConfig* best_config_;
    bool is_root_;

};

#endif
