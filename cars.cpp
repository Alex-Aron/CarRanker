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
    std::cout << "Length: " << length << "; width: " << width << "; height: " << height << "; driveline: " << driveLine << "; engine type: " <<
        engineType << "; is hybrid: " << isHybrid << "; number of gears: " << numGears << "; transmission: " << transmission << "; city MPG: "
        << cityMPG << "; fuel type: " << fuelType << "; highway MPG: " << highwayMPG << "; transmission type: " << isAuto << "; ID: " <<
        ID << "; make: " << make << "; model: " << model << "; year: " << year << "; horsepower: " << horsepower << "; torque: " <<
        torque   << std::endl;
}

std::string cars::getModel() {
    return model;
}

std::string cars::carText() {
    std::string hybrid = "False";
    std::string automatic = "Manual";
    if(isHybrid)
        hybrid = "True";
    if(isAuto == "Automatic transmission")
        automatic = "Automatic";
    return "Length: " + std::to_string(length) + "\nWidth: " + std::to_string(width)+ "\nHeight: " + std::to_string(height) + "\nDriveline: " + driveLine + "\nEngine type: " +
                      engineType + "\nIs hybrid: " + hybrid + "\nNumber of gears: " + std::to_string(numGears) + "\nTransmission: " + transmission + "\nCity MPG: "
                      + std::to_string(cityMPG) + "\nFuel type: " + fuelType + "\nHighway MPG: " + std::to_string(highwayMPG) + "\nTransmission type: " + automatic + "\nID: " +
                      ID + "\nMake: " + make + "\nModel: " + model + "\nYear: " + std::to_string(year) + "\nHorsepower: " + std::to_string(horsepower) + "\nTorque: " +
                      std::to_string(torque);
}

std::string cars::getAutoOrManual() {
    return isAuto;
}

std::string cars::getDriveLine() {
    return driveLine;
}
