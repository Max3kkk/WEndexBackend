//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_ROOM_H
#define ROOMACCESS_ROOM_H
#include "string"
#include "../AccessLevel.h"
#include "vector"
#include "algorithm"

class Room {
protected:
    int number{};
    int id{};
    int floor{};
    AccessLevel accessLevel{no_level};
    std::vector<int> whiteList{};
    std::vector<int> blackList{};
    static int instance;
public:
    virtual int getNumber() const;
    const static std::vector<std::string> accessLevelNames;
    virtual int getFlour() const;
    virtual AccessLevel getAccessLevel() const;
    virtual int getId() const;
    virtual void addToWhiteList(int userId);
    virtual void addToBlackList(int userId);
    virtual void removeFromBlackList(int userId);
    virtual void removeFromWhiteList(int userId);
    virtual bool isInWhiteList(int userId);
    virtual bool isInBlackList(int userId);
    virtual std::string getRoomInfo();
    bool isAccessible(int userId, AccessLevel userAccessLvl);
    //Room constructors
    explicit Room(int number, int floor);
};


#endif //ROOMACCESS_ROOM_H
