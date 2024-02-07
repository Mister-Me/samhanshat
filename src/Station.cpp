#include <iostream>
#include <vector>
#include <string>
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
// int main()
// {
    //our Main vector for stations

    // vector<Station>* Stations = new vector<Station>;

    //examples for using function
    // split("Shahid Rezaei_bus_taxi_",'_',Station);
    // split("Shahid Haghani__taxi_",'_',Station);
    //Outputs
    // for (auto &&i : *Station)
    // {
    //     cout<< i.name << " " << i.bus << " " << i.taxi_subway << '\n';
    // }
    // return 0;
// }