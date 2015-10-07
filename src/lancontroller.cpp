#include "lancontroller.h"

LanController::LanController() { }

LanController::LanController(std::vector<Bridge> bridges) : bridges_(bridges)
{
    for (auto& b : bridges_) {
        for (auto& pair : b.links()) {
            if (bridges_for_lan_.find(pair.first) == std::end(bridges_for_lan_)) {
                bridges_for_lan_[pair.first] = std::vector<Bridge*>();
                bridges_for_lan_[pair.first].push_back(&b);
            } else {
                bridges_for_lan_[pair.first].push_back(&b);
            }
        }
    }
}

// Main method that finds the MST for the network
void LanController::find_mst(std::list<int32_t> msg_send_order)
{
    // Assume id's are 1-indexed, but vector<Bridge> is 0-indexed
    for (auto i : msg_send_order) {

        // Gather messages broadcast by bridge i
        auto msgs = bridges_[i-1].broadcast();

        // Send them all to their receivers
        for (auto m : msgs) {

            // Figure out who is attached to the designated LAN
            auto receivers = bridges_for_lan_[m.lan];

            // Make them receive the message
            for (auto recv : receivers) {
                if (recv->id() != m.config.sender_id) {
                    recv->receive(m);
                }
            }
        }
    }
}

// Print method
std::ostream& operator<<(std::ostream& s, const LanController& l)
{
    for (auto b : l.bridges_) {
        s << b;
    }
    return s;
}
