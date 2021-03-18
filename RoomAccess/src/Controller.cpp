//
// Created by michael on 3/7/21.
//

#include "../include/Controller.h"

Controller::Controller() {
    dataBaseManager = new DataBaseManager();
    dataBaseManager->addUser(new Director("Ivan", "Ivanov"));
    auto a = new Admin("Sergey", "Serge");
    a->setDataBase(dataBaseManager);
    dataBaseManager->addUser((User*)a);
    auto b = new Admin("Albert", "Smith");
    b->setDataBase(dataBaseManager);
    dataBaseManager->addUser((User*)b);

    dataBaseManager->addUser(new Professor("Ivan", "Konyukhov"));
    dataBaseManager->addUser(new Professor("Manuel", "Mazzara"));
    dataBaseManager->addUser(new Professor("Giancarlo", "Succi"));
    dataBaseManager->addUser(new Professor("Eugene", "Eugene"));

    dataBaseManager->addUser(new LabEmployee("Anton", "Skudarnov"));
    dataBaseManager->addUser(new LabEmployee("Manuel", "Rodrigez"));
    dataBaseManager->addUser(new LabEmployee("Lera", "Vertash"));
    dataBaseManager->addUser(new LabEmployee("Vladislav", "Ostankovich"));
    dataBaseManager->addUser(new LabEmployee("Mansur", "khazeev"));
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


    for (int i = 203; i < 216; ++i) {
        dataBaseManager->addRoom(new ClassRoom(i));
    };

    for (int i = 101; i < 119; ++i) {
        dataBaseManager->addRoom(new LectureRoom(i));
    };

    for (int i = 305; i < 314; ++i) {
        dataBaseManager->addRoom(new ConferenceRoom(i));
    };

    for (int i = 514; i < 523; ++i) {
        dataBaseManager->addRoom(new Cabinet(i));
    };

    dataBaseManager->addRoom(new DirectorCabinet(536));
}

void Controller::readCommands() {
    while (lastCommand != "-1") {
        processCommand();
    }
}

void Controller::processCommand() {
    if (curUser != nullptr) {
        if (instanceOf<Admin>(curUser)) {
            if (chosenUser == nullptr) {
                std::cout << "You are an admin (you can choose anyone to grant access or banning)";
                chooseUser(chosenUser);
            } else if (chosenRoom == nullptr){
                std::cout << "You are an admin, you've chosen: " << curUser->getFirstName() << " " << curUser->getSecondName() << " (to  to grant access or ban) ";
                chooseRoom(chosenRoom);
            } else {
                if (lastCommand != "d" && lastCommand != "g") {
                    std::cout << R"(To grant access type "g", to ban person for this room "b",
                    to finish program "-1", to return to beginning "-2")"<< std::endl;
                    std::cin >> lastCommand;
                }
                if (lastCommand == "b") {
                    ((Admin*)curUser)->denyAccess(chosenUser->getId(), chosenRoom->getId());
                    std::cout << "You successfully banned room#" << chosenRoom->getId() <<
                    " for " << curUser->getFirstName() << " " << curUser->getSecondName() << std::endl;
                    reset();
                } else if (lastCommand == "g") {
                    ((Admin*)curUser)->grantAccess(chosenUser->getId(), chosenRoom->getId());
                    std::cout << "You successfully granted access to room#" << chosenRoom->getId() <<
                              " for " << curUser->getFirstName() << " " << curUser->getSecondName() << std::endl;
                    reset();
                }
            }
        } else { //if we are not an admins and we want to choose a room to book or discard booking
            if (chosenRoom == nullptr){
                std::cout << "You are " << curUser->getFirstName() << " " << curUser->getSecondName()
                <<", you can choose room to book or discard yor booking)";
                chooseRoom(chosenRoom);
            } else {
                if (chosenRoom->isBooked() && chosenRoom->getCurUserId() != curUser->getId() || (!chosenRoom->isBooked() && !dataBaseManager->canBook(curUser, chosenRoom))) {
                    std::cout << "Sorry " << curUser->getFirstName() << " " << curUser->getSecondName()
                    << " access to this room is denied. You should choose another room" << std::endl;
                    chosenRoom = nullptr;
                }
                std::cout << "last";
                if (lastCommand != "d" && lastCommand != "b") {
                    std::cout << R"(To book this room type "b", to discard booking "d",
                    to finish program "-1", to return to beginning "-2")" << std::endl;
                    std::cin >> lastCommand;
                    if (lastCommand == "-2") {
                        reset();
                    }
                }
                if (lastCommand == "d") {
                    if(chosenRoom->getCurUserId() != curUser->getId()) {
                        lastCommand = "";
                        std::cout << "You cannot discard booking of this room" << std:: endl;
                    }
                    chosenRoom->discardBooking();
                    std::cout << "You successfully discarded booking" << std::endl;
                    reset();
                    return;
                } else if (lastCommand == "b"){
                    chosenRoom->book(curUser->getId());
                    std::cout << "You successfully booked the room #" << chosenRoom->getNumber() << std::endl;
                    reset();
                }
            }
        }
    } else {
        std::cout << "[It is the \"God Mode\"] (you can choose to be anyone, even an admin) ";
        chooseUser(curUser);
    }

}

template<typename Base, typename T>
bool Controller::instanceOf(const T *ptr) {
    return (dynamic_cast<const Base*>(ptr) != nullptr);
}

void Controller::chooseUser(User*& ptr) {
    std::cout << "Here is the list of all users:" << std::endl;
    for (User* u : dataBaseManager->getUsers()) {
        std::string type{};
        if (instanceOf<Student>(u)) {
            type = "student";
        } else if (instanceOf<LabEmployee>(u)) {
            type = "lab employee";
        } else if (instanceOf<Professor>(u)) {
            type = "professor";
        } else if (instanceOf<Director>(u)) {
            type = "director";
        } else if (instanceOf<Admin>(u)) {
            type = "admin";
        }
        std::cout << "id: " << u->getId() << " " << type << " " << u->getSecondName() << " " << u->getFirstName() << std:: endl;
    }
    std::cout << "You can finish the program by typing \"-1\" or \"-2\" if you want to return to return to the beginning"
                 "\nWrite an id of the user you want to choose: ";
    int id;
    std:: cin >> id;
    std::cout << std::endl;
    lastCommand = std::to_string(id);
    if (lastCommand == "-2") {
        reset();
    } else if (dataBaseManager->hasUser(id)) {
        ptr = dataBaseManager->getUser(id);
    }
}

void Controller::chooseRoom(Room*& ptr) {
    std::cout << "Here is the list of all rooms:" << std::endl;
    for (auto r : dataBaseManager->getRooms()) {
        std::string type{};
        if (instanceOf<ClassRoom>(r)) {
            type = "class room";
        } else if (instanceOf<LectureRoom>(r)) {
            type = "lecture room";
        } else if (instanceOf<ConferenceRoom>(r)) {
            type = "conference room";
        } else if (instanceOf<Cabinet>(r)) {
            type = "cabinet";
        } else if (instanceOf<DirectorCabinet>(r)) {
            type = "director cabinet";
        }
        std::cout << "id: " << r->getId() << " " << type << " #" << r->getNumber();
        if (r->isBooked()) {
            auto booker = dataBaseManager->getUser(r->getCurUserId());
            std::cout << " Booked by: " << booker->getFirstName() << " " << booker->getSecondName();
        }
        std::cout << std::endl;
    }
    std::cout << "You can finish the program by typing \"-1\" or \"-2\" if you want to return to return to the beginning"
                 "\nWrite an id of the room you want to choose: ";
    int id;
    std::cin >> id;
    std::cout << std::endl;
    lastCommand = std::to_string(id);
    if (lastCommand == "-2") {
        reset();
    } else if (dataBaseManager->hasRoom(id)) {
        ptr = dataBaseManager->getRoom(id);
    }
}

void Controller::reset() {
    lastCommand = "-2";
    curUser = nullptr;
    lastCommand = "";
    chosenUser = nullptr;
    chosenRoom = nullptr;
}

