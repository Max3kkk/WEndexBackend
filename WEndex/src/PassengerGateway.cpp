//
// Created by michael on 4/14/21.
//

#include "PassengerGateway.h"

Passenger PassengerGateway::Login(const string &login, const string &password) {
    auto vec = st.get_all<Passenger>(where(c(&Passenger::login) == login && c(&Passenger::password) == password));
    if (vec.size() != 1) {
        throw WrongLoginOrPassword();
    }
    cout << "You are successfully signed in " << vec[0].name << endl;
    cout << st.dump(vec[0]);
    return vec[0];
}

void PassengerGateway::Register(const string &name, const string &login, const string &password) {
    if (st.count<Passenger>(where(c(&Passenger::login) == login))){
        throw LoginIsTaken();
    }
    cout << "You are successfully logged in " << name << endl;
    st.insert(Passenger(name, login, password));
}

vector<Order> PassengerGateway::SeeOrderHistory(int passengerId) {
    auto orders = st.get_all<Order>(where(c(&Order::passengerId) == passengerId) && c(&Order::status) == (int)Finished);
    cout << "Order history of this passenger is :" << endl;
    for (auto o : orders) {
        cout << st.dump(o);
    }
    return orders;
}

vector<PinnedAddress> PassengerGateway::SeePinedAddresses(int passengerId) {
    cout << "Pinned addresses of this passenger are :" << endl;
    auto addresses = st.get_all<PinnedAddress>(where(c(&PinnedAddress::passengerId) == passengerId));
    for (auto o : addresses) {
        cout << st.dump(o);
    }
    return addresses;
}

void PassengerGateway::removePinnedAddress(int passengerId, int address) {
    st.remove_all<PinnedAddress>(where(c(&PinnedAddress::passengerId) == passengerId) && c(&PinnedAddress::address) == address);
    cout << "Passenger removed address" << endl;
}

void PassengerGateway::addPaymentMethod(int passengerId, int paymentType) {
    st.insert(PaymentMethod(paymentType,passengerId));
    cout << "Passenger added payment method" << endl;
}


vector<PaymentMethod> PassengerGateway::SeePaymentMethods(int passengerId) {
    auto met = st.get_all<PaymentMethod>(where(c(&PaymentMethod::passengerId) == passengerId));
    cout << "Payment methods of this passenger are :" << endl;
    for (auto o : met) {
        cout << st.dump(o);
    }
    return met;
}

void PassengerGateway::removePaymentMethod(int passengerId, int paymentType) {
    st.remove_all<PaymentMethod>(where(c(&PaymentMethod::passengerId) == passengerId) && c(&PaymentMethod::type) == paymentType);
}

void PassengerGateway::addPinnedAddress(int passengerId, int address) {
    st.insert(PinnedAddress(address,passengerId));
}

Order PassengerGateway::makeOrder(int passengerId, int paymentType, int carType, int from, int to) {
    Order ord(from,to,passengerId,carType,paymentType);
    st.insert(ord);
    return ord;
}

void PassengerGateway::changePaymentType(int passengerId, int paymentType) {
    auto pt = SeePaymentMethods(passengerId);
    bool hasPM = false;
    for (auto pm : pt) {
        if(pm.type == paymentType) {
            hasPM = true;
            break;
        }
    }
    if(!hasPM) {
        throw HasNoSuchPaymentMethod();
    }
    auto vec = st.get_all<Order>(where(c(&Order::passengerId)==passengerId && c(&Order::status) == (int)InProgress));
    for (auto o : vec) {
        o.paymentMethod = paymentType;
        st.update(o);
        cout << st.dump(o) << endl;
    }
}

int PassengerGateway::printCurrentCoordinates(int passengerId) {
    auto orders = st.get_all<Order>(where(c(&Order::passengerId) == passengerId && c(&Order::status) != (int)LookingForDriver && c(&Order::status) != (int)Finished));
    if(orders.size() == 1) {
        auto car = st.get<Car>(st.get<Driver>(orders[0].driverId).carId);
        cout << "Your location is: " << car.location << endl;
        return car.location;
    } else {
        throw LocationIsNotSpecified();
    }
}

double PassengerGateway::askForBill(int passengerId) {
    auto orders = st.get_all<Order>(where(c(&Order::passengerId) == passengerId && c(&Order::status) == (int)InProgress));
    if(orders.size() == 1) {
        cout << "Here is your bill: " << orders[0].costDollars <<"$" << endl;
        return orders[0].costDollars;
    } else {
        throw LocationIsNotSpecified();
    }
}