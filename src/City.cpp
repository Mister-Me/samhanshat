

#include "../include/City.hpp"

void City::FillAdjMatrix(std::vector<Station> * stations, std::vector<Path> *path)
{
    //filling the matrix with indices from stations
    //each adjMatrix[i][j] is a Path object that filling from Distance.txt
    for (int i = 0; i < stations->size(); i++)
    {
        std::vector <Path> row;
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

std::vector < std::vector<Path> > City::GetAdjMatrix()
{
    return this->adjMatrix;
}
void City::PrintAdjMatrix(std::vector <Station>* stations)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        std::cout << (*stations)[i].GetName() <<'\n';
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            cout <<"firstST : "<<adjMatrix[i][j].getFirstST() << "  secondST : " << adjMatrix[i][j].getSecondST()
             << "   " << adjMatrix[i][j].getTrainTaxiDistance() << ","<<adjMatrix[i][j].getBusDistance()
             <<"     "<<adjMatrix[i][j].getSubway_Taxi_Line() <<" , " << adjMatrix[i][j].getBus_Line()<<'\n';
        }
        std::cout << '\n';
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
void City::setArrivingTime(Time t)
{
    arriving_time = t;
}
Time City::getArrivingTime()
{
    return arriving_time;
}
void City::Dijkstra(int source)
{
 
    // added[i] will true if vertex i is
    // included / in shortest path tree
    // or shortest distance from src to
    // i is finalized
    std::vector<bool> added(N);
 
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
                includedStations[vertexIndex].first.first.SetBusStatus(by_bus);
                includedStations[vertexIndex].first.first.SetTaxi_SubwayStatus(by_subway_taxi);
                includedStations[vertexIndex].first.second = edgeDistance;
                dijkstraList[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

}

void City::Print(std::vector<Station> * S,int currentVertex)
{
    if (currentVertex == -1) {
        return;
    }
    Print(S,includedStations[currentVertex].second.second);
    if(includedStations[currentVertex].first.first.GetBusStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<includedStations[currentVertex].second.first<<" , Bus ) " << '\n';
        // check changing in subway to bus
        if (includedStations[includedStations[currentVertex].second.second].first.first.GetTaxi_SubwayStatus())
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + 24 ;
                arriving_time = arriving_time + 30 ;
            }
            else
            {
                arriving_time = arriving_time + 8 ;
                arriving_time = arriving_time + 15 ;
            }
            
        }
        // check changing in one bus's line to another
        else if(includedStations[includedStations[currentVertex].second.second].second.first != ""
        &&(includedStations[includedStations[currentVertex].second.second].second.first != 
        includedStations[currentVertex].second.first))
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + 30 ;
                arriving_time = arriving_time + 30 ;
            }
            else
            {
                arriving_time = arriving_time + 15 ;
                arriving_time = arriving_time + 15 ;
            }
        }

        if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
        {
            arriving_time = arriving_time + (includedStations[currentVertex].first.second * 8);
        }
        else
        {
            arriving_time = arriving_time + (includedStations[currentVertex].first.second * 4);
        }
    }
    else if(includedStations[currentVertex].first.first.GetTaxi_SubwayStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<includedStations[currentVertex].second.first<<" , Subway ) "<<'\n';
        //check changing in bus to subway
        if (includedStations[includedStations[currentVertex].second.second].first.first.GetBusStatus())
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + 24 ;
                arriving_time = arriving_time + 30 ;
            }
            else
            {
                arriving_time = arriving_time + 8 ;
                arriving_time = arriving_time + 15 ;
            }
        }
        // check changing in one subway's line to another
        else if(includedStations[includedStations[currentVertex].second.second].second.first != ""
            &&(includedStations[includedStations[currentVertex].second.second].second.first != 
        includedStations[currentVertex].second.first))
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + 24 ;
                arriving_time = arriving_time + 24 ;
            }
            else
            {
                arriving_time = arriving_time + 8 ;
                arriving_time = arriving_time + 8 ;
            }
        }
        arriving_time = arriving_time + (includedStations[currentVertex].first.second * 1);
    }
     
}
void City::PrintAllPaths(std::vector<Station> * S,int origin)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) {
        if (vertexIndex != origin) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << '\n';
            cout << "Shortest-Distance : " << dijkstraList[vertexIndex] << '\n';
            Print(S,vertexIndex);
            std::cout << '\n';
        }
    }
}
void City::PrintPath(std::vector<Station> * S,int origin,int destination)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
    {
        if (vertexIndex != origin && vertexIndex == destination) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << "   Shortest-Distance : "  
            << dijkstraList[vertexIndex] << '\n'<< '\n';
            Print(S,vertexIndex);
            std::cout << '\n';
            cout << "Arriving Time : ";
            arriving_time.printTime();
        }
    }
}

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

void City::fillCostMatrix(std::vector <Station>* station, std::vector<Cost>* cost)
{
    std::vector<Cost> row; Cost temp;

    for (int i = 0; i < (station->size()); i++)
    {
        for (int j = 0; j < (station->size()); j++)
        {
            if (i == j)
            {
                temp.setOrigin((*station)[i].GetName());
                temp.setDestination((*station)[i].GetName());
                temp.setMinimumCost(0.0);
                row.push_back(temp);
            }
            else
            {
                for (int k = 0; k < (cost->size()); k++)
                {
                    if(((*cost)[k].getOrigin() == (*station)[i].GetName() && (*cost)[k].getDestination() == (*station)[j].GetName())
                    ||((*cost)[k].getOrigin() == (*station)[j].GetName() && (*cost)[k].getDestination() == (*station)[i].GetName()))
                    {
                        temp.setOrigin((*station)[i].GetName());
                        temp.setDestination((*station)[j].GetName());
                        temp.setMinimumCost((*cost)[k].getMinimumCost());
                    }
                }
                row.push_back(temp);
            }
        }
        costMatrix.push_back(row); row.clear();
    }   
}

void City::dijkstraOnCost(int source)
{
    for (int i = 0; i < N; i++)
        dijkstraCost[i] = DBL_MAX;
    
    std::vector<bool> finalized(N,false);
    dijkstraCost[source] = 0; int min = -1;

    for (int i = 0; i < N-1; i++)
    {
        min = -1;
        for (int j = 0; j < N; j++)
        {
            if (!finalized[j] and (min == -1 or dijkstraCost[j] < dijkstraCost[min]))
                min = j;
        }
        finalized[min] = true;
        for (int  k = 0; k < N; k++)
        {
            if (costMatrix[min][k].getMinimumCost() != 0.0 and !finalized[k])
                if (dijkstraCost[min] + costMatrix[min][k].getMinimumCost() < dijkstraCost[k])
                    dijkstraCost[k] = dijkstraCost[min] + costMatrix[min][k].getMinimumCost();        
        }
    }
}