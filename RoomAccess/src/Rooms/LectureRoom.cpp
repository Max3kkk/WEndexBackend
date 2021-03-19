//
// Created by michael on 3/7/21.
//

#include "../../include/Rooms/LectureRoom.h"

LectureRoom::LectureRoom(int number, int floor): Room(number, floor) {
    if (floor == 1) {   // Lecture rooms on the 1st floor have blue access level
        accessLevel = blue;
    } else {
        accessLevel = green;
    }
}

std::string LectureRoom::getRoomInfo() {
    return "Lecture room" + Room::getRoomInfo();
}
