//
// Created by michael on 3/7/21.
//

#include "../include/Controller.h"

Controller::Controller() {
    //create and add users to database
    dataBaseManager = new DataBaseManager();
    dataBaseManager->addUser(new Director("Kirill", "Semenikhin"));

    dataBaseManager->addUser(new Admin("Anna", "Yakimova", dataBaseManager));
    dataBaseManager->addUser(new Admin("Pavel", "Zotov", dataBaseManager));

    dataBaseManager->addUser(new Professor("Ivan", "Konyukhov"));
    dataBaseManager->addUser(new Professor("Manuel", "Mazzara"));
    dataBaseManager->addUser(new Professor("Giancarlo", "Succi"));
    dataBaseManager->addUser(new Professor("Eugene", "Eugene"));

    dataBaseManager->addUser(new LabEmployee("Anton", "Skudarnov"));
    dataBaseManager->addUser(new LabEmployee("Manuel", "Rodrigez"));
    dataBaseManager->addUser(new LabEmployee("Lera", "Vertash"));
    dataBaseManager->addUser(new LabEmployee("Vladislav", "Ostankovich"));
    dataBaseManager->addUser(new LabEmployee("Mansur", "Khazeev"));
    dataBaseManager->addUser(new LabEmployee("Marya", "Naumcheva"));
    dataBaseManager->addUser(new LabEmployee("Ramil", "Dautov"));
    dataBaseManager->addUser(new LabEmployee("Imre", "Delgado"));

    dataBaseManager->addUser(new Student("Mikhail", "Fedorov"));
    dataBaseManager->addUser(new Student("Albert", "Karabanov"));
    dataBaseManager->addUser(new Student("Anna", "kopeikina"));
    dataBaseManager->addUser(new Student("Igor", "Alentev"));
    dataBaseManager->addUser(new Student("Nickolas", "Evkarpidi"));
    dataBaseManager->addUser(new Student("Mark", "Esian"));
    dataBaseManager->addUser(new Student("Alexandr", "Strelnikov"));
    dataBaseManager->addUser(new Student("Katya", "Skvortsova"));
    dataBaseManager->addUser(new Student("Mohamed", "Selim"));
    dataBaseManager->addUser(new Student("Evgene", "Ageev"));
    dataBaseManager->addUser(new Student("Alfiya", "Mussabekova"));
    dataBaseManager->addUser(new Student("Elena", "Murtazina"));
    dataBaseManager->addUser(new Student("Danil", "Latypov"));
    dataBaseManager->addUser(new Student("Artyom", "Yuloskov"));
    dataBaseManager->addUser(new Student("Egor", "Gorozhankin"));
    dataBaseManager->addUser(new Student("Anatoliy", "Baskakov"));

    dataBaseManager->addUser(new Guest("Ruslan", "Hairov"));
    dataBaseManager->addUser(new Guest("Vitaliy", "Koltsov"));
    dataBaseManager->addUser(new Guest("Maksim", "Insapov"));
    dataBaseManager->addUser(new Guest("Zamira", "Galyautdinova"));

    //create and add rooms to database
    for (int i = 101; i < 110; ++i) {
        dataBaseManager->addRoom(new LectureRoom(i%100, i/100));
    }
    for (int i = 110; i < 116; ++i) {
        dataBaseManager->addRoom(new ConferenceRoom(i%100, i/100));
    }

    for (int i = 201; i < 212; ++i) {
        dataBaseManager->addRoom(new LectureRoom(i%100, i/100));
    }
    for (int i = 212; i < 216; ++i) {
        dataBaseManager->addRoom(new ClassRoom(i%100, i/100));
    }

    for (int i = 305; i < 314; ++i) {
        dataBaseManager->addRoom(new ConferenceRoom(i%100, i/100));
    }
    for (int i = 514; i < 523; ++i) {
        dataBaseManager->addRoom(new Cabinet(i%100, i/100));
    }

    dataBaseManager->addRoom(new DirectorCabinet(36, 5));
}
//print all users all prompt for user id
void Controller::chooseUser(User*& ptr) {
    std::cout << "\tHere is the list of all users:" << std::endl;
    dataBaseManager->printUsers();
    int id = processCommand();
    ptr = dataBaseManager->getUser(id);
}
//print all rooms all prompt for room id
void Controller::chooseRoom() {
    std::cout << "\tHere is the list of all rooms:" << std::endl;
    dataBaseManager->printRooms();
    int id = processCommand();
    curRoom = dataBaseManager->getRoom(id);
}

// always read and process data from console
[[noreturn]] void Controller::readConsole() {
    while (true) {
        processConsole();
    }
}

// all main console logic is here
// depending on what user or room you chose there is different logic for each
void Controller::processConsole() {
    if (curUser == nullptr) {   //no users are chosen
        std::cout << "\t[God Mode] (you can choose to be anyone, even an admin) " << std::endl;
        chooseUser(curUser);
        return;
    } else {    //if we've chosen a user "control"
        //get info from user to define if its an admin
        std::string userType = curUser->getUserInfo().substr(0, curUser->getUserInfo().find(" "));
        transform(userType.begin(), userType.end(), userType.begin(), tolower);
        if (userType == "admin") {  // admin:
            if (userChosenByAdmin != nullptr) { // admin: ban or grant access to currently chosen user
                if (curRoom == nullptr) { // admin: if the room is not chosen
                    std::cout << "\tYou are " << curUser->getUserInfo() << std::endl;
                    std::cout << " You have to choose a room to change an access" << std::endl;
                    chooseRoom();
                } else {    // admin: chose ban/grant access or to access some room
                    std::cout << "\tYou are " << curUser->getUserInfo() << std::endl;
                    std::cout << "\n -to ban chosen user for some room type \"-5\""
                                 "\n -to grant access to user to some room type \"-10\"" << std::endl;
                    int com = processCommand();
                    if (com == 1) {    // admin: ban user
                        ((Admin *) curUser)->denyAccess(userChosenByAdmin->getId(), curRoom->getId());
                        std::cout << "\tYou successfully baned room#" << curRoom->getId() <<
                                  " for " << curUser->getUserInfo() << std::endl;
                        reset();
                    } else if (com == 2) {     // admin: grant access to user
                        ((Admin *) curUser)->grantAccess(userChosenByAdmin->getId(), curRoom->getId());
                        std::cout << "\tYou successfully granted access to room#" << curRoom->getId() <<
                                  " for " << curUser->getUserInfo() << std::endl;
                        reset();
                    }
                }
            } else if (curRoom != nullptr) {    // admin: try to access currently chosen room
                tryAccess();
            } else {    // admin: choose something to do
                std::cout << "\tYou are " << curUser->getUserInfo() <<
                          "\n -to choose a room to access type \"-5\""
                          "\n -to choose a user for granting access or banning type \"-10\"" << std::endl;
                int com = processCommand();
                if (com == 1) {     // admin: choose a room to access
                    chooseRoom();
                } else if (com == 2) { // admin: choose a user to grant access/ban
                    chooseUser(userChosenByAdmin);
                }
            }
        } else {// user: access some room
            tryAccess();
        }
    }
}

// choose and access some room
void Controller::tryAccess(){
    if (curRoom == nullptr){    // if no room is chosen
        std::cout << "\tYou are " << curUser->getUserInfo() << std::endl;
        std::cout << "\tChoose a room to access" << std::endl;
        chooseRoom();
    } else {    // we've chosen some room
        if (curRoom->isAccessible(curUser->getId(), curUser->getAccessLevel()) || isEmergency) {
            std::cout << "\tYou successfully accessed " << curRoom->getRoomInfo() << std::endl;
        } else {    // we cannot access room
            std::cout << "\tYou cannot access " << curRoom->getRoomInfo() << std::endl;
        }
        reset();
    }
}

// resets back to a [God Mode], but keeps Emergency running
void Controller::reset(){
    curUser = nullptr;
    userChosenByAdmin = nullptr;
    curRoom = nullptr;
}

// read inputs from console and processes it
int Controller::processCommand() {
    if (isEmergency) {
        std::cout << " AAAAAAAAAAAAA, there is a SUS among us, all rooms are open, Emergency!!!" << std::endl;
    }
    std::cout << " -to finish the program type \"-1\""
                 "\n -to return to God Mode type \"-2\""
                 "\n -to toggle an emergency type \"-404\"" << std::endl;
    std::cin >> curCommand;
    switch (curCommand) {
        case -1:
            exit(0);
        case -2:
            isEmergency = false;
            reset();
            break;
        case -5:
            return 1;
        case -10:
            return 2;
        case -404:
            isEmergency = !isEmergency;
            break;
        default:
            return curCommand;
    }
    return 0;
}

