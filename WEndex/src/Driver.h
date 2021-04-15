//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_DRIVER_H
#define WENDEX_DRIVER_H
#include "vector"
#include "string"
#include "Car.h"
using namespace std;

enum DriverStatus{
    NotWorking, Available, Busy, Driving
};

class Driver {
public:
    int id{};
    string name;
    double rating{5.0};
    int status{NotWorking};
    int carId;
    string login;
    string password;
    inline Driver(string name, string login, string password, int carId) : name(move(name)), login(move(login)), password(move(password)), carId(carId) {}
    inline Driver() = default;
};


#endif //WENDEX_DRIVER_H
