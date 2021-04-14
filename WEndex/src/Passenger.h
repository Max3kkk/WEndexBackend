//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_PASSENGER_H
#define WENDEX_PASSENGER_H
#include "string"
using namespace std;

enum paymentMethodType {
    Cash, Check, DebitCard,
    CreditCards,MobilePayments,
    ElectronicBankTransfer, OrganTrade
};

struct PaymentMethod{
    int type;
    int passengerId;
};


class Passenger {
public:
    int id{};
    string name;
    double rating{5.0};
    string login;
    string password;
    inline Passenger(string name, string login, string password) : name(move(name)), login(move(login)), password(move(password)) {}
};


#endif //WENDEX_PASSENGER_H
