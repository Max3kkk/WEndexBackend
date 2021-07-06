//
// Created by michael on 4/14/21.
//

#include "DriverGateway.h"

#include <utility>

void DriverGateway::Register(const string& name, const string& login, const string& password) {
    if (st.count<Driver>(where(c(&Driver::login) == login))) {
        auto driver = st.get_all<Driver>(where(c(&Driver::login) == login));
        if (driver.size() != 1){
            throw LoginIsTaken();
        } else if (driver[0].password == password){
            cout << name << ", you are already registered as a driver" << endl;
            return;
        }
    }
    Car car;
    int CarId = st.insert(car);
    car.id = CarId;
    Driver driver(name, login, password, car.id);
    int DriverId = st.insert(driver);
    driver.id = DriverId;
    driver.currentlyUsedCarId = CarId;
    car.driverId = DriverId;
    st.update(driver);
    st.update(car);
    cout << st.dump(driver) << ", you are successfully registered as a driver "<< endl;
}

Driver DriverGateway::Login(const string& login, const string& password) {
    auto vec = st.get_all<Driver>(where(c(&Driver::login) == login && c(&Driver::password) == password));
    if (vec.size() != 1) {
        throw WrongLoginOrPassword();
    }
    cout << "You are successfully logged in as driver: " << st.dump(vec[0]) << endl;
    return vec[0];
}

Car DriverGateway::UpgradeCar(int driverId, int model=Seven, int type=Economy, int color = Cherry){
    if (!CanUpgradeCar(driverId)) {
        throw BlockedFunction();
    }
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.currentlyUsedCarId);
    car.model = model;
    car.type = type;
    car.color = color;
    if (type == Comfort) {
        car.freeBottleOfWater = rand() % 5 + 1;
    }
    st.update(car);
    cout << "Driver " << dr.name <<" upgraded car" << st.dump(car) << endl;
    return car;
}

vector<Order> DriverGateway::FindAvailableOrders(int driverId) {
    if (!CanFindAvailableOrders(driverId)) {
        throw BlockedFunction();
    }
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.currentlyUsedCarId);
    auto orders = st.get_all<Order>(where(c(&Order::driverId) == driverId) &&
            (c(&Order::status) == (int)LookingForDriver && c(&Order::carType) == car.type) && dr.status == Available);
    cout << "Orders available for driver " << dr.name <<  endl;
    for (auto o : orders) {
        cout << st.dump(o) << endl;
    }
    return orders;
}

vector<Order> DriverGateway::SeeOrderHistory(int driverId) {
    cout << "Orders order history:" <<  endl;
    auto orders = st.get_all<Order>(where(c(&Order::driverId) == driverId) && c(&Order::status) == (int)Finished);
    for (auto o : orders) {
        cout << st.dump(o) << endl;
    }
    return orders;
}

Car DriverGateway::SeeCar(int driverId){
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.currentlyUsedCarId);
    cout << st.dump(car);
    cout << "Status of driver " << dr.name << " changed car" << endl;
    return car;
}

int DriverGateway::ChangeStatus(int driverId, int status) {
    auto dr = st.get<Driver>(driverId);
    dr.status = status;
    st.update(dr);
    cout << "Status of driver " << dr.name << " changed status to " << dr.status << endl;
    return dr.status;
}

void DriverGateway::GetOrder(int driverId, int orderId){
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.currentlyUsedCarId);
    auto ord = st.get<Order>(orderId);
    if (!CarValid(dr.currentlyUsedCarId)) {
        throw CarIsInvalidated();
    }
    if (!CanAcceptRide(driverId)) {
        throw BlockedFunction();
    }
    if (ord.status != LookingForDriver && dr.status != Available) {
        throw OrderIsNotAvailable();
    }
    if (!(rand() % 5)) {
        cout << "Driver " << dr.name << " did not accepted the order" << endl;
        return;
    }
    ChangeStatus(driverId, Driving);
    ord.status = WaitingForDriverArrival;
    st.update(ord);
    car.drive(ord.fromAddress);
    st.update(car);
    cout << "The ride has began, take your seat." << endl;
    ord.status = InProgress;
    st.update(ord);
    car.drive(ord.toAddress);
    st.update(car);
    cout << "The ride has finished, you can leave the car." << endl;
    ord.status = Finished;
    st.update(ord);
    if (rand() % 3) {
        ChangeStatus(driverId, Available);
    } else {
        ChangeStatus(driverId, NotWorking);
    }
}

void DriverGateway::doRandomAvailableOrder(int driverId) {
    auto dr = st.get<Driver>(driverId);
    if (!CarValid(dr.currentlyUsedCarId)) {
        throw CarIsInvalidated();
    }
    if (!CanFindAvailableOrders(driverId)) {
        throw BlockedFunction();
    }
    auto ord = FindAvailableOrders(driverId);
    if (ord.size() != 1) {
        OrderIsNotAvailable();
    }
    cout <<"Driver " << dr.name <<" chose to do Order:  " << st.dump(ord[0]) << endl;
    GetOrder(driverId,ord[0].id);
}

Car DriverGateway::AddNewCar(int driverId, int model=Seven, int type=Economy, int color = Cherry){
    auto dr = st.get<Driver>(driverId);
    Car car;
    car.model = model;
    car.type = type;
    car.color = color;
    car.driverId = driverId;
    if (type == Comfort) {
        car.freeBottleOfWater = rand() % 5 + 1;
    }
    car.id = st.insert(car);
    st.update(car);
    cout <<"Driver " << dr.name <<" added new car " << st.dump(car) << endl;
    return car;
}

Car DriverGateway::SwitchCar(int driverId, int carId){
    auto dr = st.get<Driver>(driverId);
    auto curCar = st.get<Car>(dr.currentlyUsedCarId);
    auto otherCar = st.get<Car>(carId);
    if (!otherCar.driverId == driverId) {
        throw WrongCar();
    }
    dr.currentlyUsedCarId = otherCar.id;
    st.update(dr);
    cout <<"Driver " << dr.name <<" switched to a another car: " << st.dump(otherCar) << endl;
    return otherCar;
}

inline bool DriverGateway::CarValid(int driverId) {
    auto dr = st.get<Driver>(driverId);
    auto car = st.get<Car>(dr.currentlyUsedCarId);
    return car.isValidated;
}

inline bool DriverGateway::CanAcceptRide(int driverId) {
    auto dr = st.get<Driver>(driverId);
    return !st.count<BlockedMethod>(where(c(&BlockedMethod::userId) == driverId && c(&BlockedMethod::type) == (int)AcceptRide));
}

inline bool DriverGateway::CanUpgradeCar(int driverId) {
    auto dr = st.get<Driver>(driverId);
    return !st.count<BlockedMethod>(where(c(&BlockedMethod::userId) == driverId && c(&BlockedMethod::type) == (int)UpgradeCurrentCar));
}

inline bool DriverGateway::CanFindAvailableOrders(int driverId) {
    auto dr = st.get<Driver>(driverId);
    return !st.count<BlockedMethod>(where(c(&BlockedMethod::userId) == driverId && c(&BlockedMethod::type) == (int)FindAllAvailableOrders));
}