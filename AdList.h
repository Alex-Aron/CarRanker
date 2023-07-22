#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "cars.h"
class AdList {
private:
    std::map<std::string, std::vector<cars>> graph;
    std::map<cars, std::vector<cars>> visitedTracker;//Copy of graph, but backwards.
public:
    void insertEdge(cars from, cars to);
    AdList() {};
};
