#include "weather.h"

weather::weather(float p, std::string fDate, int m, int w, int yr, std::string c, std::string cde, std::string loc,
                 std::string st, int aTemp, int max, int min, int windDir, float windS) {
    precipitation = p;
    fullDate = fDate;
    month = m;
    weekOf = w;
    year = yr;
    city = c;
    code = cde;
    location = loc;
    state = st;
    avgTemp = aTemp;
    maxTemp = max;
    minTemp = min;
    windDirection = windDir;
    windSpeed = windS;
}

std::string weather::getLocation() {
    return location;
}

std::string weather::getCode() {
    return code;
}

std::string weather::getState() {
    return state;
}

int weather::getMinTemp() {
    return minTemp;
}


