//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_ADMIN_H
#define ROOMACCESS_ADMIN_H
#include "../DataBaseManager.h"
#include "User.h"
class DataBaseManager;
class Admin : public User{
private:
    DataBaseManager* dataBase{};
public:
    virtual void grantAccess(int userId, int roomId); //put User to white list
    virtual void denyAccess(int userId, int roomId); //put User to black list
    virtual std::string getUserInfo();
    // constructors
    Admin(std::string firstName, std::string secName);
    Admin(std::string firstName, std::string secName, DataBaseManager* db);
};


#endif //ROOMACCESS_ADMIN_H
