//
// Created by Mikhail Fedorov on 3/7/21.
//

#ifndef ROOMACCESS_USER_H
#define ROOMACCESS_USER_H
#include <string>
#include "AccessLevel.h"


class User {
protected:
    std::string firstName{};
    std::string secondName{};
    int id{};
    AccessLevel accessLevel{no_level};
public:
    static int instance;
    virtual const std::string &getFirstName() const;
    virtual int getId() const;
    virtual const std::string &getSecondName() const;
    virtual AccessLevel getAccessLevel() const;
    //User constructors
    User() = delete;
    User(std::string  firstName, std::string  secondName);

};


#endif //ROOMACCESS_USER_H
