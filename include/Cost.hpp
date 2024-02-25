#ifndef COST_HPP
#define COST_HPP

#include <iostream>
#include <vector>
#include "Station.hpp"

class Cost
{
public:
/* ====================================================================== Sets ======================================================================*/

    void setOrigin(std::string);                                                                                    /* sets the origin of user's path */
    void setDestination(std::string);                                                                               /* sets the destination of user's path */
    void setVehicle(std::string);                                                                                   /* sets the vehicle used between two stations */
    void setLine(unsigned int);                                                                                     /* sets the line between a single origin and destination */
    void setMinimumCost(double);                                                                                    /* sets the minimum cost between two stations */

/* ====================================================================== Gets ======================================================================*/

    std::string getOrigin() const;                                                                                  /* returns the origin of user's path */
    std::string getDestination() const;                                                                             /* returns the destination of user's path */
    std::string getVehicle() const;                                                                                 /* returns the vehicle used between two stations */
    unsigned int getLine() const;                                                                                   /* returns the line between a single origin and destination */
    double getMinimumCost() const;                                                                                  /* returns the minimum cost between two stations */

/* ===================================================================== General ====================================================================*/

    void readFromFile(std::vector<Cost> *, std::string);                                                            /* reads a line from file and calls wordSeparator function */
    void wordSeparator(std::string, char, std::vector<Cost> *);                                                     /* seprates the words from a line of cost file and fill the cost vector */

private:
    std::string origin = "";                                                                                        /* the origin of user's path */
    std::string destination = "";                                                                                   /* the destination of user's path */                                                                 
    std::string vehicle = "";                                                                                       /* the vehicle used between two stations */
    unsigned int line = 0;                                                                                          /* the line between a single origin and destination */
    double minimumCost = 0.0;                                                                                       /* the minimum cost between two stations  */
};

#endif