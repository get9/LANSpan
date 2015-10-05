#include "bridge.h"

Bridge::Bridge() : id_(0) {}

Bridge::Bridge(int32_t id, std::vector<std::string> lans) : id_(id), is_root_(true)
{
    for (auto l : lans) {
        links_.emplace(l, Link(id));
    }
}

std::vector<ConfigMessage> Bridge::broadcast() const
{
    auto msgs = std::vector<ConfigMessage>();
    for (auto& l : links_) {
        msgs.emplace_back(l.first, l.second.best_config);
    }
    return msgs;
}

// TODO: Implement
void Bridge::receive(ConfigMessage msg)
{
    // Check if new message contains better config than the one we already have
    bool better = false;
    auto config = links_[msg.receiver].best_config;
    if (msg.config.assumed_root < config.assumed_root ||
        (msg.config.assumed_root == config.assumed_root &&
         msg.config.distance < config.distance) ||
        (msg.config.assumed_root == config.assumed_root &&
         msg.config.distance == config.distance &&
         msg.config.sender_id < config.sender_id)) {
        better = true;
    }
}

std::ostream& operator<<(std::ostream& s, const Bridge& b)
{
    s << "id = " << b.id_ << std::endl;
    for (auto& l : b.links_) {
        s << "    " << l.first << " " << l.second << std::endl;
    }
    return s;
}
