#include "cars.h"

std::string cars::getID() {
    return ID;
}

std::string cars::getMake() {
    return make;
}

int cars::getHorsepower() {
    return horsepower;
}

int cars::getCityMPG() {
    return cityMPG;
}

int cars::getHighwayMPG() {
    return highwayMPG;
}

void cars::printCar() {
    std::cout << "Length: " << length << "; width: " << width << "; heigth: " << height << "; driveline: " << driveLine << "; engine type: " <<
        engineType << "; is hybrid: " << isHybrid << "; number of gears: " << numGears << "; transmission: " << transmission << "; city MPG: "
        << cityMPG << "; fuel type: " << fuelType << "; highway MPG: " << highwayMPG << "; transmission type: " << isAuto << "; ID: " <<
        ID << "; make: " << make << "; model: " << model << "; year: " << year << "; horsepower: " << horsepower << "; torque: " <<
        torque << std::endl;
}