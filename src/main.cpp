#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "../include/Station.hpp"
#include "../include/Path.hpp"
#include "../include/City.hpp"
#include "../include/Request.hpp"
#include "../include/Time.hpp"
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
                Tehran.Dijkstra(origin);
                Tehran.PrintPath(stations,origin,destination);
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