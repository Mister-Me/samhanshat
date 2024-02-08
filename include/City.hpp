#ifndef CITY_HPP
#define CITY_HPP

#include <string>
#include <vector>
 
#include "Path.hpp"
#include "Station.hpp"
using namespace std;
class City
{
public:
    void FillAdjMatrix(vector <Station>*,vector <Path>*);
    vector < vector<Path> > GetAdjMatrix();
    void PrintAdjMatrix(vector <Station>*);

private:
    vector < vector<Path> > adjMatrix;
};

#endif