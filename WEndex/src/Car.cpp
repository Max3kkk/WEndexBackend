//
// Created by michael on 4/14/21.
//

#include "Car.h"

void Car::drive(int to) {
    int from = location;
    int direction = 1;  //1 - "to the Right"
    if (to - from < 0) {
        direction = -1; //1 - "to the Left"
    }
    for (int i = 0; i < abs(from - to); ++i) {
        if (type == Comfort && rand() % 2) {
            if (freeBottleOfWater > 0) {
                freeBottleOfWater--;// TODO: print
            }
        }
        location += direction;  // TODO: print
    }
    park();
}

void Car::park() {
    if (type == Business) {
        parkRightInFrontOfTheEntrance();
    } else {
        parkSeveralBlocksAway();
    }
}

void Car::parkRightInFrontOfTheEntrance() {
    cout << "The car is waiting right in front of the entrance." << endl;
}
void Car::parkSeveralBlocksAway() {
    cout << "Sorry, the car is " << rand() % 3 + 1 << " blocks away from the destination." << endl;
}

string Car::generateNumber() {
    string number{};
    const string CAPS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 3; ++i) {
        number+=CAPS[rand()%(CAPS.size() - 1)];
    }
    for (int i = 0; i < 3; ++i) {
        number+=to_string(rand()%10);
    }
    return number;
}

Car::Car(int model, int type, int location, int color, int freeBottleOfWater)
        : model(model), type(type), location(location), color(color),
          freeBottleOfWater(freeBottleOfWater) {
    if (type != Comfort) {
        freeBottleOfWater = 0;
    }
    number = generateNumber();
}


