//
// Created by michael on 3/7/21.
//

#include "../../include/Users/Professor.h"
Professor::Professor(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {
    accessLevel = yellow;
}

std::string Professor::getUserInfo() {
    return "Professor " + User::getUserInfo();
}
