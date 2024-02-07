#include <iostream>
#include "Path.hpp"

// sets the distance between two stations connected by train or taxi
void Path::setTrainTaxiDistance(unsigned int distance) 
{
    this->trainTaxiDistance = distance;
}     


// sets the distance between two stations connected by bus 
void Path::setBusDistance(unsigned int distance) 
{
    this->busDistance = distance;
}  


// returns the distance between two stations connected by train ot taxi
unsigned int Path::getTrainTaxiDistance() const 
{
    return (this->trainTaxiDistance);
}


// returns the distance between two stations connected by bus 
unsigned int Path::getBusDistance() const 
{
    return (this->busDistance);
}    

// pushes a station into a list which is used for dijkstra algorithm 
void Path::setDijkstraList(std::string station) 
{
    this->dijkstraList.push_back(station);
}


// clears the list if it updates 
void Path::clearDijkstraList() 
{
    this->dijkstraList.clear();
}                     

// prints the shortest path given from dijkstra algorithm 
void Path::printDijkstraList() 
{
    for (auto i : dijkstraList)
        std::cout << i << " ";
}                      