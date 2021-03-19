//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_CABINET_H
#define ROOMACCESS_CABINET_H
#include "Room.h"

class Cabinet : public Room{
public:
    Cabinet(int number, int floor);
    virtual std::string getRoomInfo();
};


#endif //ROOMACCESS_CABINET_H
