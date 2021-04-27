//
// Created by michael on 2021-04-26.
//

#include "AdminGateway.h"

void AdminGateway::Register(const string &name, const string &login, const string &password) {
    if (st.count<Admin>(where(c(&Admin::login) == login))) {
        auto adm = st.get_all<Admin>(where(c(&Admin::login) == login));
        if (adm.size() != 1) {
            throw LoginIsTaken();
        } else if (adm[0].password == password) {
            cout << name << ", you are already registered as an admin" << endl;
            return;
        }
    }
    st.insert(Admin(name,login,password));
    cout << "You are successfully registered as an admin " << name << endl;
}

Admin AdminGateway::Login(const string &login, const string &password) {
    auto vec = st.get_all<Admin>(where(c(&Admin::login) == login && c(&Admin::password) == password));
    if (vec.size() != 1) {
        throw WrongLoginOrPassword();
    }
    cout << "You are successfully logged in as an admin:  " << st.dump(vec[0]) << endl;
    return vec[0];
}

vector<Passenger> AdminGateway::seeAllPassengers(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<Passenger>();
    cout << "Here is the list of all Passengers:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<Order> AdminGateway::seeAllOrders(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<Order>();
    cout << "Here is the list of all Orders:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<Car> AdminGateway::seeAllCars(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<Car>();
    cout << "Here is the list of all Cars:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<PaymentMethod> AdminGateway::seeAllPaymentMethods(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<PaymentMethod>();
    cout << "Here is the list of all Payment Methods:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<Driver> AdminGateway::seeAllDrivers(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<Driver>();
    cout << "Here is the list of all Drivers:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<Device> AdminGateway::seeAllDevices(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<Device>();
    cout << "Here is the list of all Devices:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

vector<BlockedMethod> AdminGateway::seeBlockedMethods(int adminId) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    auto vec = st.get_all<BlockedMethod>();
    cout << "Here is the list of all Blocked Methods:" << endl;
    for (auto el : vec) {
        cout << st.dump(el) << endl;
    }
    return vec;
}

void AdminGateway::BlockMethod(int adminId, int userId, int methodType) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    if (!st.count<BlockedMethod>(where(c(&BlockedMethod::userId) == userId && c(&BlockedMethod::type) == methodType))) {
        st.insert(BlockedMethod(methodType, userId));
    }
}

void AdminGateway::UnBlockMethod(int adminId, int userId, int methodType) {
    if (!IsAdmin(adminId)) {
        throw NotAdmin();
    }
    st.remove_all<BlockedMethod>(where(c(&BlockedMethod::userId) == userId && c(&BlockedMethod::type) == methodType));
}

bool AdminGateway::IsAdmin(int adminId) {
    return st.count<Admin>(where(c(&Admin::id) == adminId));
}