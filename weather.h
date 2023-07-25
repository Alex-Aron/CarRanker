#pragma once
#include <iostream>
class weather {
public:
    weather(float p, std::string fDate, int m, int w, int yr, std::string c, std::string cde, std::string loc, std::string st, int aTemp, int max, int min, int windDir, float windS);
    std::string getLocation();
    std::string getCode();
private:
    float precipitation;
    std::string fullDate;
    int month;
    int weekOf;
    int year;
    std::string city;
    std::string code;
    std::string location;
    std::string state;
    int avgTemp;
    int maxTemp;
    int minTemp;
    int windDirection;
    float windSpeed;
};

