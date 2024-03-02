#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "../include/Station.hpp"
#include "../include/Path.hpp"
#include "../include/City.hpp"
#include "../include/Request.hpp"
#include "../include/Time.hpp"
#include "../include/Cost.hpp"
#include "../include/Vehicle.hpp"
#include "../include/TimedPath.hpp"
#include "../include/Besttime.hpp"
#include "../include/LowestCost.hpp"
using namespace std;

int main()
{
    vector <Station>* stations = new vector <Station>;
    vector <Path>* path = new vector <Path>;
    vector<Cost> *cost = new vector <Cost>;
    Station st;
    Path p;
    Cost c;
    Besttime bestTime;
    LowestCost lowestCost;
    st.readFromFile(stations,"../file/Stations.txt");
    p.readFromFile(path,"../file/Distance.txt");
    //lowestCost.FillAdjMatrix(stations,path);
    //lowestCost.PrintAdjMatrix(stations);
    //bestTime.FillAdjMatrix(stations,path);
    // bestTime.Dijkstra(17,"subway");
    // bestTime.printDijkstra(stations);
    City Tehran;
    City Map;
    Tehran.FillAdjMatrix(stations,path);
    //Tehran.fillCostMatrix(stations,path);
    //Tehran.printCostMatrix(stations);
    // Map.fillCostMatrix(stations,cost);
    int NumberOfOrders = 0;
    queue<Request> requests;
    cout << "Please Enter Number of orders : " << '\n';
    cin >> NumberOfOrders;
    for (int i = 0; i < NumberOfOrders; i++)
    {
        Request R;
        string time , origin , destination;
        getline(cin>>ws,time);
        getline(cin>>ws,origin);
        getline(cin>>ws,destination);
        R.SetTime(time);
        R.SetOrigin(origin);
        R.SetDestination(destination);
        requests.push(R);
    }
    while (!requests.empty())
    {
        int origin = st.findIndex(requests.front().GetOrigin(),stations);
        int destination= st.findIndex(requests.front().GetDestination(),stations);
        if(origin != -1 && destination != -1)
        {
            if(origin == destination)
            {
                cout <<'\n'<< "Distance : 0 " << '\n';
            }
            else
            {
                Tehran.setArrivingTime(requests.front().GetTime());
                Map.setArrivingTime(requests.front().GetTime());
                Tehran.Dijkstra(origin);
                Tehran.PrintPath(stations,origin,destination);
                // Tehran.dijkstraOnCost(origin);
                // Tehran.print_path_cost(stations,origin,destination);

                // LowestCost l;
                // l.fillCostMatrix(stations,path);
                // l.setArrivingTime(requests.front().GetTime());
                // l.dijkstra(2);
                // l.dijkstraOnCost(2,"subway");
                // l.printDijkstraOnCost(stations);
                // cout << l.getParents()[destination].first.second << endl
                // <<l.getParents()[destination].second.second << endl;
                // Tehran.printDijkstraOnCost(stations);
                //Map.setArrivingTime(requests.front().GetTime());
                //Map.dijkstraOnCost(origin,destination,path);
                
                // Tehran.Dijkstra_FloydWarshall(origin,destination,stations,path,requests.front().GetTime());
                Map.Dijkstra_FloydWarshall(origin,destination,stations,path,requests.front().GetTime());
                Tehran.dijkstraOnTime(origin,destination,stations,path,requests.front().GetTime());
            }
        }
        else
        {
            cout << "Station does not exist !" << '\n';
        }
        requests.pop();     
    }
    return 0;
}