//
// Created by michael on 3/7/21.
//

#include "../include/Student.h"

#include <utility>

Student::Student(std::string firstName, std::string secondName) : User(std::move(firstName), std::move(secondName)) {

}
