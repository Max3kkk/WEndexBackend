//
// Created by michael on 2021-04-26.
//

#ifndef WENDEX_DEVICE_H
#define WENDEX_DEVICE_H
#include "string"
enum OS {
    Linux, iOS, macOS, Android, Windows, Avrora, TempleOS
};

class Device {
public:
    int id{-1};
    int userId{-1};
    string name{};
    int operatingSystem{Linux};
    Device(int os, string Name) : operatingSystem(os), name(Name) {}
    Device() = default;
};
#endif //WENDEX_DEVICE_H
