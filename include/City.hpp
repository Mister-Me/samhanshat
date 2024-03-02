#ifndef CITY_HPP
#define CITY_HPP
#define N 59 
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
    void dijkstraOnTime(int,int,std::vector<Station> *,std::vector<Path>*,Time);
    void Print(std::vector<Station>* ,int,int);
    void PrintAllPaths(std::vector<Station> * ,int);
    void PrintPath(std::vector<Station> *, int, int);
    void setArrivingTime(Time);
    Time getArrivingTime();

/*===================================================== Cost =====================================================*/
                                                                        
    void fillCostMatrix(std::vector <Station>*, std::vector<Path>*);                                    /* filling adjacency matrix for calculating the best cost path */                             
    void printCostMatrix(std::vector <Station>*);
    void dijkstraOnCost(int);                                                         /* dijkstra implementation for the best cost path and invoks the print function */
    void printDijkstraOnCost(std::vector <Station>*);
    void printPath(int,int);                                                                            /* prints only the path from source to destination */
    void print_cost(int,int,vector<Station>*);                                                               /* prints some basics and printPath and calculateTime functions */
    void print_path_cost(std::vector<Station> *, int, int);
    void calculateTime();                                                                               /* calculates the arriving time when user reach destination */
    int findDistance(vector<Path>*,string,string);                                                      /* finds the distance between to stations in vector path */

/*===================================================== Time =====================================================*/

private:
    std::vector<std::vector<Path>> adjMatrix;                                                           /* adjacency matrix for distance */
    std::vector<std::vector<Cost>> costMatrix;                                                          /* adjacency matrix for cost */   
    int costDijkstraList[N];
    int dijkstraList[N];                                                                             /* dijkstraList[i] will hold the shortest distance/cost form source to i */                           
    Time arriving_time;                                                                                 /* the time when user reach the destination */
    pair<pair<Cost,int>,pair<int,int>> parents[N];                                                                 /* first is object of cost class, second.first is distance, second.second is parent number */                                                                                                                                                      
    // parents.first.second is time
    vector<pair<Cost,pair<int,int>>> path;
    pair<pair<Station,int>,pair<std::string,int>> includedStations[N];                                  /* distance from source to each station. first.first is station name first.second is the distance,
                                                                                                           second.first is the name of line, second.second is the number of station's parent. */   
}; 

#endif