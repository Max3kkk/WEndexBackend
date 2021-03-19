//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_CONTROLLER_H
#define ROOMACCESS_CONTROLLER_H
#include "iostream"
#include "DataBaseManager.h"
#include "Users/User.h"
#include "Users/Student.h"
#include "Users/LabEmployee.h"
#include "Users/Director.h"
#include "Users/Professor.h"
#include "Users/Admin.h"
#include "Users/Guest.h"
#include "Rooms/Room.h"
#include "Rooms/Cabinet.h"
#include "Rooms/ClassRoom.h"
#include "Rooms/ConferenceRoom.h"
#include "Rooms/LectureRoom.h"
#include "Rooms/DirectorCabinet.h"
#include "vector"
#include "string"

class Controller {
private:
    int curCommand{};
    User* curUser = nullptr;
    User* userChosenByAdmin = nullptr;
    Room* curRoom = nullptr;
    DataBaseManager* dataBaseManager{};
    bool isEmergency{false};
    void reset();
public:
    Controller();
    //void processCommand();
    //void readCommands();
    int processCommand();

    [[noreturn]] void readConsole();
    void chooseUser(User*& ptr);
    void chooseRoom();
    void processConsole();
    void tryAccess();
};


#endif //ROOMACCESS_CONTROLLER_H
