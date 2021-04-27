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
    Chernobyl, Moscow, Berlin, Sydney, Kazan, NewYork, Paris, London, Innopolis
};

enum ColorType{
    Red, Black, Cherry, Blue, White, Gold
};
enum ModelType{
    MercedesBenz,
    Toyota,
    Volkswagen,
    BMW,
    Porsche,
    Honda,
    Ford,
    Nissan,
    Seven
};

class Car {
public:
    int id{-1};
    int model{Seven};
    int driverId{-1};
    int type{Economy};
    int location{Chernobyl};
    int color{Cherry};
    bool isValidated{false};
    string number{};
    int freeBottleOfWater = 0;

    explicit Car(int model=Seven, int type=Economy, int location = Chernobyl, int color = Cherry, int freeBottleOfWater = 0);

    void drive(int to);
private:
    string generateNumber();
    void park();
    void parkRightInFrontOfTheEntrance();
    void parkSeveralBlocksAway();
};
#endif //WENDEX_CAR_H
