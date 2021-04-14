//
// Created by michael on 3/17/21.
//

#ifndef ROOMACCESS_GUEST_H
#define ROOMACCESS_GUEST_H
#include "User.h"

class Guest : public User{
public:
    Guest(std::string firstName, std::string secondName);
    virtual std::string getUserInfo();
};


#endif //ROOMACCESS_GUEST_H
