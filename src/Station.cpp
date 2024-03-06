#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include "../include/Station.hpp"

using namespace std;
void Station::SetName(std::string Name)
{
    this->name = Name;
}
void Station::SetBusStatus(bool Status)
{
    this->bus = Status;
}
void Station::SetTaxi_SubwayStatus(bool Status)
{
    this->taxi_subway = Status;
}
std::string Station::GetName()
{
    return this->name;
}
bool Station::GetBusStatus()
{
    return this->bus;
}
bool Station::GetTaxi_SubwayStatus()
{
    return this->taxi_subway;
}





