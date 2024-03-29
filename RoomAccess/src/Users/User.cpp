//
// Created by michael on 3/7/21.
//

#include "../../include/Users/User.h"
#include "../../include/Rooms/Room.h"
int User::instance = 0;

User::User(std::string  firstName, std::string  secondName)
        : firstName(std::move(firstName)), secondName(std::move(secondName)){
    id = ++instance;
}

const std::string &User::getFirstName() const {
    return firstName;
}

const std::string &User::getSecondName() const {
    return secondName;
}

AccessLevel User::getAccessLevel() const {
    return accessLevel;
}

int User::getId() const {
    return id;
}

// returns a string containing user information
std::string User::getUserInfo() {
    return firstName + " " + secondName + " with " + Room::accessLevelNames[accessLevel] + " access level\tId: " + std::to_string(id);
}


