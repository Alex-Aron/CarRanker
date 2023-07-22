#pragma once
#include <iostream>
class cars {
public:
    cars(int l, int w, int h, std::string driveLine, std::string enType, bool isH, int gears, std::string trans, int cityM, std::string fType, int hM, bool autoOrManual, std::string id, std::string Make, std::string Model, int Year, int HP, int to){
    length = l;
    width = w;
    height = h;
    driveLine = AWD;
    engineType = enType;
    isHybrid = isH;
    numGears = gears;
    transmission = trans;
    cityMPG = cityM;
    fuelType = gasoline;
    highwayMPG = hM;
    isAuto = autoOrManual;
    ID = id;
    make = Make;
    model = Model;
    year = Year;
    horsepower = HP;
    torque = to;
    };

private:
    int length;
    int width;
    int height;
    enum engineDriveLine {AWD = 1, FWD = 2, RWD = 3, fourWD = 4} driveLine;
    std::string engineType;
    bool isHybrid;
    int numGears;
    std::string transmission;
    int cityMPG;
    enum fuelType {gasoline, diesel, e85, natGas} fuelType;
    int highwayMPG;
    bool isAuto;
    std::string ID;
    std::string make;
    std::string model;
    int year;
    int horsepower;
    int torque;

};

