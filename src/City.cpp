#include "../include/City.hpp"

void City::FillAdjMatrix(vector<Station> * stations, vector<Path> *path)
{
    //filling the matrix with indices from stations
    //each adjMatrix[i][j] is a Path object that filling from Distance.txt
    for (int i = 0; i < stations->size(); i++)
    {
        vector <Path> row;
        for (int j = 0; j < stations->size(); j++)
        {
            Path tempPath;
            if(i == j)
            {
                tempPath.setFirstST((*stations)[i].GetName());
                tempPath.setSecondST((*stations)[i].GetName());
                tempPath.setBusDistance(0);
                tempPath.setTrainTaxiDistance(0);
                row.push_back(tempPath);
            }
            else
            {
                Path temp;
                //searching in path vector for matching the station's name
                for (int k = 0; k < path->size(); k++)
                {
                    if(((*path)[k].getFirstST()==(*stations)[i].GetName() && (*path)[k].getSecondST()==(*stations)[j].GetName())
                    ||((*path)[k].getFirstST()==(*stations)[j].GetName() && (*path)[k].getSecondST()==(*stations)[i].GetName()))
                    {
                        temp.setFirstST((*stations)[i].GetName());
                        temp.setSecondST((*stations)[j].GetName());
                        if((*path)[k].getBusDistance() >= 0 ||(*path)[k].getTrainTaxiDistance() >= 0)
                        {
                            temp.setBusDistance((*path)[k].getBusDistance());
                            temp.setTrainTaxiDistance((*path)[k].getTrainTaxiDistance());
                        }
                        else
                        {
                            temp.setBusDistance(0);
                            temp.setTrainTaxiDistance(0);
                        }
                        temp.setSubway_Taxi_Line((*path)[k].getSubway_Taxi_Line());
                        temp.setBus_Line((*path)[k].getBus_Line());
                    }
                }
                row.push_back(temp);
            }    
        }
        adjMatrix.push_back(row);
    }
}

vector < vector<Path> > City::GetAdjMatrix()
{
    return this->adjMatrix;
}
void City::PrintAdjMatrix(vector <Station>* stations)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        cout << (*stations)[i].GetName() <<'\n';
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            cout <<"firstST : "<<adjMatrix[i][j].getFirstST() << "  secondST : " << adjMatrix[i][j].getSecondST()
             << "   " << adjMatrix[i][j].getTrainTaxiDistance() << ","<<adjMatrix[i][j].getBusDistance()
             <<"     "<<adjMatrix[i][j].getSubway_Taxi_Line() <<" , " << adjMatrix[i][j].getBus_Line()<<'\n';
        }
        cout << '\n';
    }
}

int City::MinDistance(int distance[],bool sptSet[]) 
{
    int min = INT_MAX, minIndex;

    for (int i = 0; i < N; i++)
    {
        if (sptSet[i] == false && distance[i] <= min)
        {
            min = distance[i], minIndex = i;
        }
    }
    return minIndex;
}

// void City::Dijkstra(int source)
// {
//     bool sptSet[N]; 
//     // sptSet[i] will be true if vertex i is
//     // included in shortest
//     // path tree or shortest distance from src to i is
//     // finalized
 
//     // Initialize all distances as INFINITE and stpSet[] as
//     // false
//     for (int i = 0; i < N; i++)
//     {
//         dijkstraList[i] = INT_MAX;
//         sptSet[i] = false;
//         includeStations[i] = false;
//     }
 
//     // Distance of source vertex from itself is always 0
//     dijkstraList[source] = 0;
 
//     // Find shortest path for all vertices
//     for (int count = 0; count < N - 1; count++) {
//         // Pick the minimum distance vertex from the set of
//         // vertices not yet processed. u is always equal to
//         // src in the first iteration.
//         int u = MinDistance(dijkstraList, sptSet);
 
//         // Mark the picked vertex as processed
//         sptSet[u] = true;
 
//         // Update dist value of the adjacent vertices of the
//         // picked vertex.
//         for (int v = 0; v < N; v++)
//         {
//             int weight=0;
//             bool flag = false; // check existing path
//             if(adjMatrix[u][v].getBusDistance()!=0 )
//             {
//                 weight = adjMatrix[u][v].getBusDistance();
//                 flag= true;
//             }
//             else if(adjMatrix[u][v].getTrainTaxiDistance()!=0)
//             {
//                 weight = adjMatrix[u][v].getTrainTaxiDistance();
//                 flag = true;
//             }
//             else
//             {
//                 flag = false;
//             }
//             if (!sptSet[v] && flag
//                 && dijkstraList[u] != INT_MAX
//                 && dijkstraList[u] + weight < dijkstraList[v])
//                 dijkstraList[v] = dijkstraList[u] + weight;
//         }
//     }
// }
void City::Dijkstra(int source)
{
 
    // added[i] will true if vertex i is
    // included / in shortest path tree
    // or shortest distance from src to
    // i is finalized
    vector<bool> added(N);
 
    // Initialize all distances as
    // INFINITE and added[] as false
    for (int vertexIndex = 0; vertexIndex < N;
         vertexIndex++) {
        dijkstraList[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
 
    // Distance of source vertex from
    // itself is always 0
    dijkstraList[source] = 0;
 
    // The starting vertex does not
    // have a parent
    includedStations[source].second.second = -1;
 
    // Find shortest path for all
    // vertices
    for (int i = 1; i < N; i++) {
 
        // Pick the minimum distance vertex
        // from the set of vertices not yet
        // processed. nearestVertex is
        // always equal to startNode in
        // first iteration.
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < N;
             vertexIndex++) {
            if (!added[vertexIndex] && dijkstraList[vertexIndex] <shortestDistance) 
            {
                nearestVertex = vertexIndex;
                shortestDistance = dijkstraList[vertexIndex];
            }
        }
 
        // Mark the picked vertex as
        // processed
        added[nearestVertex] = true;
 
        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
        {
            int weight=0;
            bool flag = false; // check existing path
            bool by_bus = false;
            bool by_subway_taxi = false;
            std::string line="";
            if(adjMatrix[nearestVertex][vertexIndex].getBusDistance()!=0)
            {
                if(adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() != 0
                && adjMatrix[nearestVertex][vertexIndex].getBusDistance()<=
                adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance())
                {
                    weight = adjMatrix[nearestVertex][vertexIndex].getBusDistance();
                    flag= true;
                    by_bus = true;
                    by_subway_taxi = false;
                    line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                }
                else if(adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()!=0)
                {
                    weight = adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance();
                    flag = true;
                    by_bus = false;
                    by_subway_taxi = true;
                    line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                }
                else if (adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() == 0)
                {
                    weight = adjMatrix[nearestVertex][vertexIndex].getBusDistance();
                    flag= true;
                    by_bus = true;
                    by_subway_taxi = false;
                    line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                }
            }
            else if (adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() != 0)
            {
                weight = adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance();
                flag = true;
                by_bus = false;
                by_subway_taxi = true;
                line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
            }
            else
            {
                flag = false;
            }
            int edgeDistance = weight;
 
            if (!added[vertexIndex]&& dijkstraList[nearestVertex] != INT_MAX && flag && ((shortestDistance + edgeDistance) < dijkstraList[vertexIndex])) 
            {
                includedStations[vertexIndex].second.second = nearestVertex;
                includedStations[vertexIndex].second.first = line;
                includedStations[vertexIndex].first.SetBusStatus(by_bus);
                includedStations[vertexIndex].first.SetTaxi_SubwayStatus(by_subway_taxi);
                dijkstraList[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

}

void City::Print(vector<Station> * S,int currentVertex)
{
    if (currentVertex == -1) {
        return;
    }
    Print(S,includedStations[currentVertex].second.second);
    if(includedStations[currentVertex].first.GetBusStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<includedStations[currentVertex].second.first<<" , Bus ) " << '\n';
    }
    else if(includedStations[currentVertex].first.GetTaxi_SubwayStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<includedStations[currentVertex].second.first<<" , Taxi_Subway ) "<<'\n';
    }
}
void City::PrintAllPaths(vector<Station> * S,int origin)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) {
        if (vertexIndex != origin) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << '\n';
            cout << "Shortest-Distance : " << dijkstraList[vertexIndex] << '\n';
            Print(S,vertexIndex);
            cout << '\n';
        }
    }
}
void City::PrintPath(vector<Station> * S,int origin,int destination)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
    {
        if (vertexIndex != origin && vertexIndex == destination) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << "   Shortest-Distance : "  
            << dijkstraList[vertexIndex] << '\n'<< '\n';
            Print(S,vertexIndex);
            cout << '\n';
        }
    }
}
// void City::PrintPath(vector<Station> * S)
// {
//     for (int i = 0; i < N; i++)
//     {
//         cout << (*S)[i].GetName() << "  Distance :  " << dijkstraList[i] << '\n';
//     }
    
// }

int City::GetShortestDistance(int destination)
{
    for (int i = 0; i < N; i++)
    {
        if(i == destination)
        {
            return dijkstraList[i];
        }
    }
    
}