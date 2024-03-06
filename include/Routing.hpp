#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <exception>
#include <fstream>

#include "../include/Station.hpp"
#include "../include/Path.hpp"
#include "../include/City.hpp"
#include "../include/Request.hpp"
#include "../include/Time.hpp"
#include "../include/Cost.hpp"
#include "../include/Vehicle.hpp"
#include "../include/TimedPath.hpp"
#include "../include/Besttime.hpp"
#include "../include/LowestCost.hpp"
#include "../include/Hash.hpp"

class Routing
{
private:
    Hash hash;
public:
    void Split(std::string record, char delimeter , std::vector <Station> *S);
    // split function record is one line from Stations file 
    // delimeter is _
    // S is our station vector
    void readFromFile(std::vector <Station>*,std::string);  // read from a file then split each line
    int findIndex(std::string,std::vector <Station>*);  // finds the index of a specific station in the vector
    void runAlgorithm();
};
