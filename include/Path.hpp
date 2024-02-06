#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <vector>

class Path
{
public:
    void setTrainDistance(unsigned int);             /* sets the distance between two stations connected by train */
    void setTaxiDistance(unsigned int);              /* sets the distance between two stations connected by taxi  */
    void setBusDistance(unsigned int);               /* sets the distance between two stations connected by bus   */
    unsigned int getTrainDistance() const;           /* returns the distance between two stations connected by train */
    unsigned int getTaxiDistance() const;            /* returns the distance between two stations connected by taxi  */
    unsigned int getBusDistance() const;             /* returns the distance between two stations connected by bus   */
    void setDijkstraList(std::string);               /* pushes a station into a list which is used for dijkstra algorithm */ 
    void clearDijkstraList();                        /* clears the list if it updates  */
    void printDijkstraList();                        /* prints the shortest path given from dijkstra algorithm  */
private:
    unsigned int trainDistance;                      /* distance between two stations connected by train */
    unsigned int taxiDistance;                       /* distance between two stations connected by taxi  */
    unsigned int busDistance;                        /* distance between two stations connected by bus   */
    std::vector<std::string> dijkstraList;           /* list for showing the stations after dijkstra algorithm */
};

#endif