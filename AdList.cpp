#include "AdList.h"

void AdList::insertCarEdge(cars from, cars to) {
    carGraph[from.getID()].push_back(to);//Insert edge with vertices on graph
    if(carGraph.find(to.getID()) == carGraph.end()) {
        carGraph[to.getID()] = {};
    }
}

void AdList::insertWeatherEdge(weather from, weather to) {
    weatherGraph[from.getCode()].push_back(to);//Insert edge with vertices on graph
    if(weatherGraph.find(to.getCode()) == weatherGraph.end()) {
        weatherGraph[to.getCode()] = {};
    }
}

void AdList::carBFS(std::string startV) {

}
