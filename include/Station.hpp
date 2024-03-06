#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <vector>
#include <exception>

class Station
{
public:
    void SetName(std::string Name);
    void SetBusStatus(bool Status);
    void SetTaxi_SubwayStatus(bool Status);
    std::string GetName();
    bool GetBusStatus();
    bool GetTaxi_SubwayStatus();
private:
    std::string name = "";
    bool bus = false;
    bool taxi_subway = false;
};

#endif