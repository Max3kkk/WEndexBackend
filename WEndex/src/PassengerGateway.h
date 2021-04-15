//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_PASSENGERGATEWAY_H
#define WENDEX_PASSENGERGATEWAY_H
#define st DataBase::Storage
#include "string"
#include "DataBase.h"
#include "Car.h"
#include "iostream"
#include "Driver.h"
#include "vector"
#include "Order.h"
#include "Exeptions.h"

class PassengerGateway {
public:
    void Register(const string& name, const string& login, const string& password);
    Passenger Login(const string& login, const string& password);
    vector<Order> SeeOrderHistory(int passengerId);

    vector<struct PinnedAddress> SeePinedAddresses(int passengerId);

    void removePinnedAddress(int passengerId, int address);

    void addPinnedAddress(int passengerId, int address);

    void addPaymentMethod(int passengerId, int paymentType);

    vector<PaymentMethod> SeePaymentMethods(int passengerId);

    void removePaymentMethod(int passengerId, int paymentType);

    Order makeOrder(int passengerId, int paymentType, int carType, int from, int to);

    void changePaymentType(int passengerId, int paymentType);

    int printCurrentCoordinates(int passengerId);

    double askForBill(int passengerId);
};


#endif //WENDEX_PASSENGERGATEWAY_H
