//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_DIRECTOR_H
#define ROOMACCESS_DIRECTOR_H
#include "User.h"

class Director : public User{
public:
    Director(std::string  firstName, std::string  secondName);
    virtual std::string getUserInfo();
};


#endif //ROOMACCESS_DIRECTOR_H
