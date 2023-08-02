#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "cars.h"
#include "weather.h"
class AdList {
private:
    std::map<std::string, std::vector<cars>> carGraph;
    std::map<std::string, std::vector<weather>> weatherGraph;
    std::map<cars, std::vector<cars>> visitedTracker;//Copy of graph, but backwards.
public:
    void insertCarEdge(cars from, cars to);
    void carBFS(std::string startV);
    void carDFS(std::string startV);
    void insertWeatherEdge(weather from, weather to);
    void weatherBFS();
    AdList() {};
};
