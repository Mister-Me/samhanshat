#ifndef TIMEDPATH_HPP
#define TIMEDPATH_HPP

#include <iostream>
#include <vector>
#include <string>

class TimedPath
{
public:
    void setFirstST(std::string firstst);
    void setSecondST(std::string secondst);
    std::string getFirstST();
    std::string getSecondST();
    void setSubway_Taxi_Line(std::string);
    void setBus_Line(std::string);
    std::string getSubway_Taxi_Line();
    std::string getBus_Line();
    void setSubwayTime(unsigned int);
    void setTaxiTime(unsigned int);               
    void setBusTime(unsigned int);
    unsigned int getSubwayTime();
    unsigned int getTaxiTime();               
    unsigned int getBusTime();
    void setBusStatus(bool); 
    void setTaxiStatus(bool);  
    void setSubwayStatus(bool);
    bool getBusStatus();  
    bool getTaxiStatus();  
    bool getSubwayStatus();  
private:
    std::string firstST="";
    std::string secondST="";
    std::string subway_taxi_line="";
    std::string bus_line="";
    unsigned int subway_time = 0;//minute per km
    unsigned int taxi_time = 0;//minute per km
    unsigned int bus_time = 0;//minute per km
    bool taxi_status = false; //for detecting which vehicle is used               
    bool subway_status = false;                
    bool bus_status = false;                
};

#endif