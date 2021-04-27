//
// Created by michael on 4/14/21.
//

#include "PassengerGateway.h"

#include <utility>

Passenger PassengerGateway::Login(const string &login, const string &password) {
    auto vec = st.get_all<Passenger>(where(c(&Passenger::login) == login && c(&Passenger::password) == password));
    if (vec.size() != 1) {
        throw WrongLoginOrPassword();
    }
    cout << "You are successfully logged in as passenger:  " << st.dump(vec[0]) << endl;
    return vec[0];
}

void PassengerGateway::Register(const string &name, const string &login, const string &password) {
    if (st.count<Passenger>(where(c(&Passenger::login) == login))) {
        auto passenger = st.get_all<Passenger>(where(c(&Passenger::login) == login));
        if (passenger.size() != 1) {
            throw LoginIsTaken();
        } else if (passenger[0].password == password) {
            cout << name << ", you are already registered as a passenger" << endl;
            return;
        }
    }
    Device device;
    st.insert(device);
    Passenger pt(name, login, password);
    pt.currentlyUsedDeviceId = device.id;
    st.insert(pt);
    cout << "You are successfully registered as a passenger, " << st.dump(pt) << endl;
}

vector<Order> PassengerGateway::SeeOrderHistory(int passengerId) {
    auto orders = st.get_all<Order>(
            where(c(&Order::passengerId) == passengerId) && c(&Order::status) == (int) Finished);
    cout << "Order history of this passenger is :" << endl;
    for (auto o : orders) {
        cout << st.dump(o) << endl;
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
    st.remove_all<PinnedAddress>(
            where(c(&PinnedAddress::passengerId) == passengerId) && c(&PinnedAddress::address) == address);
    cout << "Passenger removed address" << endl;
}

void PassengerGateway::addPaymentMethod(int passengerId, int paymentType) {
    auto pt = st.get<Passenger>(passengerId);
    if (!CanAddPaymentMethod(passengerId)) {
        throw BlockedFunction();
    }
    st.insert(PaymentMethod(paymentType, passengerId));
    cout << "Passenger " << pt.name << " added payment method " <<  paymentType << endl;
}


vector<PaymentMethod> PassengerGateway::SeePaymentMethods(int passengerId) {
    auto pt = st.get<Passenger>(passengerId);
    auto met = st.get_all<PaymentMethod>(where(c(&PaymentMethod::passengerId) == passengerId));
    cout << "Payment methods of passenger: " << pt.name << endl;
    for (auto o : met) {
        cout << st.dump(o) << endl;
    }
    return met;
}

void PassengerGateway::removePaymentMethod(int passengerId, int paymentType) {
    auto pt = st.get<Passenger>(passengerId);
    if (!CanRemovePaymentMethod(passengerId)) {
        throw BlockedFunction();
    }
    cout << "Passenger " << pt.name << " removed payment method :" << paymentType << endl;
    st.remove_all<PaymentMethod>(
            where(c(&PaymentMethod::passengerId) == passengerId && c(&PaymentMethod::type) == paymentType));
}

void PassengerGateway::addPinnedAddress(int passengerId, int address) {
    st.insert(PinnedAddress(address, passengerId));
}

Order PassengerGateway::makeOrder(int passengerId, int paymentType, int carType, int from, int to) {
    auto pt = st.get<Passenger>(passengerId);
    if (!CanMakeOrder(passengerId)) {
        throw BlockedFunction();
    }
    Order ord(from, to, passengerId, carType, paymentType);
    st.insert(ord);
    cout << "Passenger " << pt.name << " made order :" << st.dump(ord) << endl;
    return ord;
}

void PassengerGateway::switchPaymentType(int passengerId, int paymentType) {
    auto pt = st.get<Passenger>(passengerId);
    auto paymentMethods = SeePaymentMethods(passengerId);
    bool hasPM = false;
    for (auto pm : paymentMethods) {
        if (pm.type == paymentType) {
            hasPM = true;
            break;
        }
    }
    if (!hasPM) {
        throw HasNoSuchPaymentMethod();
    }
    auto vec = st.get_all<Order>(where(c(&Order::passengerId) == passengerId and c(&Order::status) == (int) InProgress));
    for (auto o : vec) {
        o.paymentMethod = paymentType;
        st.update(o);
        cout << st.dump(o) << endl;
    }
    cout << "Passenger " << pt.name << " switched payment method to: " << paymentType << endl;
}

int PassengerGateway::printCurrentCoordinates(int passengerId) {
    auto pt = st.get<Passenger>(passengerId);
    auto orders = st.get_all<Order>(
            where(c(&Order::passengerId) == passengerId && c(&Order::status) != (int) LookingForDriver &&
                  c(&Order::status) != (int) Finished));
    if (orders.size() == 1) {
        auto car = st.get<Car>(st.get<Driver>(orders[0].driverId).currentlyUsedCarId);
        cout << "Location of passenger " << pt.name << " is: " << car.location << endl;
        return car.location;
    } else {
        throw LocationIsNotSpecified();
    }
}

double PassengerGateway::askForBill(int passengerId) {
    auto pt = st.get<Passenger>(passengerId);
    if (!CanAskForBill(passengerId)) {
        throw BlockedFunction();
    }
    auto orders = st.get_all<Order>(
            where(c(&Order::passengerId) == passengerId && c(&Order::status) == (int) InProgress));
    if (orders.size() == 1) {
        cout << "Passenger" << pt.name << "Here is your bill: " << orders[0].costDollars << "$" << endl;
        return orders[0].costDollars;
    } else {
        throw LocationIsNotSpecified();
    }
}

void PassengerGateway::SwitchDevice(int passengerId, int deviceId) {
    auto pt = st.get<Passenger>(passengerId);
    if (!st.count<Device>(where(c(&Device::userId) == passengerId and c(&Device::id) == deviceId))) {
        cout << st.dump(pt) << " Passenger " << pt.name << " have no such device to switch to" << endl;
    } else {
        pt.currentlyUsedDeviceId = deviceId;
        st.update(pt);
        cout << " Passenger " << pt.name << " added a new device " << st.dump(st.get<Device>(deviceId)) << endl;
    }
}

Device PassengerGateway::addDevice(int passengerId, int OS = Android, string name = {}) {
    auto pt = st.get<Passenger>(passengerId);
    Device device(OS, std::move(name));
    device.userId = passengerId;
    device.id = st.insert(device);
    st.update(device);
    cout << "Passenger " << pt.name << " added a new device" << st.dump(device) << endl;
    return device;
}

void PassengerGateway::removeDevice(int passengerId, int deviceId) {
    auto pt = st.get<Passenger>(passengerId);
    if (pt.currentlyUsedDeviceId == deviceId ||
        !st.count<Device>(where(c(&Device::userId) == passengerId and c(&Device::id) == deviceId))) {
        cout << " Passenger " << pt.name << " cannot remove this device" << endl;
    } else {
        st.remove<Device>(deviceId);
        cout << "Passenger " << pt.name << " removed the device: " << deviceId << endl;
    }
}


inline bool PassengerGateway::CanAddPaymentMethod(int passengerId) {
    return CheckBlockedMethod(passengerId, AddPaymentMethod);
}

inline bool PassengerGateway::CanRemovePaymentMethod(int passengerId) {
    return CheckBlockedMethod(passengerId, RemovePaymentMethod);
}

inline bool PassengerGateway::CanMakeOrder(int passengerId) {
    return CheckBlockedMethod(passengerId, MakeOrder);
}

inline bool PassengerGateway::CanAskForBill(int passengerId) {
    return CheckBlockedMethod(passengerId, AskForBill);
}

inline bool PassengerGateway::CheckBlockedMethod(int passengerId, int type) {
    auto pt = st.get<Passenger>(passengerId);
    return !st.count<BlockedMethod>(where(c(&BlockedMethod::userId) == passengerId && c(&BlockedMethod::type) == type));
}
