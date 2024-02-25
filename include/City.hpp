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
    void Print(std::vector<Station>* ,int);
    void PrintAllPaths(std::vector<Station> * ,int);
    void PrintPath(std::vector<Station> *, int, int);
    void setArrivingTime(Time);
    Time getArrivingTime();

/*===================================================== Cost =====================================================*/
                                                                        
    void fillCostMatrix(std::vector <Station>*, std::vector<Cost>*);                                    /* filling adjacency matrix for calculating the best cost path */                             
    void dijkstraOnCost(int,int,vector<Path>*);                                                         /* dijkstra implementation for the best cost path and invoks the print function */
    void printPath(int,int);                                                                            /* prints only the path from source to destination */
    void print(int,int);                                                                                /* prints some basics and printPath and calculateTime functions */
    void calculateTime();                                                                               /* calculates the arriving time when user reach destination */
    int findDistance(vector<Path>*,string,string);                                                      /* finds the distance between to stations in vector path */

/*===================================================== Time =====================================================*/

private:
    std::vector<std::vector<Path>> adjMatrix;                                                           /* adjacency matrix for distance */
    std::vector<std::vector<Cost>> costMatrix;                                                          /* adjacency matrix for cost */   
    double dijkstraList[N];                                                                             /* dijkstraList[i] will hold the shortest distance/cost form source to i */                           
    Time arriving_time;                                                                                 /* the time when user reach the destination */
    pair<Cost,pair<int,int>> parent[N];                                                                 /* first is object of cost class, second.first is distance, second.second is parent number */                                                                                                                                                      
    vector<pair<Cost,pair<int,int>>> path;
    pair<pair<Station,int>,pair<std::string,int>> includedStations[N];                                  /* distance from source to each station. first.first is station name first.second is the distance,
                                                                                                           second.first is the name of line, second.second is the number of station's parent. */   
}; 

#endif