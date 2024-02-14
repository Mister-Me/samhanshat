
#include "../include/Time.hpp"


int Time::setHour(int hour)
{
    if(hour > 12 || hour < 0)
    {
        return -1;
    }
    if (am_pm == "am")
    {
        Hour = std::to_string(hour);
    }
    else if (am_pm == "pm")
    {
        hour = hour + 12;
        if(hour == 24)
        {
            hour = 0;
        }
        Hour = std::to_string(hour); 
    }
    return 1;
}
int Time::setMinute(int minute)
{
    if(minute > 59 || minute < 0)
    {
        return -1;
    }
    Minute = std::to_string(minute);
    return 1;
}
void Time::setAm_Pm(std::string str)
{
    if(str == "am" || str == "pm")
    {
        am_pm = str;
    }
    else if(str != "none")
    {
        std::cout << "input is invalid use am or pm" << '\n';
    }
}

Time::Time(std::string am_pm, int hour, int minute)
{
    this->setAm_Pm(am_pm);
    try
    {
        if(this->setHour(hour) == -1)
        {
           throw  std::invalid_argument("input is invalid");
        }
        if (this->setMinute(minute) == -1)
        {
            throw  std::invalid_argument("input is invalid");
        }  
    }
    catch(const std::exception& e)
    {
        Hour = "00";
        Minute = "00";
        std::cerr << e.what() << '\n';
    }
    
}
std::string Time::getHour()
{
    return Hour;
}

void Time::operator=(Time const & t)
{
    this->am_pm = t.am_pm;
    this->Hour = t.Hour; //because setHour return -1 if hour is greater than 12 i don't use setHour function
    this->setMinute(stoi(t.Minute));
}
std::string Time::getMinute()
{
    return Minute;
}
std::string Time::getAm_Pm()
{
    return am_pm;
}
// give the value of added time in minute
Time operator+(Time const &t1, int minute)
{
    int hour = std::stoi(t1.Hour);
    while (minute >= 60)
    {
        hour++;
        minute -= 60;
    }
    int min = std::stoi(t1.Minute);
    min += minute;
    while( min >= 60)
    {
        hour ++;
        min -= 60 ;
    }
    while (hour >= 24)
    {
        hour = hour - 24;
    }
    Time temp;
    temp.Hour = std::to_string(hour);
    temp.Minute = std::to_string(min);
    temp.am_pm = "none";
    return(temp);
}
void Time::printTime()
{
    std::cout << std::setfill('0') << std::setw(2) << Hour << ":" << std::setw(2) << Minute << '\n';
}
Time::Time()
{

}