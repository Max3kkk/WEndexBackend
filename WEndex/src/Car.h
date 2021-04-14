//
// Created by michael on 4/14/21.
//

#ifndef WENDEX_CAR_H
#define WENDEX_CAR_H
#include <utility>

#include "vector"
#include "string"
#include "iostream"

using namespace std;
enum CarType {
Economy, Comfort,
ComfortPlus, Business
};

enum LocationType {
    Chernobyl, Moscow, Berlin, Sydney, Kazan, NewYork, Paris, London
};

class Car {
public:
    int id{};
    string model{};
    int type{Economy};
    int location;
    string color{};
    string number{};
    int freeBottleOfWater = rand() % 5 + 1;

    inline Car(string model, int type, int location, string color, string number, int freeBottleOfWater)
            : model(std::move(model)), type(type), location(location), color(std::move(color)), number(std::move(number)),
              freeBottleOfWater(freeBottleOfWater) {}

    void drive(int to);
private:
    void park();
    void parkRightInFrontOfTheEntrance();
    void parkSeveralBlocksAway();
};
#endif //WENDEX_CAR_H
