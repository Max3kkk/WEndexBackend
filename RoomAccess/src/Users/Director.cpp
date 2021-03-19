//
// Created by michael on 3/7/21.
//

#include "../../include/Users/Director.h"
Director::Director(std::string firstName, std::string secondName)
: User(std::move(firstName), std::move(secondName)) {
    accessLevel = red;
}

std::string Director::getUserInfo() {
    return "Our favorite director " + User::getUserInfo();
}
