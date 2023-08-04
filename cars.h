#pragma once
#include <iostream>
class cars {
public:
    cars(int l, int w, int h, std::string driveLine, std::string enType, bool isH, int gears, std::string trans, int cityM, std::string fType, int hM, std::string autoOrManual, std::string id, std::string Make, std::string Model, int Year, int HP, int to) {
        length = l;
        width = w;
        height = h;
        this->driveLine = driveLine;
        engineType = enType;
        isHybrid = isH;
        numGears = gears;
        transmission = trans;
        cityMPG = cityM;
        fuelType = fType;
        highwayMPG = hM;
        isAuto = autoOrManual;
        ID = id;
        make = Make;
        model = Model;
        year = Year;
        horsepower = HP;
        torque = to;
    };
    std::string getID();
    std::string getMake();
    std::string getModel();
    std::string getAutoOrManual();
    std::string getDriveLine();
    int getHorsepower();
    int getCityMPG();
    int getHighwayMPG();
    void printCar();
    std::string carText();
private:
    int length;
    int width;
    int height;
    std::string driveLine;
    std::string engineType;
    bool isHybrid;
    int numGears;
    std::string transmission;
    int cityMPG;
    std::string fuelType;
    int highwayMPG;
    std::string isAuto;
    std::string ID;
    std::string make;
    std::string model;
    int year;
    int horsepower;
    int torque;

}; 