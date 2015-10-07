#include "bridge.h"

Bridge::Bridge() : id_(0), best_config_(nullptr) {}

// Creates a new bridge and initializes its links to have config
// id = id
// root = id
// distance = 0
// and set to be root
Bridge::Bridge(int32_t id, std::vector<std::string> lans) : id_(id), is_root_(true)
{
    for (auto l : lans) {
        links_.emplace(l, std::make_shared<Link>(id));
    }
    best_config_ = &(links_.begin()->second->config);
}

// Send messages to all active links
std::vector<ConfigMessage> Bridge::broadcast() const
{
    std::cout << "Bridge " << id_ << " sending to ";
    auto msgs = std::vector<ConfigMessage>();
    for (auto& l : links_) {
        // Only send out on active links
        if (!l.second->is_active) {
            continue;
        }
        std::cout << l.first << ", ";

        // If not the root, need to adjust sending id to be bridge's id
        if (!is_root_) {
            l.second->config.sender_id = id_;
        }
        msgs.emplace_back(l.first, l.second->config);
    }
    std::cout << std::endl;
    return msgs;
}

// Actually "receives" a sent message
void Bridge::receive(ConfigMessage msg)
{
    // Find the link that this message is address to (NOTE: assumes the msg
    // is addressed to a link this bridge has)
    /*auto& link = [msg, this]() {
        try {
            return links_.at(msg.lan);
        } catch (std::out_of_range ex) {
            std::cerr << "Bridge " << id_ << " got a message from "
                      << msg.config.sender_id
                      << " but there's no corresponding link";
            std::exit(1);
        }
    }();*/
    // XXX Not handling if msg.lan is not in links_
    std::cout << "Bridge " << id_ << " recv " << msg.config << " from " << msg.config.sender_id << std::endl;
    auto& link = links_.at(msg.lan);

    // First check if the msg has a root with a smaller ID
    if (msg.config.assumed_root < link->config.assumed_root) {
        std::cout << "Bridge " << id_ << " found root "
                  << msg.config.assumed_root << std::endl;
        is_root_ = false;

        // Need to broadcast new config to all links since this is now best
        // config
        for (auto& p : links_) {
            p.second->config = msg.config;
            p.second->config.distance++;
            p.second->config.sender_id = id_;
        }
    }

    // Then check if msg has same root but shorter distance
    if (msg.config.assumed_root == link->config.assumed_root &&
        msg.config.distance < link->config.distance) {
        std::cout << "Bridge " << id_ << " found shorter distance "
                  << msg.config.distance << " from Bridge "
                  << msg.config.sender_id << std::endl;
        link->config = msg.config;
        link->config.distance++;
    }

    // Then check if msg has same root, same distance, but smaller sender_id
    // Disable if so
    if (msg.config.assumed_root == link->config.assumed_root &&
        (msg.config.distance < link->config.distance ||
        (msg.config.distance == link->config.distance &&
         msg.config.sender_id < link->config.sender_id))) {
        if (msg.config.sender_id != link->config.assumed_root) {
            link->config = msg.config;
            link->config.distance++;
            std::cout << "Disabling link " << msg.lan << " for bridge "
                      << id_ << std::endl;
            link->is_active = false;
        }
    }
}

std::ostream& operator<<(std::ostream& s, const Bridge& b)
{
    s << "id = " << b.id_ << std::endl;
    for (auto& l : b.links_) {
        s << "    " << l.first << " " << *(l.second) << std::endl;
    }
    return s;
}
