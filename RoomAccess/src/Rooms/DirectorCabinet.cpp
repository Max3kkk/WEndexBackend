//
// Created by michael on 3/7/21.
//

#include "../../include/Rooms/DirectorCabinet.h"
DirectorCabinet::DirectorCabinet(int number, int floor): Room(number, floor) {
    accessLevel = red;
}

std::string DirectorCabinet::getRoomInfo() {
    return "Director cabinet" + Room::getRoomInfo();
}
