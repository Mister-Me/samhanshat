#include <iostream>
#include <string>
#include <vector>

#include "../include/Station.hpp"
#include "../include/Path.hpp"
#include "../include/City.hpp"
using namespace std;

int main()
{
    vector <Station>* stations = new vector <Station>;
    vector <Path>* path = new vector <Path>;
    Station st;
    Path p;
    st.readFromFile(stations,"../file/Stations.txt");
    p.readFromFile(path,"../file/Distance.txt");
    City Tehran;
    Tehran.FillAdjMatrix(stations,path);
    Tehran.PrintAdjMatrix(stations);
    return 0;
}