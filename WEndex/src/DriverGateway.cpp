//
// Created by michael on 4/14/21.
//

#include "DriverGateway.h"

void DriverGateway::Register(const string& name, const string& login, const string& password) {
    if (st.count<Driver>(where(c(&Driver::login) == login))){
        throw LoginIsTaken();
    }
    int carId = st.insert(Car());   //default Car
    st.insert(Driver(name, login, password, carId));
}

Driver DriverGateway::Login(const string& login, const string& password) {
    auto vec = st.get_all<Driver>(where(c(&Driver::login) == login && c(&Driver::password) == password));
    if (vec.size() != 1) {
        throw WrongLoginOrPassword();
    }
    cout << "You are succesefully signed in " << vec[0].name << endl;
    //cout << st.dump(vec[0]);
    return vec[0];
}

Car DriverGateway::UpgradeCar(int driverId, int model=Seven, int type=Economy, int location = Chernobyl, int color = Cherry, string number = "AAA228AAA"){
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.carId);
    car.location = location;
    car.model = model;
    car.type = type;
    car.color - color;
    car.number = number;
    st.update(car);
    return car;
}

vector<Order> DriverGateway::FindAvailableOrders(int driverId) {
    auto orders = st.get_all<Order>(where(c(&Order::driverId) == driverId) && (c(&Order::status) == (int)LookingForDriver));
    for (auto o : orders) {
        cout << st.dump(o);
    }
    return orders;
}

vector<Order> DriverGateway::SeeOrderHistory(int driverId) {
    auto orders = st.get_all<Order>(where(c(&Order::driverId) == driverId) && c(&Order::status) == (int)Finished);
    for (auto o : orders) {
        cout << st.dump(o);
    }
    return orders;
}

Car DriverGateway::SeeCar(int driverId){
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.carId);
    cout << st.dump(car);
    cout << "Status of driver " << dr.name << " changed car" << endl;
    return car;
}

int DriverGateway::ChangeStatus(int driverId, int status) {
    auto dr = st.get<Driver>(driverId);
    dr.status = status;
    st.update(dr);
    cout << "Status of driver " << dr.name << " is now << dr.status" << endl;
    return dr.status;
}

void DriverGateway::GetOrder(int driverId, int orderId){
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.carId);
    auto ord = st.get<Order>(orderId);
    if (ord.status != LookingForDriver && dr.status != Available) {
        throw OrderIsNotAvailable();
    }

    ChangeStatus(driverId, Driving);
    ord.status = WaitingForDriverArrival;
    car.drive(ord.fromAddress);
    st.update(car);
    st.update(ord);
    cout << "The ride has began, take your seat." << endl;
    ord.status = InProgress;
    o
}
