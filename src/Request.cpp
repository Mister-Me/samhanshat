#include <iostream>
#include <vector>
#include <string>
#include "../include/Request.hpp"

using namespace std;
void Request::SetTime(std::string Time)
{
    this->time = Time;
}
void Request::SetOrigin(std::string Origin)
{
    this->origin = Origin;
}
void Request::SetDestination(std::string Destination)
{
    this->destination = Destination;
}
std::string Request::GetTime()
{
    return this->time;
}
std::string Request::GetOrigin()
{
    return this->origin;
}
std::string Request::GetDestination()
{
    return this->destination;
}
std::string Request::Split(string Time, char delimeter)
{
    string parameter="";
    for (int i = 0; i < Time.size(); i++)
    {
        if(Time[i] != delimeter)
        {
            parameter += Time[i];
        }
        else
        {
            parameter = "";
        }
    }
    return parameter;
}