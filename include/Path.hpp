#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <vector>
#include <string>

class Path
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
    void setTrainTaxiDistance(unsigned int);         /* sets the distance between two stations connected by train or taxi */
    void setBusDistance(unsigned int);               /* sets the distance between two stations connected by bus   */
    unsigned int getTrainTaxiDistance() const;       /* returns the distance between two stations connected by train or taxi */
    unsigned int getBusDistance() const;             /* returns the distance between two stations connected by bus   */
    void setDijkstraList(std::string);               /* pushes a station into a list which is used for dijkstra algorithm */ 
    void clearDijkstraList();                        /* clears the list if it updates  */
    void printDijkstraList();     
    void Split(std::string record, char delimeter , std::vector <Path> *P);
    void readFromFile(std::vector <Path>*,std::string);
private:
    std::string firstST="",secondST="";
    std::string subway_taxi_line="";
    std::string bus_line="";
    unsigned int trainTaxiDistance=0;                  /* distance between two stations connected by train */
    unsigned int busDistance=0;                        /* distance between two stations connected by bus   */
    std::vector<std::string> dijkstraList;           /* list for showing the stations after dijkstra algorithm */
};

#endif