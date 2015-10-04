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
        auto msg = ConfigMessage(l.first, l.second.best_config);
        msgs.push_back(msg);
    }
    return msgs;
}

// TODO: Implement
void Bridge::receive(ConfigMessage msg)
{
    // do stuff
}

// TODO: Implement
std::ostream& operator<<(std::ostream& s, const Bridge& b)
{
    return s;
}
