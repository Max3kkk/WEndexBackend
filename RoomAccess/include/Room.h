//
// Created by michael on 3/7/21.
//

#ifndef ROOMACCESS_ROOM_H
#define ROOMACCESS_ROOM_H
#include "string"
#include "AccessLevel.h"
#include "vector"
#include "algorithm"

class Room {
protected:
    int number{};
    int id{};
    AccessLevel accessLevel{no_level};
    bool is_Booked{false};
    int curUserId{-1};
    std::vector<int> whiteList{};
    std::vector<int> blackList{};
public:
    static int instance;
    virtual int getNumber() const;
    virtual AccessLevel getAccessLevel() const;
    virtual int getId() const;
    virtual bool isBooked() const;
    virtual int getCurUserId() const;
    virtual const std::vector<int> &getWhiteList() const;
    virtual const std::vector<int> &getBlackList() const;
    virtual void addToWhiteList(int userId);
    virtual void addToBlackList(int userId);
    virtual void removeFromBlackList(int userId);
    virtual void removeFromWhiteList(int userId);
    virtual bool isInWhiteList(int userId);
    virtual bool isInBlackList(int userId);
    virtual void book(int userId);
    virtual void discardBooking();
    //Room constructors
    Room() = delete;
    Room(int number);
};


#endif //ROOMACCESS_ROOM_H
