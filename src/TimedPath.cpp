#include "../include/TimedPath.hpp"

    void TimedPath::setFirstST(std::string firstst)
    {   
        firstST = firstst;
    }
    void TimedPath::setSecondST(std::string secondst)
    {
        secondST = secondst;
    }
    std::string TimedPath::getFirstST()
    {
        return firstST;
    }
    std::string TimedPath::getSecondST()
    {
        return secondST;
    }
    void TimedPath::setSubway_Taxi_Line(std::string line)
    {
        subway_taxi_line = line;
    }
    void TimedPath::setBus_Line(std::string line)
    {
        bus_line = line;
    }
    std::string TimedPath::getSubway_Taxi_Line()
    {
        return subway_taxi_line;
    }
    std::string TimedPath::getBus_Line()
    {
        return bus_line;
    }
    void TimedPath::setSubwayTime(unsigned int min)
    {
        subway_time = min;
    }
    void TimedPath::setTaxiTime(unsigned int min)
    {
        taxi_time = min;
    }               
    void TimedPath::setBusTime(unsigned int min)
    {
        bus_time = min;
    }
    unsigned int TimedPath::getSubwayTime()
    {
        return subway_time;
    }
    unsigned int TimedPath::getTaxiTime()
    {
        return taxi_time;
    }          
    unsigned int TimedPath::getBusTime()
    {
        return bus_time;
    } 
    void TimedPath::setBusStatus(bool status)
    {
        bus_status = status;
    } 
    void TimedPath::setTaxiStatus(bool status)
    {
        taxi_status = status;
    }
    void TimedPath::setSubwayStatus(bool status)
    {
        subway_status = status;
    }
    bool TimedPath::getBusStatus()
    {
        return bus_status;
    } 
    bool TimedPath::getTaxiStatus()
    {
        return taxi_status;
    }
    bool TimedPath::getSubwayStatus()
    {
        return subway_status;
    }