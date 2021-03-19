//
// Created by michael on 3/7/21.
//

#include "../../include/Rooms/Room.h"
// vector is used for easier printing names of enums into console
const std::vector<std::string> Room::accessLevelNames = {"not specified", "Blue", "Green", "Yellow", "Red"};
int Room::instance = 0;

Room::Room(int number, int floor) :
    number(number), floor(floor) {
    id = ++instance;
}

int Room::getNumber() const {
    return number;
}

AccessLevel Room::getAccessLevel() const {
    return accessLevel;
}

void Room::addToBlackList(int userId) {
    if (!isInBlackList(userId)) {
        blackList.push_back(userId);
    }
}

void Room::addToWhiteList(int userId) {
    if (!isInWhiteList(userId)) {
        whiteList.push_back(userId);
    }
}

void Room::removeFromWhiteList(int userId) {
    if (isInWhiteList(userId)) {
        whiteList.erase(std::find(whiteList.begin(), whiteList.end(),userId));
    }
}

void Room::removeFromBlackList(int userId) {
    if (isInBlackList(userId)) {
        blackList.erase(std::find(blackList.begin(), blackList.end(),userId));
    }
}
// checks if user is in the black list of this room
bool Room::isInBlackList(int userId) {
    return !blackList.empty() && std::find(blackList.begin(), blackList.end(),userId) != blackList.end();
}
// checks if user is in the white list of this room
bool Room::isInWhiteList(int userId) {
    return !whiteList.empty() && std::find(whiteList.begin(), whiteList.end(),userId) != whiteList.end();
}

int Room::getId() const {
    return id;
}
// checks is room if accessible for some user
bool Room::isAccessible(int userId, AccessLevel userAccessLvl) {
    return userAccessLvl >= accessLevel || isInWhiteList(userId);
}

int Room::getFlour() const {
    return floor;
}
// returns a string containing room information
std::string Room::getRoomInfo() {
    return " #" + std::to_string(floor) + std::to_string(number) + " with " + accessLevelNames[accessLevel] + " access level\tId: " + std::to_string(id);
}
