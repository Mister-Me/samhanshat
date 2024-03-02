#include "../include/Cost.hpp"

void Cost::setFirstST(std::string firstst)
{   
    firstST = firstst;
}
void Cost::setSecondST(std::string secondst)
{
    secondST = secondst;
}
std::string Cost::getFirstST()
{
    return firstST;
}
std::string Cost::getSecondST()
{
    return secondST;
}
void Cost::setSubway_Taxi_Line(std::string line)
{
    subway_taxi_line = line;
}
void Cost::setBus_Line(std::string line)
{
    bus_line = line;
}
std::string Cost::getSubway_Taxi_Line()
{
    return subway_taxi_line;
}
std::string Cost::getBus_Line()
{
    return bus_line;
}
void Cost::setSubwayCost(unsigned int cost)
{
    subway_cost = cost;
}
void Cost::setTaxiCost(unsigned int cost)
{
    taxi_cost = cost;
}               
void Cost::setBusCost(unsigned int cost)
{
    bus_cost = cost;
}
unsigned int Cost::getSubwayCost()
{
    return subway_cost;
}
unsigned int Cost::getTaxiCost()
{
    return taxi_cost;
}          
unsigned int Cost::getBusCost()
{
    return bus_cost;
} 
void Cost::setBusStatus(bool status)
{
    bus_status = status;
} 
void Cost::setTaxiStatus(bool status)
{
    taxi_status = status;
}
void Cost::setSubwayStatus(bool status)
{
    subway_status = status;
}
bool Cost::getBusStatus()
{
    return bus_status;
} 
bool Cost::getTaxiStatus()
{
    return taxi_status;
}
bool Cost::getSubwayStatus()
{
    return subway_status;
}
void Cost::setTrainTaxiDistance(unsigned int distance) 
{
    this->trainTaxiDistance = distance;
}     

void Cost::setBusDistance(unsigned int distance) 
{
    this->busDistance = distance;
}  
unsigned int Cost::getTrainTaxiDistance() const 
{
    return (this->trainTaxiDistance);
} 
unsigned int Cost::getBusDistance() const 
{
    return (this->busDistance);
}  