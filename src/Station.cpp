#include <iostream>
#include <fstream>
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


// finds the index of a specific station in the vector
int Station::findIndex(string station,vector<Station>*S)
{
    for (int i = 0; i < (*S).size(); i++)
        if ((*S)[i].name == station)
            return i;
}


// seprates line by delimeter which is '_' and starts to fill the adjacency matrix
void Station::fillMatrix(string line,std::vector <Station>*S)
{
    string split = ""; Path temp;
    vector<string> stations;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != '_')
            split += line[i];
        else
            stations.push_back(split), split = "";
    }

    // stations[2] is trainTaxiDistance in path class
    temp.setTrainTaxiDistance(stoi(stations[2]));
    //  stations[3] is busDistance in path class
    temp.setBusDistance(stoi(stations[3]));

    // index of the start station
    int start = findIndex(stations[0],S);
    // index of the destination
    int end   = findIndex(stations[1],S);
    
    Matrix[start][end] = temp;
    Matrix[end][start] = temp;
}


// reads a single line from a file and then call function fillMatrix
void Station::readFromFile(std::vector <Station>*S)
{
    string line = ""; ifstream myfile;
    myfile.open("Distance.txt");

    while (getline(myfile,line))
        fillMatrix(line,S);
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