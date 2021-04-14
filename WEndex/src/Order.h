//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_ORDER_H
#define WENDEX_ORDER_H

enum OrderStatusType {
    LookingForDriver, WaitingForDriverArrival, InProgress, Finished
};

class Order {
public:
    int id;
    double costDollars;
    int timeMinutes;
    int fromAddress;
    int toAddress;
    int passengerId;
    int driverId;
    int paymentMethod{Cash};
    OrderStatusType status{LookingForDriver};

    Order(int id, int fromAddress, int toAddress, int passengerId, int driverId) : id(id), fromAddress(fromAddress),
    toAddress(toAddress), passengerId(passengerId), driverId(driverId) {
        timeMinutes = abs(fromAddress - toAddress) * 30;
        costDollars = double(timeMinutes) * 1.56;
    }
};


#endif //WENDEX_ORDER_H
