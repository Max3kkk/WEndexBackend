//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_STUDENT_H
#define ROOMACCESS_STUDENT_H
#include "User.h"

class Student : public User{
public:
    Student(std::string  firstName, std::string  secondName);
    virtual std::string getUserInfo();
};


#endif //ROOMACCESS_STUDENT_H
