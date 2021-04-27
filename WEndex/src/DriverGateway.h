//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_DRIVERGATEWAY_H
#define WENDEX_DRIVERGATEWAY_H
#define st DataBase::Storage

#include "string"
#include "DataBase.h"
#include "Car.h"
#include "iostream"
#include "Driver.h"
#include "vector"
#include "Order.h"
#include "Exeptions.h"


class DriverGateway {
public:
    void Register(const string& name, const string& login, const string& password);
    Driver Login(const string& login, const string& password);

    vector<Order> SeeOrderHistory(int driverId);

    Car SeeCar(int driverId);

    int ChangeStatus(int driverId, int status);

    vector<Order> FindAvailableOrders(int driverId);

    void GetOrder(int driverId, int OrderId);

    void doRandomAvailableOrder(int driverId);

    Car UpgradeCar(int driverId, int model, int type, int color);

    bool CarValid(int driverId);

    bool CanAcceptRide(int driverId);

    bool CanUpgradeCar(int driverId);

    bool CanFindAvailableOrders(int driverId);

    Car AddNewCar(int driverId, int model, int type, int color);

    Car SwitchCar(int driverId, int carId);
};


#endif //WENDEX_DRIVERGATEWAY_H
