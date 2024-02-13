#include <iostream>
#include <fstream>

#include "../include/Cost.hpp"

void Cost::setOrigin(std::string origin)
{
    this->origin = origin;
}


void Cost::setDestination(std::string destination)
{
    this->destination = destination;
}


void Cost::setMinimumCost(double cost)
{
    this->minimumCost = cost;
}


std::string Cost::getOrigin() const
{
    return (this->origin);
}


std::string Cost::getDestination() const
{
    return (this->destination);
}


double Cost::getMinimumCost() const
{
    return (this->minimumCost);
}

void Cost::wordSeparator(std::string line, char delimeter, std::vector<Cost> *cost)
{
    std::vector<std::string> seprate; 
    std::string word = ""; Cost temp;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != delimeter)
            word += line[i];
        else 
            seprate.push_back(word), word = "";
    }

    temp.setOrigin(seprate[0]);
    temp.setDestination(seprate[1]);
    temp.setMinimumCost(stod(seprate[2]));

    cost->push_back(temp);
}


void Cost::readFromFile(std::vector<Cost> *cost, std::string filename)
{
    try
    {
        std::ifstream myfile(filename);
        std::string line = "";

        if (!myfile.is_open() and filename == "cost.txt") {
            throw ("Could not open Cost.txt file");
        } 
        if (!myfile.is_open() and filename == "costByTime.txt") {
            throw ("Could not open costByTime.txt file");
        } 
        while (getline(myfile, line)) {
            wordSeparator(line,'_',cost);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}