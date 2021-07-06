//
// Created by michael on .
//

#ifndef WENDEX_PASSENGER_H
#define WENDEX_PASSENGER_H

#include "string"
#include "Car.h"

using namespace std;

enum paymentMethodType {
    Cash, Check, DebitCard,
    CreditCards, MobilePayments,
    ElectronicBankTransfer, OrganTrade
};

struct PaymentMethod {
    int id{-1};
    int type{-1};
    int passengerId{-1};

    PaymentMethod(int type = Cash, int passengerId = -1) : type(type), passengerId(passengerId) {}

};

struct PinnedAddress {
    int id{-1};
    int address{-1};
    int passengerId{-1};

    PinnedAddress(int address = Chernobyl, int passengerId = -1) : address(address), passengerId(passengerId) {}
};


class Passenger {
public:
    int id{};
    string name{};
    int currentlyUsedDeviceId{};
    double rating{5.0};
    string login{};
    string password{};

    inline Passenger(string name, string login, string password) : name(move(name)), login(move(login)),
                                                                   password(move(password)) {}

    Passenger() = default;
};


#endif //WENDEX_PASSENGER_H
