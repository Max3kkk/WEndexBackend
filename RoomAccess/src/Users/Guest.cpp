//
// Created by michael on 3/17/21.
//

#include "../../include/Users/Guest.h"

#include <utility>

Guest::Guest(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {
    accessLevel = blue;
}

std::string Guest::getUserInfo() {
    return "Guest " + User::getUserInfo();
}
