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
    int id{-1};
    double costDollars{100000};
    int timeMinutes{-1};
    int fromAddress{Chernobyl};
    int toAddress{Innopolis};
    int passengerId{-1};
    int driverId{-1};
    int paymentMethod{Cash};
    int status{LookingForDriver};

    Order(int id = -1, int fromAddress = Chernobyl, int toAddress = Innopolis, int passengerId = -1, int driverId = -1) : id(id), fromAddress(fromAddress),
    toAddress(toAddress), passengerId(passengerId), driverId(driverId) {
        timeMinutes = abs(fromAddress - toAddress) * 30;
        costDollars = double(timeMinutes) * 1.56;
    }
};


#endif //WENDEX_ORDER_H
