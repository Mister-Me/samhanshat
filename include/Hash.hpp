#include <string>
#include <iostream>
#include <cmath>
#include "Station.hpp"
#define N 59
class Hash
{
private:
    Station hashTable[N];
    int maximum_i = 0;
public:
    Hash();
    int hashFunction(Station);
    int returnKey(std::string);
    int getMaximumI();
};

