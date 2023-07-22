#include "AdList.h"

void AdList::insertEdge(cars from, cars to) {
    graph[from.getID()].push_back(to);//Insert edge with vertices on graph
    if(graph.find(to.getID()) == graph.end()) {
        graph[to.getID()] = {};
    }
}
