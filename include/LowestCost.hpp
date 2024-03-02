#ifndef LOWESTCOST_HPP
#define LOWESTCOST_HPP
#define N 59
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

#include "Time.hpp"
#include "PricedPath.hpp"
#include "Station.hpp"
#include "Vehicle.hpp"
#include "Path.hpp"
using namespace std;
class LowestCost
{
public:
    void FillAdjMatrix(std::vector <Station>*,std::vector<Path>*);
    void PrintAdjMatrix(std::vector <Station>*);
    void Dijkstra(int,string);
    void printDijkstra(std::vector <Station>*);
    void Print(std::vector<Station>* ,int,int);
    void PrintPath(std::vector<Station> *, int, int);
    int* getDijkstraList ();
    void setArrivingTime(Time);
    Time getArrivingTime();
    pair<pair<PricedPath,int>,pair<bool,int>> * getParents();
private:
    std::vector<std::vector<PricedPath>> adjMatrix;
    int dijkstraList[N];
    pair<pair<PricedPath,int>,pair<bool,int>> parents[N];
    Time arriving_time;
};

#endif