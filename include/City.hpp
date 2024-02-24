#ifndef CITY_HPP
#define CITY_HPP
#define N 59 

#include <string>
#include <vector>
#include <limits.h>
#include <cfloat>
#include "Path.hpp"
#include "Station.hpp"
#include "Cost.hpp"
#include "Time.hpp"
#include "Vehicle.hpp"
#include "Besttime.hpp"
using namespace std;
class City
{
public:
    void FillAdjMatrix(std::vector <Station>*, std::vector<Path>*);
    std::vector<std::vector<Path>> GetAdjMatrix();
    void PrintAdjMatrix(std::vector <Station>*);
    int MinDistance(int distance[], bool sptSet[]);
    int GetShortestDistance(int);
    //parameter is the destination number
    void Dijkstra(int);
    void dijkstraOnTime(int,int,std::vector<Station> *,std::vector<Path>*,Time);
    void Print(std::vector<Station>* ,int,int);
    void PrintAllPaths(std::vector<Station> * ,int);
    void PrintPath(std::vector<Station> *, int, int);
    // void PrintPath(vector <Station>*);
    void setArrivingTime(Time);
    Time getArrivingTime();
    void fillCostMatrix(std::vector <Station>*, std::vector<Cost>*);
    void dijkstraOnCost(int);
private:
    std::vector<std::vector<Path>> adjMatrix;
    std::vector<std::vector<Cost>> costMatrix;
    std::vector<double> dijkstraCost; 
    int dijkstraList[N];
    //dijkstraList[i] will hold the shortest
    //distance from source to each station
    pair<pair<Station,int>,pair<std::string,int>> includedStations[N];
    // first.first is station name 
    // first.second is the distance
    // second.first is the name of line
    // second.second is the number of station's parent 
    Time arriving_time;
};

#endif