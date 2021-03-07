//
// Created by michael on 3/7/21.
//

#include "../include/Room.h"
int Room::instance = 0;

Room::Room(int number) :
    number(number) {
    id = ++instance;
}

int Room::getNumber() const {
    return number;
}

AccessLevel Room::getAccessLevel() const {
    return accessLevel;
}

bool Room::isBooked() const {
    return is_Booked;
}

int Room::getCurUserId() const {
    return curUserId;
}

const std::vector<int> &Room::getWhiteList() const {
    return whiteList;
}

const std::vector<int> &Room::getBlackList() const {
    return blackList;
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

bool Room::isInBlackList(int userId) {
    return !blackList.empty() && std::find(blackList.begin(), blackList.end(),userId) != blackList.end();
}

bool Room::isInWhiteList(int userId) {
    return !whiteList.empty() && std::find(whiteList.begin(), whiteList.end(),userId) != whiteList.end();
}

int Room::getId() const {
    return id;
}

void Room::discardBooking() {
    is_Booked = false;
    curUserId = -1;
}

void Room::book(int userId) {
    if (!is_Booked) {
        is_Booked = true;
        curUserId = userId;
    }
}
