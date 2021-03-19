//
// Created by michael on 3/7/21.
//

#include "../../include/Users/Admin.h"

Admin::Admin(std::string firstName, std::string secondName)
        : User(std::move(firstName), std::move(secondName)) {
    accessLevel = red;
}

Admin::Admin(std::string firstName, std::string secondName, DataBaseManager *db) : User(std::move(firstName), std::move(secondName)), dataBase(db){
    accessLevel = red;
}

// add user to room's white list
void Admin::grantAccess(int userId, int roomId) {
    if (dataBase->hasRoom(roomId) && dataBase->hasUser(userId)) {
        auto room = dataBase->getRoom(roomId);
        if (!dataBase->canAccess(userId, roomId)) {
            room->removeFromBlackList(userId);
            room->addToWhiteList(userId);
        }
    }
}

// add user to room's black list
void Admin::denyAccess(int userId, int roomId) {
    if (dataBase->hasRoom(roomId) && dataBase->hasUser(userId)) {
        auto room = dataBase->getRoom(roomId);
        if (dataBase->canAccess(userId, roomId)) {
            room->removeFromWhiteList(userId);
            room->addToBlackList(userId);
        }
    }
}

std::string Admin::getUserInfo() {
    return "Admin " + User::getUserInfo();
}
