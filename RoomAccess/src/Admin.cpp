//
// Created by michael on 3/7/21.
//

#include "../include/Admin.h"

Admin::Admin(std::string firstName, std::string secondName)
        : User(std::move(firstName), std::move(secondName)) {
    //dataBase = nullptr;
    accessLevel = red;
}

void Admin::grantAccess(int userId, int roomId) {
    if (dataBase->hasRoom(roomId) && dataBase->hasUser(userId)) {
        auto room = dataBase->getRoom(roomId);
        if (!dataBase->canBook(userId, roomId)) {
            room->removeFromBlackList(userId);
            room->addToWhiteList(userId);
        }
    }
}

void Admin::denyAccess(int userId, int roomId) {
    if (dataBase->hasRoom(roomId) && dataBase->hasUser(userId)) {
        auto room = dataBase->getRoom(roomId);
        if (dataBase->canBook(userId, roomId)) {
            room->removeFromWhiteList(userId);
            room->addToBlackList(userId);
        }
    }
}

void Admin::setDataBase(DataBaseManager* dB) {
    this->dataBase = dB;
}
