//
// Created by michael on 3/7/21.
//

#include "../../include/Rooms/ClassRoom.h"

ClassRoom::ClassRoom(int number, int floor) : Room(number, floor) {
    accessLevel = green;
}

std::string ClassRoom::getRoomInfo() {
    return "Class room" + Room::getRoomInfo();
}
