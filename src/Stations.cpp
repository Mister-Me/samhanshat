#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Station
{
private:
public:
    std::string name = "";
    bool bus = false;
    bool taxi_subway = false;    /* list for showing the stations after dijkstra algorithm */
};
// split function record is one line from Stations file 
// delimeter is _
// S is our station vector
void split (string record, char delimeter , vector<Station> *S)
{
    Station temp;
    string parameter;
    vector<string> station;
    for (int i = 0; i < record.size(); i++)
    {
        if(record[i] != delimeter)
        {
            parameter += record[i];
        }
        else
        {
            station.push_back(parameter);
            parameter = "";
        }
    }
    //filling temp station
    temp.name = station[0];
    if (station[1] == "bus")
    {
        temp.bus = true;
    }
    if (station[2] == "taxi")
    {
        temp.taxi_subway = true;
    }
    // push in our Stations vector
    S->push_back(temp); 
}
int main()
{
    //our Main vector for stations

    vector<Station>* Stations = new vector<Station>;

    //examples for using function
    split("Shahid Rezaei_bus_taxi_",'_',Stations);
    split("Shahid Haghani__taxi_",'_',Stations);
    
    //Outputs
    for (auto &&i : *Stations)
    {
        cout<< i.name << " " << i.bus << " " << i.taxi_subway << '\n';
    }
    return 0;
}