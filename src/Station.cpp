#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include "../include/Station.hpp"

using namespace std;
void Station::SetName(std::string Name)
{
    this->name = Name;
}
void Station::SetBusStatus(bool Status)
{
    this->bus = Status;
}
void Station::SetTaxi_SubwayStatus(bool Status)
{
    this->taxi_subway = Status;
}
std::string Station::GetName()
{
    return this->name;
}
bool Station::GetBusStatus()
{
    return this->bus;
}
bool Station::GetTaxi_SubwayStatus()
{
    return this->taxi_subway;
}
void Station::Split(string record, char delimeter, vector<Station> *S)
{
    Station temp;
    string parameter;
    vector<string> station;
    for (int i = 0; i < record.size(); i++)
    {
        if(record[i] != delimeter)
        {
            parameter += record[i];
        }
        else
        {
            station.push_back(parameter);
            parameter = "";
        }
    }
    //filling temp station
    temp.name = station[0];
    if (station[1] == "bus")
    {
        temp.bus = true;
    }
    if (station[2] == "taxi")
    {
        temp.taxi_subway = true;
    }
    // push in our Stations vector
    S->push_back(temp); 
}


// finds the index of a specific station in the vector
int Station::findIndex(string station,vector<Station>*S)
{
    for (int i = 0; i < (*S).size(); i++)
        if ((*S)[i].name == station)
            return i;
}


void Station::readFromFile(std::vector <Station>*S,string filename)
{
    try
    {
        ifstream in(filename);
        string text; 
        while(getline(in, text)) 
        {  
            Split(text,'_',S);
        } 
        in.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}