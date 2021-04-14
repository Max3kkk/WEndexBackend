//
// Created by michael on 3/7/21.
//

#include "../../include/Users/LabEmployee.h"
LabEmployee::LabEmployee(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {
    accessLevel = yellow;
}

std::string LabEmployee::getUserInfo() {
    return "Lab employee " + User::getUserInfo();
}
