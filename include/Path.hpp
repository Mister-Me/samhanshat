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
private:
    unsigned int trainDistance;                      /* distance between two stations connected by train */
    unsigned int taxiDistance;                       /* distance between two stations connected by taxi  */
    unsigned int busDistance;                        /* distance between two stations connected by bus   */
    std::vector<std::string> dijkstraList;           /* list for showing the stations after dijkstra algorithm */
};

#endif