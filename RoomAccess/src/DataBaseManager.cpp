//
// Created by michael on 3/7/21.
//

#include <iostream>
#include "../include/DataBaseManager.h"

// return a room by its id
Room* DataBaseManager::getRoom(int roomId) {
    for (auto room : rooms) {
        if (room->getId() == roomId) {
            return room;
        }
    }
    return nullptr;
}
// return a user by its id
User* DataBaseManager::getUser(int userId) {
    for (User* user : users) {
        if (user->getId() == userId) {
            return user;
        }
    }
    return nullptr;
}
// checks if DB has a user
bool DataBaseManager::hasUser(int userId) {
    for (auto user : users) {
        if (user->getId() == userId) {
            return true;
        }
    }
    return false;
}

// checks if DB has a room
bool DataBaseManager::hasRoom(int roomId) {
    for (auto room : rooms) {
        if (room->getId() == roomId) {
            return true;
        }
    }
    return false;
}

void DataBaseManager::addRoom(Room *room) {
    if (!hasRoom(room->getId())) {
        rooms.push_back(room);
    }
}

void DataBaseManager::addUser(User *user) {
    if (!hasUser(user->getId())) {
        users.push_back(user);
    }
}

// prints information of all user to console
void DataBaseManager::printUsers() {
    for (auto user : users) {
        std::cout << user->getUserInfo() << std::endl;
    }
}

// prints information of all rooms to console
void DataBaseManager::printRooms() {
    for (auto room : rooms) {
        std::cout << room->getRoomInfo() << std::endl;
    }
}

// checks if user's & room's ids are valid and user can access room
bool DataBaseManager::canAccess(int userId, int roomId) {
    auto user = getUser(userId);
    auto room = getRoom(roomId);
    return hasUser(userId) && hasRoom(roomId) && room->isAccessible(userId, user->getAccessLevel());
}
