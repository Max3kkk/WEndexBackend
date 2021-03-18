//
// Created by michael on 3/7/21.
//

#include "../include/DataBaseManager.h"

Room* DataBaseManager::getRoom(int roomId) {
    for (auto room : rooms) {
        if (room->getId() == roomId) {
            return room;
        }
    }
    return nullptr;
}

User* DataBaseManager::getUser(int userId) {
    for (User* user : users) {
        if (user->getId() == userId) {
            return user;
        }
    }
    return nullptr;
}

bool DataBaseManager::hasUser(int userId) {
    for (auto user : users) {
        if (user->getId() == userId) {
            return true;
        }
    }
    return false;
}

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

const std::vector<User *> &DataBaseManager::getUsers() const {
    return users;
}

const std::vector<Room *> &DataBaseManager::getRooms() const {
    return rooms;
}

bool DataBaseManager::canBook(int userId, int roomId) {
    auto user = getUser(userId);
    auto room = getRoom(roomId);
    return user != nullptr && room != nullptr && (user->getAccessLevel() >= room->getAccessLevel() || room->isInWhiteList(userId));
}

bool DataBaseManager::canBook(User* user, Room* room) {
    return user != nullptr && room != nullptr && (user->getAccessLevel() >= room->getAccessLevel() || room->isInWhiteList(user->getId()));
}

