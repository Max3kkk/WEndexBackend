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
#include "Exeptions.h"


class DriverGateway {
public:
    void Register(const string& name, const string& login, const string& password);
    Driver Login(const string& login, const string& password);

    Car ChangeCar(int driverId, int model, int type, int location, int color, string number);
};


#endif //WENDEX_DRIVERGATEWAY_H
