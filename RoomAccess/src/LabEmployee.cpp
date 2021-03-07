//
// Created by michael on 3/7/21.
//

#include "../include/LabEmployee.h"
LabEmployee::LabEmployee(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {
    accessLevel = green;
}