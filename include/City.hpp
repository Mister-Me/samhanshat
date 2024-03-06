#ifndef CITY_HPP
#define CITY_HPP
#define N 59 
#define taxi_cost_coefficient_traffic 1.5
#define taxi_cost_coefficient_traffic 1.5
#include <string>
#include <vector>
#include <limits.h>
#include <cfloat>
#include "Path.hpp"
#include "Station.hpp"
#include "LowestCost.hpp"
#include "Time.hpp"
#include "Vehicle.hpp"
#include "Besttime.hpp"
#include "Cost.hpp"
using namespace std;

class City
{
public:
    /*=================================================== Distance ===================================================*/

    void FillAdjMatrix(std::vector <Station>*, std::vector<Path>*);                                     /* filling adjacency matrix for calculating the best distance path */  
    std::vector<std::vector<Path>> GetAdjMatrix();                                                      /* returns the distance adjacency matrix */
    void PrintAdjMatrix(std::vector <Station>*);                                                        /* prints the distance adjacency matrix */
    int MinDistance(int distance[], bool sptSet[]);
    int GetShortestDistance(int);
    void Dijkstra(int);
    void Print(std::vector<Station>* ,int,int);
    void PrintAllPaths(std::vector<Station> * ,int);
    void PrintPath(std::vector<Station> *, int, int);
    void setArrivingTime(Time);
    Time getArrivingTime();
    /*=================================================== Cost ===================================================*/
    void Dijkstra_FloydWarshall(int,int,std::vector <Station>*,std::vector<Path>*,Time);
    /*=================================================== Time ===================================================*/
    void dijkstraOnTime(int,int,std::vector<Station> *,std::vector<Path>*,Time);
private:
    std::vector<std::vector<Path>> adjMatrix;/* adjacency matrix for distance */
    int dijkstraList[N];/* dijkstraList[i] will hold the shortest distance/cost form source to i */                           
    Time arriving_time;/* the time when user reach the destination */
    pair<pair<Station,int>,pair<std::string,int>> includedStations[N]; 
    /*first.first is station name first.second is the distance,
    second.first is the name of line, second.second is the number of station's parent. */   
}; 

#endif