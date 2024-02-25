#include <iostream>
#include <fstream>

#include "Cost.hpp"
#include "Station.hpp"

/* =========================================================================== Sets ===========================================================================*/
/* sets the origin of user's path */
void Cost::setOrigin(std::string origin)
{
    this->origin = origin;
}

//-----------------------------------------------------
/* sets the destination of user's path */
void Cost::setDestination(std::string destination)
{
    this->destination = destination;
}

//-----------------------------------------------------
/* sets the vehicle used between two stations */
void Cost::setVehicle(std::string vehicle)
{
    this->vehicle = vehicle;
}

//-----------------------------------------------------
/* sets the line between a single origin and destination */
void Cost::setLine(unsigned int line)
{
    this->line = line;
}                                                                                

//-----------------------------------------------------
/* sets the minimum cost between two stations */
void Cost::setMinimumCost(double cost)
{
    this->minimumCost = cost;
}

/* =========================================================================== Gets ===========================================================================*/
/* returns the origin of user's path */
std::string Cost::getOrigin() const
{
    return (this->origin);
}

//-----------------------------------------------------
/* returns the destination of user's path */
std::string Cost::getDestination() const
{
    return (this->destination);
}

//-----------------------------------------------------
/* returns the vehicle used between two stations */
std::string Cost::getVehicle() const
{
    return (this->vehicle);
}

//-----------------------------------------------------
/* returns the line between a single origin and destination */
unsigned int Cost::getLine() const
{
    return (this->line);
} 

//-----------------------------------------------------
/* returns the minimum cost between two stations */
double Cost::getMinimumCost() const
{
    return (this->minimumCost);
}


/* =========================================================================== General ===========================================================================*/
/* seprates the words from a line of cost file and fill the cost vector */
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
    temp.setLine(stoi(seprate[3]));
    temp.setVehicle(seprate[4]);

    cost->push_back(temp);
}

//-----------------------------------------------------
/* reads a line from file and calls wordSeparator function */
void Cost::readFromFile(std::vector<Cost> *cost, std::string filename)
{
    try
    {
        std::ifstream myfile(filename);
        std::string line = "";

        if (!myfile.is_open() and filename == "cost.txt") {
            throw ("Could not open Cost.txt file");
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