#ifndef BESTTIME_HPP
#define BESTTIME_HPP
#define N 59
#define subway_time_coefficient_traffic 1
#define taxi_time_coefficient_traffic 2
#define bus_time_coefficient_traffic 2

#include <limits.h>

#include "Time.hpp"
#include "TimedPath.hpp"
#include "Station.hpp"
#include "Vehicle.hpp"
#include "Path.hpp"
using namespace std;
class Besttime
{
public:
    Besttime();
    ~Besttime();
    void Dijkstra(int source);
    void FillAdjMatrix(std::vector <Station>*,std::vector<Path>*);
    void PrintAdjMatrix(std::vector <Station>*);
    void Dijkstra(int,string);
    void printDijkstra(std::vector <Station>*);
    void Print(std::vector<Station>* ,int,pair<pair<TimedPath,int>,pair<bool,int>>*);
    void PrintPath(std::vector<Station> *, int, int);
    int* getDijkstraList ();
    void setArrivingTime(Time);
    Time getArrivingTime();
    pair<pair<TimedPath,int>,pair<bool,int>> * getParents();
    int getIndexFromParents(int,int);
private:
    std::vector<std::vector<TimedPath>> adjMatrix;
    int dijkstraList[N];
    pair<pair<TimedPath,int>,pair<bool,int>>* parents;
    Time arriving_time;
};

#endif