#include <iostream>
#include <exception>
#include <fstream>

#include "../include/Path.hpp"

using namespace std;
void Path::setFirstST(std::string firstst)
{
    firstST = firstst;
}
void Path::setSecondST(std::string secondst)
{
    secondST = secondst;
}
std::string Path::getFirstST()
{
    return firstST;
}
std::string Path::getSecondST()
{
    return secondST;
}
// sets the distance between two stations connected by train or taxi
void Path::setTrainTaxiDistance(unsigned int distance) 
{
    this->trainTaxiDistance = distance;
}     


// sets the distance between two stations connected by bus 
void Path::setBusDistance(unsigned int distance) 
{
    this->busDistance = distance;
}  


// returns the distance between two stations connected by train ot taxi
unsigned int Path::getTrainTaxiDistance() const 
{
    return (this->trainTaxiDistance);
}


// returns the distance between two stations connected by bus 
unsigned int Path::getBusDistance() const 
{
    return (this->busDistance);
}    

// pushes a station into a list which is used for dijkstra algorithm 
void Path::setDijkstraList(std::string station) 
{
    this->dijkstraList.push_back(station);
}


// clears the list if it updates 
void Path::clearDijkstraList() 
{
    this->dijkstraList.clear();
}                     

// prints the shortest path given from dijkstra algorithm 
void Path::printDijkstraList() 
{
    for (auto i : dijkstraList)
        std::cout << i << " ";
}
void Path::Split(std::string record, char delimeter, std::vector<Path> *P)
{
    Path temp;
    string parameter;
    vector<string> parameters;
    for (int i = 0; i < record.size(); i++)
    {
        if(record[i] != delimeter)
        {
            parameter += record[i];
        }
        else
        {
            parameters.push_back(parameter);
            parameter = "";
        }
    }
    //filling temp path
    temp.setFirstST(parameters[0]);
    temp.setSecondST(parameters[1]);
    temp.setTrainTaxiDistance(stoi(parameters[2]));
    temp.setBusDistance(stoi(parameters[3]));

    P->push_back(temp); 
}

void Path::readFromFile(std::vector <Path>*P,string filename)
{
    try
    {
        ifstream in(filename);
        string text; 
        while(getline(in, text)) 
        {  
            Split(text,'_',P);
        } 
        in.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}