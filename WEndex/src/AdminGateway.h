//
// Created by michael on 2021-04-26.
//

#ifndef WENDEX_ADMINGATEWAY_H
#define WENDEX_ADMINGATEWAY_H
#define st DataBase::Storage

#include "string"
#include "DataBase.h"
#include "Exeptions.h"
#include "iostream"
#include "vector"
#include "Car.h"
#include "Driver.h"
#include "Order.h"

class AdminGateway {
public:
    void Register(const string &name, const string &login, const string &password);

    Admin Login(const string &login, const string &password);

    void UnBlockMethod(int adminId, int userId, int methodType);

    void BlockMethod(int adminId, int userId, int methodType);

    vector<BlockedMethod> seeBlockedMethods(int adminId);

    vector<Device> seeAllDevices(int adminId);

    vector<Driver> seeAllDrivers(int adminId);

    vector<PaymentMethod> seeAllPaymentMethods(int adminId);

    vector<Car> seeAllCars(int adminId);

    vector<Order> seeAllOrders(int adminId);

    vector<Passenger> seeAllPassengers(int adminId);

    bool IsAdmin(int adminId);
};


#endif //WENDEX_ADMINGATEWAY_H
