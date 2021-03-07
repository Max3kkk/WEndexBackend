//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_DATABASEMANAGER_H
#define ROOMACCESS_DATABASEMANAGER_H
#include "Admin.h"
#include "vector"
#include "User.h"
#include "Room.h"
#include "Student.h"
#include "Professor.h"
#include "LabEmployee.h"
#include "Director.h"

class DataBaseManager {
private:
    std::vector<User*> users{};
    std::vector<Room*> rooms{};
public:
    const std::vector<User *> &getUsers() const;
    const std::vector<Room *> &getRooms() const;
    bool hasUser(int userId);
    bool hasRoom(int roomId);
    void addUser(User* user);
    void addRoom(Room* room);
    User* getUser(int userId);
    Room* getRoom(int roomId);
    bool canBook(int userId, int roomId);

    bool canBook(User *user, Room *room);
};


#endif //ROOMACCESS_DATABASEMANAGER_H
