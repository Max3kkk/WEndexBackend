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

Car DriverGateway::ChangeCar(int driverId, int model=Seven, int type=Economy, int location = Chernobyl, int color = Cherry, string number = "AAA228AAA"){
    auto dr = st.get<Driver>(driverId);

}
