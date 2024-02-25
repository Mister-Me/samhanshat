#include "../include/PricedPath.hpp"

    void PricedPath::setFirstST(std::string firstst)
    {   
        firstST = firstst;
    }
    void PricedPath::setSecondST(std::string secondst)
    {
        secondST = secondst;
    }
    std::string PricedPath::getFirstST()
    {
        return firstST;
    }
    std::string PricedPath::getSecondST()
    {
        return secondST;
    }
    void PricedPath::setSubway_Taxi_Line(std::string line)
    {
        subway_taxi_line = line;
    }
    void PricedPath::setBus_Line(std::string line)
    {
        bus_line = line;
    }
    std::string PricedPath::getSubway_Taxi_Line()
    {
        return subway_taxi_line;
    }
    std::string PricedPath::getBus_Line()
    {
        return bus_line;
    }
    void PricedPath::setSubwayCost(unsigned int cost)
    {
        subway_cost = cost;
    }
    void PricedPath::setTaxiCost(unsigned int cost)
    {
        taxi_cost = cost;
    }               
    void PricedPath::setBusCost(unsigned int cost)
    {
        bus_cost = cost;
    }
    unsigned int PricedPath::getSubwayCost()
    {
        return subway_cost;
    }
    unsigned int PricedPath::getTaxiCost()
    {
        return taxi_cost;
    }          
    unsigned int PricedPath::getBusCost()
    {
        return bus_cost;
    } 
    void PricedPath::setBusStatus(bool status)
    {
        bus_status = status;
    } 
    void PricedPath::setTaxiStatus(bool status)
    {
        taxi_status = status;
    }
    void PricedPath::setSubwayStatus(bool status)
    {
        subway_status = status;
    }
    bool PricedPath::getBusStatus()
    {
        return bus_status;
    } 
    bool PricedPath::getTaxiStatus()
    {
        return taxi_status;
    }
    bool PricedPath::getSubwayStatus()
    {
        return subway_status;
    }