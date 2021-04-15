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
#endif //WENDEX_EXEPTIONS_H
