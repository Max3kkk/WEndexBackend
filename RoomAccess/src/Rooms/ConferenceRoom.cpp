//
// Created by michael on 3/7/21.
//

#include "../../include/Rooms/ConferenceRoom.h"
ConferenceRoom::ConferenceRoom(int number, int floor): Room(number, floor) {
    if (floor == 1) { // Conference rooms on the 1st floor have blue access level
        accessLevel = blue;
    } else {
        accessLevel = yellow;
    }
}

std::string ConferenceRoom::getRoomInfo() {
    return "Conference room" + Room::getRoomInfo();
}
