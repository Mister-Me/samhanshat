#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>

class Request
{
public:
    void SetTime(std::string Time);
    void SetOrigin(std::string Origin);
    void SetDestination(std::string Destination);
    std::string GetTime();
    std::string GetOrigin();
    std::string GetDestination();
    std::string  Split(std::string Time, char delimeter);
    // split function for separating am and pm  
    // delimeter is white space

private:
    std::string time = "";
    std::string origin = "";
    std::string destination = "";
};

#endif