//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_CONTROLLER_H
#define ROOMACCESS_CONTROLLER_H
#include "iostream"
#include "DataBaseManager.h"
#include "User.h"
#include "Student.h"
#include "LabEmployee.h"
#include "Director.h"
#include "Professor.h"
#include "Admin.h"
#include "Room.h"
#include "Cabinet.h"
#include "ClassRoom.h"
#include "ConferenceRoom.h"
#include "LectureRoom.h"
#include "DirectorCabinet.h"
#include "vector"
#include "string"

class Controller {
private:
    std::string lastCommand{};
    User* curUser = nullptr;
    User* chosenUser = nullptr;
    Room* chosenRoom = nullptr;
    DataBaseManager* dataBaseManager{};
    void reset();
public:
    Controller();
    void processCommand();
    void readCommands();
    template<typename Base, typename T>
    bool instanceOf(const T *ptr);
    void chooseUser(User*& ptr);
    void chooseRoom(Room*& ptr);
};


#endif //ROOMACCESS_CONTROLLER_H
