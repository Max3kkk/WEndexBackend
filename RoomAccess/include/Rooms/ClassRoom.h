//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_CLASSROOM_H
#define ROOMACCESS_CLASSROOM_H
#include "Room.h"

class ClassRoom : public Room{
public:
    ClassRoom(int number, int floor);
    virtual std::string getRoomInfo();
};


#endif //ROOMACCESS_CLASSROOM_H
