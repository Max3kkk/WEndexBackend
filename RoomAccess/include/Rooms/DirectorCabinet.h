//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_DIRECTORCABINET_H
#define ROOMACCESS_DIRECTORCABINET_H
#include "Room.h"

class DirectorCabinet : public Room{
public:
    explicit DirectorCabinet(int number, int floor);
    virtual std::string getRoomInfo();
};


#endif //ROOMACCESS_DIRECTORCABINET_H
