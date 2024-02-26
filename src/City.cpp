#include "../include/City.hpp"

/*======================================================================== Distance ========================================================================*/
/* filling adjacency matrix for calculating the best distance path */
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

//-------------------------------------------------------------

std::vector < std::vector<Path> > City::GetAdjMatrix()
{
    return this->adjMatrix;
}

//-------------------------------------------------------------

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

//-------------------------------------------------------------

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

//-------------------------------------------------------------

void City::setArrivingTime(Time t)
{
    arriving_time = t;
}

//-------------------------------------------------------------

Time City::getArrivingTime()
{
    return arriving_time;
}

//-------------------------------------------------------------

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
            int busDistance = adjMatrix[nearestVertex][vertexIndex].getBusDistance();
            int subway_taxiDistance = adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance();
            busDistance = busDistance != 0 ? busDistance : INT_MAX;
            subway_taxiDistance = subway_taxiDistance != 0 ? subway_taxiDistance : INT_MAX;
            if (nearestVertex == source)
            {
                cout << "bus distance " << busDistance << endl;
            }
            
            if(busDistance != INT_MAX && busDistance < subway_taxiDistance)
            {
                // if(adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() != 0
                // && adjMatrix[nearestVertex][vertexIndex].getBusDistance()<=
                // adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance())
                // {
                    
                    weight = busDistance;
                    flag= true;
                    by_bus = true;
                    by_subway_taxi = false;
                    line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                // }
                // else if(adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()!=0)
                // {
                //     weight = adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance();
                //     flag = true;
                //     by_bus = false;
                //     by_subway_taxi = true;
                //     line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                // }
                // else if (adjMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() == 0)
                // {
                //     weight = adjMatrix[nearestVertex][vertexIndex].getBusDistance();
                //     flag= true;
                //     by_bus = true;
                //     by_subway_taxi = false;
                //     line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                // }
            }
            else if (subway_taxiDistance != INT_MAX && subway_taxiDistance <= busDistance)
            {
                weight = subway_taxiDistance;
                flag = true;
                by_bus = false;
                by_subway_taxi = true;
                line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
            }
            else if (subway_taxiDistance == INT_MAX && busDistance == INT_MAX)
            {
                flag = false;
            }
            //int edgeDistance = weight;
 
            if (!added[vertexIndex]&& dijkstraList[nearestVertex] != INT_MAX && flag
             && ((shortestDistance + weight) < dijkstraList[vertexIndex])) 
            {
                includedStations[vertexIndex].second.second = nearestVertex;
                includedStations[vertexIndex].second.first = line;
                includedStations[vertexIndex].first.first.SetBusStatus(by_bus);
                includedStations[vertexIndex].first.first.SetTaxi_SubwayStatus(by_subway_taxi);
                includedStations[vertexIndex].first.second = weight;
                dijkstraList[vertexIndex] = shortestDistance + weight;
            }
        }
    }
}

//-------------------------------------------------------------

void City::Print(std::vector<Station> * S,int currentVertex,int destination)
{
    Bus bus;
    Subway subway;
    if (currentVertex == -1) {
        return;
    }
    //below code gives path between origin and next station
    if (includedStations[includedStations[currentVertex].second.second].second.second == -1)
    {
        if (includedStations[currentVertex].first.first.GetBusStatus())
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff_Traffic() ;
            }
            else
            {
                arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff();
            }
        }
        else if (includedStations[currentVertex].first.first.GetTaxi_SubwayStatus())
        {
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff_Traffic() ;
            }
            else
            {
                arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff();
            }
        }
        
    }
    Print(S,includedStations[currentVertex].second.second,destination);

    // else
    // {

        // if(currentVertex == destination)
        // {
        //     if (includedStations[currentVertex].first.first.GetBusStatus())
        //     {
        //         if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
        //         {
        //             arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff_Traffic() ;
        //         }
        //         else
        //         {
        //             arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff();
        //         }
        //     }
        //     else if (includedStations[currentVertex].first.first.GetTaxi_SubwayStatus())
        //     {
        //         if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
        //         {
        //             arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff_Traffic() ;
        //         }
        //         else
        //         {
        //             arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff();
        //         }
        //     }
        // }
        if(includedStations[currentVertex].first.first.GetBusStatus())
        {
            cout<<(*S)[currentVertex].GetName() << " ( "
            <<includedStations[currentVertex].second.first<<" , Bus ) " << '\n';
            // check changing in subway to bus
            if (includedStations[includedStations[currentVertex].second.second].first.first.GetTaxi_SubwayStatus())
            {
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
                {
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff_Traffic() ;
                }
                else
                {
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff() ;
                }
                
            }
            // check changing in one bus's line to another
            else if(includedStations[includedStations[currentVertex].second.second].second.first != ""
            &&(includedStations[includedStations[currentVertex].second.second].second.first != 
            includedStations[currentVertex].second.first))
            {
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
                {
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff_Traffic();
                }
                else
                {
                    
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff() ;
                }
            }

            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
            {
                arriving_time = arriving_time + (includedStations[currentVertex].first.second * bus.getMinute_per_km_Traffic());
            }
            else
            {
                arriving_time = arriving_time + (includedStations[currentVertex].first.second * bus.getMinute_per_km());
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
                    arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff_Traffic() ;
                }
                else
                {
                    arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff() ;
                }
            }
            // check changing in one subway's line to another
            else if(includedStations[includedStations[currentVertex].second.second].second.first != ""
                &&(includedStations[includedStations[currentVertex].second.second].second.first != 
            includedStations[currentVertex].second.first))
            {
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<=8)
                {
                    arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff_Traffic() ;
                }
                else
                {
                    arriving_time = arriving_time + subway.getMinute_gettingOn_gettingOff() ;
                }
            }
            arriving_time = arriving_time + (includedStations[currentVertex].first.second * 1);
        }
    // }
     
}

//-------------------------------------------------------------

void City::PrintAllPaths(std::vector<Station> * S,int origin)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) {
        if (vertexIndex != origin) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << '\n';
            cout << "Shortest-Distance : " << dijkstraList[vertexIndex] << '\n';
            Print(S,vertexIndex,vertexIndex);
            std::cout << '\n';
        }
    }
}

//-------------------------------------------------------------

void City::PrintPath(std::vector<Station> * S,int origin,int destination)
{
    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
    {
        if (vertexIndex != origin && vertexIndex == destination) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << "   Shortest-Distance : "  
            << dijkstraList[vertexIndex] << '\n'<< '\n';
            Print(S,vertexIndex,destination);
            std::cout << '\n';
            cout << "Arriving Time : ";
            arriving_time.printTime();
        }
    }
}

//-------------------------------------------------------------

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

/*========================================================================== Cost ==========================================================================*/
/* filling adjacency matrix for calculating the best cost path */
void City::fillCostMatrix(std::vector <Station>* station, std::vector<Cost>* cost)
{ 
    for (int i = 0; i < (station->size()); i++)
    {
        std::vector<Cost> row;
        for (int j = 0; j < (station->size()); j++)
        {
            Cost temp_1;
            if (i == j)
            {
                temp_1.setOrigin((*station)[i].GetName());
                temp_1.setDestination((*station)[i].GetName());
                temp_1.setLine(0);
                temp_1.setVehicle("non");
                temp_1.setMinimumCost(0.0);
                row.push_back(temp_1);
            }
            else
            {
                Cost temp_2;
                for (int k = 0; k < (cost->size()); k++)
                {
                    if(((*cost)[k].getOrigin() == (*station)[i].GetName() && (*cost)[k].getDestination() == (*station)[j].GetName())
                    ||((*cost)[k].getOrigin() == (*station)[j].GetName() && (*cost)[k].getDestination() == (*station)[i].GetName()))
                    {
                        temp_2.setOrigin((*station)[i].GetName());
                        temp_2.setDestination((*station)[j].GetName());
                        temp_2.setLine((*cost)[k].getLine());
                        temp_2.setVehicle((*cost)[k].getVehicle());
                        temp_2.setMinimumCost((*cost)[k].getMinimumCost());
                    }
                }
                row.push_back(temp_2);
            }
        }
        costMatrix.push_back(row);
    }  
}

//-------------------------------------------------------------
/* dijkstra implementation for the best cost path and invoks the print function */
void City::dijkstraOnCost(int source, int destination,vector<Path>* p)
{
    for (int i = 0; i < N; i++)
        dijkstraList[i] = INT_MAX;
    
    std::vector<bool> finalized(N,false);
    dijkstraList[source] = 0; int min = -1;
    parent[source].second.second = -1;

    for (int i = 0; i < N-1; i++)
    {
        min = -1;
        for (int j = 0; j < N; j++)
        {
            if (!finalized[j] and (min == -1 or dijkstraList[j] < dijkstraList[min]))
                min = j;
        }
        finalized[min] = true;
        for (int  k = 0; k < N; k++)
        {
            if ((costMatrix[min][k].getMinimumCost() != 0.0) and (!finalized[k]))
            {
                parent[k].first.setOrigin(costMatrix[min][k].getOrigin());
                parent[k].first.setDestination(costMatrix[min][k].getDestination());
                parent[k].first.setVehicle(costMatrix[min][k].getVehicle());
                parent[k].first.setLine(costMatrix[min][k].getLine());
                parent[k].second.first = findDistance(p,costMatrix[min][k].getOrigin(),costMatrix[min][k].getDestination()); 
                parent[k].second.second = min;

                if (min == source)  
                {
                    if (dijkstraList[min] + costMatrix[min][k].getMinimumCost() < dijkstraList[k])
                        dijkstraList[k] = dijkstraList[min] + costMatrix[min][k].getMinimumCost();
                }
                else if (costMatrix[parent[min].second.second][min].getLine() == costMatrix[min][k].getLine())
                {
                    if (parent[min].second.second != source)
                        dijkstraList[k] = dijkstraList[min];
                    else
                        dijkstraList[k] = costMatrix[parent[min].second.second][min].getMinimumCost();
                }
                else if((costMatrix[parent[min].second.second][min].getLine() != costMatrix[min][k].getLine()))
                {
                    if (dijkstraList[min] + costMatrix[min][k].getMinimumCost() < dijkstraList[k])
                        dijkstraList[k] = dijkstraList[min] + costMatrix[min][k].getMinimumCost();
                }
            }       
        }
    }
}

//-------------------------------------------------------------
/* prints only the path from source to destination */
void City::printPath(int source,int destination)
{
    if (destination == source)
        return;

    printPath(source,parent[destination].second.second);
    path.push_back(parent[destination]);
    cout << parent[destination].first.getDestination() << " (";
    cout << parent[destination].first.getVehicle() <<  ", Line";
    cout << parent[destination].first.getLine() << ")\n";
}

//-------------------------------------------------------------
/* prints some basics and printPath and calculateTime functions */
void City::print(int source, int destination, vector<Station>*S)
{
    cout << endl << endl << endl;
    cout << (*S)[source].GetName() << " -> " << parent[destination].first.getDestination() << "    ";
    cout << "Low-Cost : " << dijkstraList[destination] << endl;
    //printPath(source,destination); 
    cout << endl;
    calculateTime();
    
}

//-------------------------------------------------------------
/* finds the distance between to stations in vector path */
int City::findDistance(vector<Path>* p, string origin, string destination)
{
    int distance = 0;
    for (int i = 0; i < (*p).size(); i++)
    {
        if (((*p)[i].getFirstST() == origin and (*p)[i].getSecondST() == destination) or ((*p)[i].getFirstST() == destination and (*p)[i].getSecondST() == origin))
        {
            if ((*p)[i].getBusDistance() < (*p)[i].getTrainTaxiDistance())
                distance  = (*p)[i].getBusDistance();
            else
                distance = (*p)[i].getTrainTaxiDistance();
        }
    }
    return distance;
}

//-------------------------------------------------------------
/* calculates the arriving time when user reach destination */
void City::calculateTime()
{
    int i = 0;
    int size = path.size()-1;
    for (i = 0; i < size; i++)
    {
        if (stoi(arriving_time.getHour()) >= 6 and stoi(arriving_time.getHour()) <=8)
        {
            if (path[i].first.getLine() == path[i+1].first.getLine())
            {   
                if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first);

                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first*8);

                else if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first) + 30;

                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first*8) + 24;
            }
            else if(path[i].first.getLine() != path[i+1].first.getLine())
            {
                if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "metro")  
                    arriving_time = arriving_time + (path[i].second.first) + 24;
                
                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first*8) + 30;
                
                else if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first) + 30;
                
                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first*8) + 24;
            }   
        }
        else
        {
            if (path[i].first.getLine() == path[i+1].first.getLine())
            {
                if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first);

                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first*4);

                else if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first) + 15;

                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first*4) + 8;
            }
            else if(path[i].first.getLine() != path[i+1].first.getLine())
            {
                if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "metro")  
                    arriving_time = arriving_time + (path[i].second.first) + 8;
                
                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first*4) + 15;
                
                else if (path[i].first.getVehicle() == "metro" and  path[i+1].first.getVehicle() == "bus")
                    arriving_time = arriving_time + (path[i].second.first) + 15;
                
                else if (path[i].first.getVehicle() == "bus" and  path[i+1].first.getVehicle() == "metro")
                    arriving_time = arriving_time + (path[i].second.first*4) + 8;
            } 
        }
    }
    if (stoi(arriving_time.getHour()) >= 6 and stoi(arriving_time.getHour()) <=8)
    {
        if (path[i].first.getVehicle() == "metro") 
            arriving_time = arriving_time + (path[i].second.first); 
        else
            arriving_time = arriving_time + (path[i].second.first*8);                 
    }
    else
    {
        if (path[i].first.getVehicle() == "metro") 
            arriving_time = arriving_time + (path[i].second.first); 
        else
            arriving_time = arriving_time + (path[i].second.first*4); 
    }
    cout << "Arriving Time : ";
    arriving_time.printTime();
}

void City::dijkstraOnTime(int source,int destination,std::vector<Station> * stations,std::vector<Path>* path,Time t)
{
    Besttime start_with_bus;
    Besttime start_with_taxi;
    Besttime start_with_subway;
    start_with_bus.setArrivingTime(t);
    start_with_taxi.setArrivingTime(t);
    start_with_subway.setArrivingTime(t);
    start_with_bus.FillAdjMatrix(stations,path);
    start_with_taxi.FillAdjMatrix(stations,path);
    start_with_subway.FillAdjMatrix(stations,path);
    int bestTime_start_bus = 0 ;
    int bestTime_start_taxi = 0 ;
    int bestTime_start_subway = 0 ;
    if ((*stations)[source].GetBusStatus())
    {
        start_with_bus.Dijkstra(source,"bus");
        bestTime_start_bus = start_with_bus.getDijkstraList()[destination];
    }
    else
    {
        bestTime_start_bus = INT_MAX;
    }
    if((*stations)[source].GetTaxi_SubwayStatus())
    {
        start_with_taxi.Dijkstra(source,"taxi");
        start_with_subway.Dijkstra(source,"subway");
        bestTime_start_taxi = start_with_taxi.getDijkstraList()[destination];
        bestTime_start_subway = start_with_subway.getDijkstraList()[destination];
        
    }
    else
    {
        bestTime_start_taxi = INT_MAX;
        bestTime_start_subway = INT_MAX;
    }
    if(bestTime_start_bus < bestTime_start_taxi && bestTime_start_bus < bestTime_start_subway)
    {
        start_with_bus.PrintPath(stations,source,destination);
    }
    if (bestTime_start_taxi < bestTime_start_bus && bestTime_start_taxi < bestTime_start_subway) 
    {
        start_with_taxi.PrintPath(stations,source,destination);

    }
    if (bestTime_start_subway < bestTime_start_bus && bestTime_start_subway < bestTime_start_taxi)
    {
        start_with_subway.PrintPath(stations,source,destination);
    }
    
    
}