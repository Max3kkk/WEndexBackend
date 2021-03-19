//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_LABEMPLOYEE_H
#define ROOMACCESS_LABEMPLOYEE_H
#include "User.h"

class LabEmployee : public User{
public:
    LabEmployee(std::string  firstName, std::string  secondName);
    virtual std::string getUserInfo();
};


#endif //ROOMACCESS_LABEMPLOYEE_H
