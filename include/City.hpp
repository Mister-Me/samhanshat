#ifndef CITY_HPP
#define CITY_HPP
#define N 59

#include <string>
#include <vector>
#include <limits.h>

#include "Path.hpp"
#include "Station.hpp"
using namespace std;
class City
{
public:
    void FillAdjMatrix(vector <Station>*,vector <Path>*);
    vector < vector<Path> > GetAdjMatrix();
    void PrintAdjMatrix(vector <Station>*);
    int MinDistance(int distance[],bool sptSet[]);
    void Dijkstra(int);
    void PrintPath(vector <Station>*);
private:
    vector < vector<Path> > adjMatrix;
    int dijkstraList[N]; 
    //dijkstraList[i] will hold the shortest
    // distance from source to each station
};

#endif