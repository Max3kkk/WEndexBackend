//
// Created by michael on 3/7/21.
//

#include "../include/Professor.h"
Professor::Professor(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {
    accessLevel = yellow;
}