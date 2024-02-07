#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <vector>
#include "Path.hpp"

class Station
{
public:
    void SetName(std::string Name);
    void SetBusStatus(bool Status);
    void SetTaxi_SubwayStatus(bool Status);
    std::string GetName();
    bool GetBusStatus();
    bool GetTaxi_SubwayStatus();
    void Split(std::string record, char delimeter , std::vector <Station> *S);
    // split function record is one line from Stations file 
    // delimeter is _
    // S is our station vector

    // reads a single line from a file and then call function fillMatrix
    void readFromFile(std::vector <Station>*);
    // seprates line by delimeter which is '_' and starts to fill the adjacency matrix
    void fillMatrix(std::string,std::vector <Station>*);
    // finds the index of a specific station in the vector
    int findIndex(std::string,std::vector <Station>*);
private:
    std::string name = "";
    bool bus = false;
    bool taxi_subway = false;
    Path Matrix[59][59];
};

#endif