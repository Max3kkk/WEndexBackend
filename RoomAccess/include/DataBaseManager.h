//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_DATABASEMANAGER_H
#define ROOMACCESS_DATABASEMANAGER_H
#include "Users/Admin.h"
#include "vector"
#include "Users/User.h"
#include "Rooms/Room.h"
#include "Users/Student.h"
#include "Users/Professor.h"
#include "Users/LabEmployee.h"
#include "Users/Director.h"

class DataBaseManager {
private:
    std::vector<User*> users{};
    std::vector<Room*> rooms{};
public:
    void printRooms();
    void printUsers();
    bool hasUser(int userId);
    bool hasRoom(int roomId);
    void addUser(User* user);
    void addRoom(Room* room);
    User* getUser(int userId);
    Room* getRoom(int roomId);
    bool canAccess(int userId, int roomId);
};


#endif //ROOMACCESS_DATABASEMANAGER_H
