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

