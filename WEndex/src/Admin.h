//
// Created by michael on 2021-04-26.
//

#ifndef WENDEX_ADMIN_H
#define WENDEX_ADMIN_H

#include "string"

using namespace std;

struct BlockedMethod {
    int id{-1};
    int type{-1};
    int userId{-1};

    BlockedMethod(int type, int userId) : type(type), userId(userId) {}
    BlockedMethod() = default;
};

enum BlockedDriversMethods {
    AcceptRide, UpgradeCurrentCar, FindAllAvailableOrders
};

enum BlockedPassengersMethods {
    AddPaymentMethod, RemovePaymentMethod, MakeOrder, AskForBill
};

class Admin {
public:
    int id{};
    string name{};
    string login{};
    string password{};

    inline Admin(string name, string login, string password) : name(move(name)), login(move(login)),
                                                               password(move(password)) {}

    Admin() = default;
};


#endif //WENDEX_ADMIN_H
