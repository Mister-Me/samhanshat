#ifndef COST_HPP
#define COST_HPP

#include <iostream>
#include <vector>

class Cost
{
public:
    void setOrigin(std::string);
    void setDestination(std::string);
    void setMinimumCost(double);
    std::string getOrigin() const;
    std::string getDestination() const;
    double getMinimumCost() const;
    void wordSeparator(std::string, char, std::vector<Cost> *);
    void readFromFile(std::vector<Cost> *, std::string);
private:
    std::string origin = "";
    std::string destination = "";
    double minimumCost = 0.0;
};

#endif