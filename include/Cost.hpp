#ifndef COST_HPP
#define COST_HPP

#include <iostream>
#include <vector>
#include <string>

class Cost
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
    void setSubwayCost(unsigned int);
    void setTaxiCost(unsigned int);               
    void setBusCost(unsigned int);
    unsigned int getSubwayCost();
    unsigned int getTaxiCost();               
    unsigned int getBusCost();
    void setBusStatus(bool); 
    void setTaxiStatus(bool);  
    void setSubwayStatus(bool);
    bool getBusStatus();  
    bool getTaxiStatus();  
    bool getSubwayStatus(); 
    void setTrainTaxiDistance(unsigned int);   
    void setBusDistance(unsigned int);            
    unsigned int getTrainTaxiDistance() const;       
    unsigned int getBusDistance() const; 
private:
    std::string firstST="";
    std::string secondST="";
    std::string subway_taxi_line="";
    std::string bus_line="";
    unsigned int subway_cost = 0;
    unsigned int taxi_cost = 0;
    unsigned int bus_cost = 0;
    bool taxi_status = false; //for detecting which vehicle is used               
    bool subway_status = false;                
    bool bus_status = false;   
    unsigned int trainTaxiDistance=0;
    unsigned int busDistance=0;             
};

#endif