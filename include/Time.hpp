#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <exception>
class Time
{
private:
    std::string Hour = "";
    std::string Minute = "";
    std:: string am_pm = "";
public:
    Time(std::string,int,int);
    Time();
    friend Time  operator+(Time const&,int);
    void operator=(Time const&);
    int setHour(int);
    int setMinute(int);
    void setAm_Pm(std::string);
    std::string getHour();
    std::string getMinute();
    std::string getAm_Pm();
    void printTime();
};
#endif