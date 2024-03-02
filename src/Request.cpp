#include <iostream>
#include <vector>
#include <string>
#include "../include/Request.hpp"

using namespace std;
void Request::SetTime(std::string Time)
{
    std::vector<std::string> params = Split(Time,' ');
    std::vector<std::string> numbers = Split(params[0],':');
    time.setAm_Pm(params[1]);
    if(time.setHour(stoi(numbers[0])) == -1 || time.setMinute(stoi(numbers[1])) == -1)
    {
        std:: cout << "input is invalid";
    }
}
void Request::SetOrigin(std::string Origin)
{
    this->origin = Origin;
}
void Request::SetDestination(std::string Destination)
{
    this->destination = Destination;
}
Time Request::GetTime()
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
std::vector<std::string> Request::Split(string Time, char delimeter)
{
    std::vector<std::string> parameters;
    std::string parameter="";
    for (int i = 0; i < Time.size(); i++)
    {
        if(Time[i] != delimeter)
        {
            parameter += Time[i];
        }
        else
        {
            parameters.push_back(parameter);
            parameter = "";
        }
    }
    parameters.push_back(parameter);
    return parameters;
}