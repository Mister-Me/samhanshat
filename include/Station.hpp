#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <vector>

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

    
    void readFromFile(std::vector <Station>*,std::string);  // read from a file then split each line
    
    int findIndex(std::string,std::vector <Station>*);  // finds the index of a specific station in the vector
private:
    std::string name = "";
    bool bus = false;
    bool taxi_subway = false;
};

#endif