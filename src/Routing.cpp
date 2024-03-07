#include "../include/Routing.hpp"

void Routing::Split(string record, char delimeter, vector<Station> *S)
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
    temp.SetName(station[0]);
    if (station[1] == "bus")
    {
        temp.SetBusStatus(true);
    }
    if (station[2] == "taxi")
    {
        temp.SetTaxi_SubwayStatus(true);
    }
    int key = hash.hashFunction(temp);
    // push in our Stations vector
    (*S)[key] = temp; 
}
void Routing::readFromFile(std::vector <Station>*S,string filename)
{
    try
    {
        ifstream in(filename);
        string text; 
        while(getline(in, text)) 
        {  
            Split(text,'_',S);
        } 
        in.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
// finds the index of a specific station in the vector
int Routing::findIndex(string station,vector<Station>*S)
{
    return hash.returnKey(station);  
}
void Routing::runAlgorithm()
{
    vector <Station>* stations = new vector <Station>(N);
    vector <Path>* path = new vector <Path>;
    vector<Cost> *cost = new vector <Cost>;
    Path p;
    Cost c;
    Besttime bestTime;
    LowestCost lowestCost;
    this->readFromFile(stations,"../file/Stations.txt");
    p.readFromFile(path,"../file/Distance.txt");
    City Tehran;
    City Map;
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
        int origin = this->findIndex(requests.front().GetOrigin(),stations);
        int destination= this->findIndex(requests.front().GetDestination(),stations);
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
                Tehran.dijkstraOnTime(origin,destination,stations,path,requests.front().GetTime());
                Map.Dijkstra_FloydWarshall(origin,destination,stations,path,requests.front().GetTime());
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
}