//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_CONFERENCEROOM_H
#define ROOMACCESS_CONFERENCEROOM_H
#include "Room.h"

class ConferenceRoom : public Room{
public:
    ConferenceRoom(int number, int floor);
    virtual std::string getRoomInfo();
};


#endif //ROOMACCESS_CONFERENCEROOM_H
