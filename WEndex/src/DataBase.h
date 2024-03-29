//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_DATABASE_H
#define WENDEX_DATABASE_H

#include <sqlite_orm/sqlite_orm.h>
#include "Passenger.h"
#include "Driver.h"
#include "Order.h"
#include "Exeptions.h"
#include "Device.h"
#include "Admin.h"

using namespace std;
using namespace sqlite_orm;

inline auto InitializeStorage() {
    return make_storage("DataBase.sqlite",
                        make_table("Drivers",
                                   make_column("id", &Driver::id, autoincrement(), primary_key()),
                                   make_column("status", &Driver::status),
                                   make_column("rating", &Driver::rating),
                                   make_column("name", &Driver::name),
                                   make_column("currentlyUsedCarId", &Driver::currentlyUsedCarId),
                                   make_column("login", &Driver::login),
                                   make_column("password", &Driver::password)),
                        make_table("Passengers",
                                   make_column("id", &Passenger::id, autoincrement(), primary_key()),
                                   make_column("name", &Passenger::name),
                                   make_column("rating", &Passenger::rating),
                                   make_column("login", &Passenger::login),
                                   make_column("password", &Passenger::password)),
                        make_table("PinnedAddresses",
                                   make_column("id", &PinnedAddress::id, autoincrement(), primary_key()),
                                   make_column("address", &PinnedAddress::address),
                                   make_column("passengerId", &PinnedAddress::passengerId)),
                        make_table("Orders",
                                   make_column("id", &Order::id, autoincrement(), primary_key()),
                                   make_column("costDollars", &Order::costDollars),
                                   make_column("fromAddress", &Order::fromAddress),
                                   make_column("toAddress", &Order::toAddress),
                                   make_column("timeMinutes", &Order::timeMinutes),
                                   make_column("passengerId", &Order::passengerId),
                                   make_column("driverId", &Order::driverId),
                                   make_column("paymentMethod", &Order::paymentMethod),
                                   make_column("status", &Order::status),
                                   make_column("carType", &Order::carType)),
                        make_table("PaymentMethods",
                                   make_column("id", &PaymentMethod::id, autoincrement(), primary_key()),
                                   make_column("type", &PaymentMethod::type),
                                   make_column("passengerId", &PaymentMethod::passengerId)),
                        make_table("Cars",
                                   make_column("id", &Car::id, autoincrement(), primary_key()),
                                   make_column("model", &Car::model),
                                   make_column("type", &Car::type),
                                   make_column("location", &Car::location),
                                   make_column("color", &Car::color),
                                   make_column("number", &Car::number),
                                   make_column("driverId", &Car::driverId),
                                   make_column("freeBottleOfWater", &Car::freeBottleOfWater)),
                        make_table("Devices",
                                   make_column("id", &Device::id, autoincrement(), primary_key()),
                                   make_column("name", &Device::name),
                                   make_column("userID", &Device::userId),
                                   make_column("operatingSystem", &Device::operatingSystem)),
                        make_table("Admins",
                                   make_column("id", &Admin::id, autoincrement(), primary_key()),
                                   make_column("name", &Admin::name),
                                   make_column("login", &Admin::login),
                                   make_column("password", &Admin::password)),
                        make_table("BlockedMethods",
                                   make_column("id", &BlockedMethod::id, autoincrement(), primary_key()),
                                   make_column("type", &BlockedMethod::type),
                                   make_column("userId", &BlockedMethod::userId)));
}

class DataBase {
public:
    inline static auto Storage = InitializeStorage();
};

#endif //WENDEX_DATABASE_H
