#ifndef LOWESTCOST_HPP
#define LOWESTCOST_HPP
#define N 59 
#define taxi_cost_coefficient_traffic 1.5
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>

#include "Time.hpp"
#include "Station.hpp"
#include "Vehicle.hpp"
#include "Path.hpp"
#include "Cost.hpp"
using namespace std;
class LowestCost
{
public:
    LowestCost();
    void fillCostMatrix(std::vector <Station>*, std::vector<Path>*);/* filling adjacency matrix for calculating the best cost path */                             
    void printCostMatrix(std::vector <Station>*);
    void dijkstraOnCost(int,std::string);/* dijkstra implementation for the best cost path and invoks the print function */
    void printDijkstraOnCost(std::vector <Station>*);
    void dijkstra(int source);
    pair<pair<Cost,int>,pair<int,int>>* getParents();
    int * getCostDijkstraList();
    void setArrivingTime(Time);
    Time getArrivingTime();
    int getIndexFromParents(int,int);
    void print_cost(int,vector<Station>*,pair<pair<Cost,int>,pair<int,int>>*); /* prints some basics and printPath and calculateTime functions */
private:

    Time arriving_time;
    pair<pair<Cost,int>,pair<int,int>>* parents;                                                                                                                                                                                                                      
    /*parents.first.second is time 
    parents.second.first is traffic status
    parents.second.second is parent index
    */ 
    vector<pair<Cost,pair<int,int>>> path;
    std::vector<std::vector<Cost>> costMatrix;/* adjacency matrix for cost */   
    int costDijkstraList[N];
};

#endif