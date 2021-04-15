//
// Created by michael on 4/15/21.
//

#ifndef WENDEX_EXEPTIONS_H
#define WENDEX_EXEPTIONS_H
#include "exception"
#include "string"

using namespace std;

class LoginIsTaken: public exception {
    virtual const char* what() const throw(){
        return "Please choose another login, this login is taken.";
    }
};

class WrongLoginOrPassword: public exception {
    virtual const char* what() const throw() {
        return "Login or Password is incorrect.";
    }
};

class OrderIsNotAvailable: public exception {
    virtual const char* what() const throw() {
        return "Driver cannot take the order";
    }
};

class LocationIsNotSpecified: public exception {
    virtual const char* what() const throw() {
        return "There is no current rides to specify the location";
    }
};

class HasNoSuchPaymentMethod: public exception {
    virtual const char* what() const throw() {
        return "Passenger has no such payment method";
    }
};

#endif //WENDEX_EXEPTIONS_H
