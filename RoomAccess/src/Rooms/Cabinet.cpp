//
// Created by michael on 3/7/21.
//

    #include "../../include/Rooms/Cabinet.h"
    Cabinet::Cabinet(int number, int floor): Room(number, floor) {
        accessLevel = yellow;
    }

    std::string Cabinet::getRoomInfo() {
    return "Cabinet" + Room::getRoomInfo();
}
