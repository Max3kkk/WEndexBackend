//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_LECTUREROOM_H
#define ROOMACCESS_LECTUREROOM_H
#include "Room.h"

class LectureRoom : public Room{
public:
    explicit LectureRoom(int number, int floor);
    virtual std::string getRoomInfo();
};


#endif //ROOMACCESS_LECTUREROOM_H
