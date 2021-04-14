//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_PROFESSOR_H
#define ROOMACCESS_PROFESSOR_H
#include "User.h"

class Professor : public User{
public:
    Professor(std::string  firstName, std::string  secondName);
    virtual std::string getUserInfo();
};


#endif //ROOMACCESS_PROFESSOR_H
