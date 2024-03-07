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
            if(busDistance != INT_MAX && busDistance < subway_taxiDistance)
            {
                    
                weight = busDistance;
                flag= true;
                by_bus = true;
                by_subway_taxi = false;
                line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();

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
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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
            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
                {
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff_Traffic();
                }
                else
                {
                    
                    arriving_time = arriving_time + bus.getMinute_gettingOn_gettingOff() ;
                }
            }

            if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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
                if (stoi(arriving_time.getHour()) >= 6 && stoi(arriving_time.getHour())<8
            ||(stoi(arriving_time.getHour())== 8 && stoi(arriving_time.getMinute())== 0))
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

void City::Dijkstra_FloydWarshall(int origin,int destination,std::vector <Station>* stations,std::vector<Path>* path,Time time)
{
    
    LowestCost primary_start_with_bus;
    LowestCost primary_start_with_taxi;
    LowestCost primary_start_with_subway;

    primary_start_with_bus.setArrivingTime(time);
    primary_start_with_taxi.setArrivingTime(time);
    primary_start_with_subway.setArrivingTime(time);

    primary_start_with_bus.fillCostMatrix(stations,path);
    primary_start_with_taxi.fillCostMatrix(stations,path);
    primary_start_with_subway.fillCostMatrix(stations,path);

    LowestCost intermediate;
    LowestCost intermediate_start_with_taxi;
    LowestCost intermediate_start_with_subway;

    intermediate.fillCostMatrix(stations,path);
    intermediate_start_with_taxi.fillCostMatrix(stations,path);
    intermediate_start_with_subway.fillCostMatrix(stations,path);

    intermediate.setArrivingTime(time);
    intermediate_start_with_taxi.setArrivingTime(time);
    intermediate_start_with_subway.setArrivingTime(time);

    pair<pair<Cost,int>,pair<int,int>> first_copy_parents[N];
    pair<pair<Cost,int>,pair<int,int>> second_copy_parents[N];
    pair<pair<Cost,int>,pair<int,int>> third_copy_parents[N];
    pair<pair<Cost,int>,pair<int,int>> forth_copy_parents[N];
    Bus bus;
    Taxi taxi;
    Subway subway;
    int min_cost = INT_MAX;
    int min_time = INT_MAX;
    int index_min_cost = -1;
    if ((*stations)[origin].GetBusStatus())
    {
        primary_start_with_bus.dijkstraOnCost(origin,"bus");
    }
    if((*stations)[origin].GetTaxi_SubwayStatus())
    {
        primary_start_with_taxi.dijkstraOnCost(origin,"taxi");
        primary_start_with_subway.dijkstraOnCost(origin,"subway");
    }
    
    for (int i = 0; i < N; i++)
    {
        if ( i != destination)
        {
            int time_to_i = 0;
            int time_to_destination = 0;

            int cost_to_i = 0;

            int LowestCost_start_bus = 0 ;
            int LowestCost_start_taxi = 0 ;
            int LowestCost_start_subway = 0 ;

            bool bus_status_to_i;
            bool taxi_status_to_i;
            bool subway_status_to_i ;
            std::string bus_line_to_i ;
            std::string subway_taxi_line_to_i ;

            int cost_to_destination = 0;

            bool bus_status_to_destination = false;
            bool taxi_status_to_destination = false;
            bool subway_status_to_destination = false;
            std::string bus_line_to_destination = "";
            std::string subway_taxi_line_to_destination ="";

            int LowestCost_destination= 0 ;
            int LowestCost_start_taxi_destination = 0 ;
            int LowestCost_start_subway_destination = 0 ;

                if ((*stations)[origin].GetBusStatus())
                {
                    LowestCost_start_bus = primary_start_with_bus.getCostDijkstraList()[i];
                }
                else
                {
                    LowestCost_start_bus = INT_MAX;
                }
                if((*stations)[origin].GetTaxi_SubwayStatus())
                {
                    LowestCost_start_taxi = primary_start_with_taxi.getCostDijkstraList()[i];
                    LowestCost_start_subway = primary_start_with_subway.getCostDijkstraList()[i];
                }
                else
                {
                    LowestCost_start_taxi = INT_MAX;
                    LowestCost_start_subway = INT_MAX;
                }
                if(LowestCost_start_bus < LowestCost_start_taxi && LowestCost_start_bus < LowestCost_start_subway)
                {
                    cost_to_i = LowestCost_start_bus;
                    bus_status_to_i = primary_start_with_bus.getParents()[i].first.first.getBusStatus();
                    taxi_status_to_i = primary_start_with_bus.getParents()[i].first.first.getTaxiStatus();
                    subway_status_to_i = primary_start_with_bus.getParents()[i].first.first.getSubwayStatus();
                    bus_line_to_i = primary_start_with_bus.getParents()[i].first.first.getBus_Line();
                    subway_taxi_line_to_i = primary_start_with_bus.getParents()[i].first.first.getSubway_Taxi_Line() ;
                    for (int j = 0; j < N; j++)
                    {
                        first_copy_parents[j] = primary_start_with_bus.getParents()[j];
                    }
                    time_to_i = primary_start_with_bus.getParents()[i].first.second;
                }
                if (LowestCost_start_taxi < LowestCost_start_bus && LowestCost_start_taxi < LowestCost_start_subway) 
                {
                    cost_to_i = LowestCost_start_taxi;
                    bus_status_to_i = primary_start_with_taxi.getParents()[i].first.first.getBusStatus();
                    taxi_status_to_i = primary_start_with_taxi.getParents()[i].first.first.getTaxiStatus();
                    subway_status_to_i = primary_start_with_taxi.getParents()[i].first.first.getSubwayStatus();
                    bus_line_to_i = primary_start_with_taxi.getParents()[i].first.first.getBus_Line();
                    subway_taxi_line_to_i = primary_start_with_taxi.getParents()[i].first.first.getSubway_Taxi_Line() ;
                    for (int j = 0; j < N; j++)
                    {
                        first_copy_parents[j] = primary_start_with_taxi.getParents()[j];
                    }
                    time_to_i = primary_start_with_taxi.getParents()[i].first.second;
                }
                if (LowestCost_start_subway < LowestCost_start_bus && LowestCost_start_subway < LowestCost_start_taxi)
                {
                    cost_to_i = LowestCost_start_subway;
                    bus_status_to_i = primary_start_with_subway.getParents()[i].first.first.getBusStatus();
                    taxi_status_to_i = primary_start_with_subway.getParents()[i].first.first.getTaxiStatus();
                    subway_status_to_i = primary_start_with_subway.getParents()[i].first.first.getSubwayStatus();
                    bus_line_to_i = primary_start_with_subway.getParents()[i].first.first.getBus_Line();
                    subway_taxi_line_to_i = primary_start_with_subway.getParents()[i].first.first.getSubway_Taxi_Line() ;
                    for (int j = 0; j < N; j++)
                    {
                        first_copy_parents[j] = primary_start_with_subway.getParents()[j];
                    }
                    time_to_i = primary_start_with_subway.getParents()[i].first.second;
                }
                int j;
                if ((*stations)[i].GetBusStatus())
                {
                    if (LowestCost_start_bus < LowestCost_start_taxi && LowestCost_start_bus == LowestCost_start_subway)
                    {
                        intermediate.setArrivingTime(time + primary_start_with_bus.getParents()[i].first.second);

                    }
                    else
                    {
                        intermediate.setArrivingTime(time + time_to_i);
                    }
                    intermediate.dijkstra(i);
                    LowestCost_destination = intermediate.getCostDijkstraList()[destination];
                }
                else
                {
                    LowestCost_destination = INT_MAX;
                }
                if((*stations)[i].GetTaxi_SubwayStatus())
                {
                    if (LowestCost_start_bus < LowestCost_start_taxi && LowestCost_start_bus == LowestCost_start_subway)
                    {
                        intermediate_start_with_subway.setArrivingTime(time + primary_start_with_subway.getParents()[i].first.second);

                    }
                    else
                    {
                        intermediate_start_with_subway.setArrivingTime(time + time_to_i);
                    }
                    intermediate_start_with_subway.dijkstraOnCost(i,"subway");
                    LowestCost_start_subway_destination = intermediate_start_with_subway.getCostDijkstraList()[destination];
                }
                else
                {
                    LowestCost_start_subway_destination = INT_MAX;
                }
                if ((*stations)[i].GetTaxi_SubwayStatus())
                {
                    intermediate_start_with_taxi.setArrivingTime(time + time_to_i);
                    intermediate_start_with_taxi.dijkstraOnCost(i,"taxi");
                    LowestCost_start_taxi_destination = intermediate_start_with_taxi.getCostDijkstraList()[destination];
                }
                else
                {
                    LowestCost_start_taxi_destination = INT_MAX;
                }
                if(LowestCost_destination < LowestCost_start_taxi_destination && 
                LowestCost_destination < LowestCost_start_subway_destination)
                {
                    cost_to_destination = LowestCost_destination;
                    j = intermediate.getIndexFromParents(i,destination);
                    bus_status_to_destination = intermediate.getParents()[j].first.first.getBusStatus();
                    taxi_status_to_destination = intermediate.getParents()[j].first.first.getTaxiStatus();
                    subway_status_to_destination = intermediate.getParents()[j].first.first.getSubwayStatus();
                    bus_line_to_destination = intermediate.getParents()[j].first.first.getBus_Line();
                    subway_taxi_line_to_destination =intermediate.getParents()[j].first.first.getSubway_Taxi_Line();
                    for (int j = 0; j < N; j++)
                    {
                        second_copy_parents[j] = intermediate.getParents()[j];
                    }
                    time_to_destination = intermediate.getParents()[destination].first.second;
                }
                else if (LowestCost_start_taxi_destination < LowestCost_destination 
                && LowestCost_start_taxi_destination < LowestCost_start_subway_destination) 
                {
                    cost_to_destination = LowestCost_start_taxi_destination;
                    j = intermediate_start_with_taxi.getIndexFromParents(i,destination);
                    bus_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getBusStatus();
                    taxi_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getTaxiStatus();
                    subway_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getSubwayStatus();
                    bus_line_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getBus_Line();
                    subway_taxi_line_to_destination =intermediate_start_with_taxi.getParents()[j].first.first.getSubway_Taxi_Line();
                    for (int j = 0; j < N; j++)
                    {
                        second_copy_parents[j] = intermediate_start_with_taxi.getParents()[j];
                    }
                    time_to_destination = intermediate_start_with_taxi.getParents()[destination].first.second;
                }
                else if (LowestCost_start_subway_destination < LowestCost_destination
                 && LowestCost_start_subway_destination < LowestCost_start_taxi_destination)
                {
                    cost_to_destination = LowestCost_start_subway_destination;
                    j = intermediate_start_with_subway.getIndexFromParents(i,destination);
                    bus_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBusStatus();
                    taxi_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getTaxiStatus();
                    subway_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getSubwayStatus();
                    bus_line_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBus_Line();
                    subway_taxi_line_to_destination =intermediate_start_with_subway.getParents()[j].first.first.getSubway_Taxi_Line();
                    for (int j = 0; j < N; j++)
                    {
                        second_copy_parents[j] = intermediate_start_with_subway.getParents()[j];
                    }
                    time_to_destination = intermediate_start_with_subway.getParents()[destination].first.second;
                }
                if (LowestCost_start_bus < LowestCost_start_taxi && LowestCost_start_bus == LowestCost_start_subway)
                {
                    if (bus_status_to_destination)
                    {
                        cost_to_i = LowestCost_start_bus;
                        bus_status_to_i = primary_start_with_bus.getParents()[i].first.first.getBusStatus();
                        taxi_status_to_i = primary_start_with_bus.getParents()[i].first.first.getTaxiStatus();
                        subway_status_to_i = primary_start_with_bus.getParents()[i].first.first.getSubwayStatus();
                        bus_line_to_i = primary_start_with_bus.getParents()[i].first.first.getBus_Line();
                        subway_taxi_line_to_i = primary_start_with_bus.getParents()[i].first.first.getSubway_Taxi_Line() ;
                        for (int j = 0; j < N; j++)
                        {
                            first_copy_parents[j] = primary_start_with_bus.getParents()[j];
                        }
                        time_to_i = primary_start_with_bus.getParents()[i].first.second;
                    }
                    if (subway_status_to_destination)
                    {
                        cost_to_i = LowestCost_start_subway;
                        bus_status_to_i = primary_start_with_subway.getParents()[i].first.first.getBusStatus();
                        taxi_status_to_i = primary_start_with_subway.getParents()[i].first.first.getTaxiStatus();
                        subway_status_to_i = primary_start_with_subway.getParents()[i].first.first.getSubwayStatus();
                        bus_line_to_i = primary_start_with_subway.getParents()[i].first.first.getBus_Line();
                        subway_taxi_line_to_i = primary_start_with_subway.getParents()[i].first.first.getSubway_Taxi_Line() ;
                        for (int j = 0; j < N; j++)
                        {
                            first_copy_parents[j] = primary_start_with_subway.getParents()[j];
                        }
                        time_to_i = primary_start_with_subway.getParents()[i].first.second;
                    }
                }
                if(LowestCost_destination < LowestCost_start_taxi_destination && 
                LowestCost_destination == LowestCost_start_subway_destination)
                {
                    if (bus_status_to_i)
                    {
                        cost_to_destination = LowestCost_destination;
                        j = intermediate.getIndexFromParents(i,destination);
                        bus_status_to_destination = intermediate.getParents()[j].first.first.getBusStatus();
                        taxi_status_to_destination = intermediate.getParents()[j].first.first.getTaxiStatus();
                        subway_status_to_destination = intermediate.getParents()[j].first.first.getSubwayStatus();
                        bus_line_to_destination = intermediate.getParents()[j].first.first.getBus_Line();
                        subway_taxi_line_to_destination =intermediate.getParents()[j].first.first.getSubway_Taxi_Line();
                        for (int j = 0; j < N; j++)
                        {
                            second_copy_parents[j] = intermediate.getParents()[j];
                        }
                        time_to_destination = intermediate.getParents()[destination].first.second;
                    }
                    if (subway_status_to_i)
                    {
                        cost_to_destination = LowestCost_start_subway_destination;
                        j = intermediate_start_with_subway.getIndexFromParents(i,destination);
                        bus_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBusStatus();
                        taxi_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getTaxiStatus();
                        subway_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getSubwayStatus();
                        bus_line_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBus_Line();
                        subway_taxi_line_to_destination =intermediate_start_with_subway.getParents()[j].first.first.getSubway_Taxi_Line();
                        for (int j = 0; j < N; j++)
                        {
                            second_copy_parents[j] = intermediate_start_with_subway.getParents()[j];
                        }
                        time_to_destination = intermediate_start_with_subway.getParents()[destination].first.second ;
                    }
                    
                    
                }
            
                
            // }
            if (bus_status_to_i == bus_status_to_destination && 
                bus_line_to_i == bus_line_to_destination && bus_line_to_i != "" 
                && bus_line_to_destination != "")
            {
                if (cost_to_i != 0 && i != origin)
                {
                    if (((cost_to_i + cost_to_destination) - bus.getCost_for_each_line()) < min_cost)
                    {
                        min_cost = (cost_to_i + cost_to_destination) - bus.getCost_for_each_line();
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                    else if (((cost_to_i + cost_to_destination) - bus.getCost_for_each_line()) == min_cost && 
                    (time_to_i + time_to_destination) < min_time && (time_to_i + time_to_destination)!= 0)
                    {
                        min_cost = (cost_to_i + cost_to_destination) - bus.getCost_for_each_line();
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                }
                else if(i == origin)
                {
                    if (((cost_to_i + cost_to_destination) - bus.getCost_for_each_line()) < min_cost)
                    {
                        min_cost = (cost_to_i + cost_to_destination) - bus.getCost_for_each_line();
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                    else if (((cost_to_i + cost_to_destination) - bus.getCost_for_each_line()) == min_cost && 
                    (time_to_i + time_to_destination) < min_time && (time_to_i + time_to_destination)!= 0)
                    {
                        min_cost = (cost_to_i + cost_to_destination) - bus.getCost_for_each_line();
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }

                }
                
            }
            else if (subway_status_to_i == subway_status_to_destination && 
            subway_taxi_line_to_i == subway_taxi_line_to_destination
            && subway_taxi_line_to_i != "" && subway_taxi_line_to_destination != ""
            )
            {
                if (cost_to_i != 0 && i!= origin)
                {
                    if (((cost_to_i + cost_to_destination) - subway.getCost_for_each_line()) < min_cost)
                    {
                        min_cost = (cost_to_i + cost_to_destination )- subway.getCost_for_each_line();
                        index_min_cost = i;       
                        min_time = time_to_i + time_to_destination;       
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                    else if (((cost_to_i + cost_to_destination) - subway.getCost_for_each_line()) == min_cost&& 
                    (time_to_i + time_to_destination) < min_time&&(time_to_i + time_to_destination)!=0)
                    {
                        min_cost = (cost_to_i + cost_to_destination )- subway.getCost_for_each_line();
                        index_min_cost = i;       
                        min_time = time_to_i + time_to_destination;       
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                    
                }
                else if (i == origin)
                {
                    if (((cost_to_i + cost_to_destination) - subway.getCost_for_each_line()) < min_cost)
                    {
                        min_cost = (cost_to_i + cost_to_destination )- subway.getCost_for_each_line();
                        index_min_cost = i;       
                        min_time = time_to_i + time_to_destination;       
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                    else if (((cost_to_i + cost_to_destination) - subway.getCost_for_each_line()) == min_cost&& 
                    (time_to_i + time_to_destination) < min_time&&(time_to_i + time_to_destination)!=0)
                    {
                        min_cost = (cost_to_i + cost_to_destination )- subway.getCost_for_each_line();
                        index_min_cost = i;       
                        min_time = time_to_i + time_to_destination;       
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }
                    }
                }
                
                
            }
            else
            {

                if (cost_to_i != 0 && i != origin)
                {
                    
                    if ((cost_to_i + cost_to_destination) < min_cost)
                    {
                        min_cost = cost_to_i + cost_to_destination;
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }           
                    }
                    else if ((cost_to_i + cost_to_destination) == min_cost&& (time_to_i + time_to_destination) < min_time
                    &&(time_to_i + time_to_destination)!=0)
                    {
                        min_cost = cost_to_i + cost_to_destination;
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }      
                    }
                }
                else if (i == origin)
                {
                    if ((cost_to_i + cost_to_destination) < min_cost)
                    {
                        min_cost = cost_to_i + cost_to_destination;
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }           
                    }
                    else if ((cost_to_i + cost_to_destination) == min_cost&& (time_to_i + time_to_destination) < min_time
                    &&(time_to_i + time_to_destination)!=0)
                    {
                        min_cost = cost_to_i + cost_to_destination;
                        index_min_cost = i;
                        min_time = time_to_i + time_to_destination;
                        for (int j = 0; j < N; j++)
                        {
                            third_copy_parents[j] = first_copy_parents[j];
                        }
                        for (int j = 0; j < N; j++)
                        {
                            forth_copy_parents[j] = second_copy_parents[j];
                        }      
                    }
                }
                  
            }
        }
        
    }
    cout << "\n" << (*stations)[origin].GetName() << " -> ";
    cout << (*stations)[destination].GetName() << "   Lowest-Cost : "  
    << min_cost << '\n'<< '\n';
    LowestCost temp;
    temp.print_cost(index_min_cost,stations,third_copy_parents);
    temp.print_cost(destination,stations,forth_copy_parents);
    cout << '\n';
    cout << "Arriving Time : ";
    (time + min_time).printTime();
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
    
    
    Besttime intermediate_start_with_taxi;
    Besttime intermediate_start_with_subway;
    Besttime intermediate_start_with_bus;
    intermediate_start_with_bus.FillAdjMatrix(stations,path);
    intermediate_start_with_bus.setArrivingTime(t);
    intermediate_start_with_taxi.setArrivingTime(t);
    intermediate_start_with_subway.setArrivingTime(t);
    intermediate_start_with_taxi.FillAdjMatrix(stations,path);
    intermediate_start_with_subway.FillAdjMatrix(stations,path);
    
    if ((*stations)[source].GetBusStatus())
    {
        start_with_bus.Dijkstra(source);
    }
    if((*stations)[source].GetTaxi_SubwayStatus())
    {
        start_with_taxi.Dijkstra(source,"taxi");
        start_with_subway.Dijkstra(source,"subway");        
    }

    pair<pair<TimedPath,int>,pair<bool,int>> first_copy_parents[N];
    pair<pair<TimedPath,int>,pair<bool,int>> second_copy_parents[N];
    pair<pair<TimedPath,int>,pair<bool,int>> third_copy_parents[N];
    pair<pair<TimedPath,int>,pair<bool,int>> forth_copy_parents[N];
    int min_time = INT_MAX;
    int index_min_time = -1;
    for (int i = 0; i < N; i++)
    {
        int bestTime_start_bus = 0 ;
        int bestTime_start_taxi = 0 ;
        int bestTime_start_subway = 0 ;
        int time_to_i = 0 ;

        bool bus_status_to_i;
        bool taxi_status_to_i;
        bool subway_status_to_i ;
        std::string bus_line_to_i ;
        std::string subway_taxi_line_to_i ;
        
        int intermediate_bestTime_start_bus = 0 ;
        int intermediate_bestTime_start_taxi = 0 ;
        int intermediate_bestTime_start_subway = 0 ;
        int time_to_destination = 0 ;

        bool bus_status_to_destination;
        bool taxi_status_to_destination;
        bool subway_status_to_destination ;
        std::string bus_line_to_destination ;
        std::string subway_taxi_line_to_destination ;
        if (i != destination)
        {
            if ((*stations)[source].GetBusStatus())
            {
                bestTime_start_bus = start_with_bus.getDijkstraList()[i];
            }
            else
            {
                bestTime_start_bus = INT_MAX;
            }
            if((*stations)[source].GetTaxi_SubwayStatus())
            {
                bestTime_start_taxi = start_with_taxi.getDijkstraList()[i];
                bestTime_start_subway = start_with_subway.getDijkstraList()[i];
                
            }
            else
            {
                bestTime_start_taxi = INT_MAX;
                bestTime_start_subway = INT_MAX;
            }
            if(bestTime_start_bus <= bestTime_start_taxi && bestTime_start_bus <= bestTime_start_subway)
            {
                time_to_i = bestTime_start_bus;
                bus_status_to_i = start_with_bus.getParents()[i].first.first.getBusStatus();
                taxi_status_to_i = start_with_bus.getParents()[i].first.first.getTaxiStatus();
                subway_status_to_i = start_with_bus.getParents()[i].first.first.getSubwayStatus();
                bus_line_to_i = start_with_bus.getParents()[i].first.first.getBus_Line();
                subway_taxi_line_to_i = start_with_bus.getParents()[i].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    first_copy_parents[j] = start_with_bus.getParents()[j];
                }
            }
            if (bestTime_start_taxi <= bestTime_start_bus && bestTime_start_taxi <= bestTime_start_subway) 
            {
                time_to_i = bestTime_start_taxi;
                bus_status_to_i = start_with_taxi.getParents()[i].first.first.getBusStatus();
                taxi_status_to_i = start_with_taxi.getParents()[i].first.first.getTaxiStatus();
                subway_status_to_i = start_with_taxi.getParents()[i].first.first.getSubwayStatus();
                bus_line_to_i = start_with_taxi.getParents()[i].first.first.getBus_Line();
                subway_taxi_line_to_i = start_with_taxi.getParents()[i].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    first_copy_parents[j] = start_with_taxi.getParents()[j];
                }
            }
            if (bestTime_start_subway <= bestTime_start_bus && bestTime_start_subway <= bestTime_start_taxi)
            {
                time_to_i = bestTime_start_subway;
                bus_status_to_i = start_with_subway.getParents()[i].first.first.getBusStatus();
                taxi_status_to_i = start_with_subway.getParents()[i].first.first.getTaxiStatus();
                subway_status_to_i = start_with_subway.getParents()[i].first.first.getSubwayStatus();
                bus_line_to_i = start_with_subway.getParents()[i].first.first.getBus_Line();
                subway_taxi_line_to_i = start_with_subway.getParents()[i].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    first_copy_parents[j] = start_with_subway.getParents()[j];
                }
            }
            int j;

            if ((*stations)[i].GetBusStatus())
            {
                if (bestTime_start_bus < bestTime_start_taxi && bestTime_start_bus == bestTime_start_subway)
                {
                    intermediate_start_with_bus.setArrivingTime(t + bestTime_start_bus);

                }
                else if (bestTime_start_bus < bestTime_start_subway && bestTime_start_bus == bestTime_start_taxi)
                {
                    intermediate_start_with_bus.setArrivingTime(t + bestTime_start_bus);
                }
                else if (bestTime_start_taxi < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_bus.setArrivingTime(t + bestTime_start_taxi);

                }
                else if (bestTime_start_subway < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_bus.setArrivingTime(t + bestTime_start_subway);
                }
                else
                {
                    intermediate_start_with_bus.setArrivingTime(t + time_to_i);
                }
                intermediate_start_with_bus.Dijkstra(i);
                intermediate_bestTime_start_bus = intermediate_start_with_bus.getDijkstraList()[destination];
            }
            else
            {
                intermediate_bestTime_start_bus = INT_MAX;
            }
            if((*stations)[i].GetTaxi_SubwayStatus())
            {
                if (bestTime_start_bus < bestTime_start_taxi && bestTime_start_bus == bestTime_start_subway)
                {
                    intermediate_start_with_taxi.setArrivingTime(t + bestTime_start_bus);

                }
                else if (bestTime_start_bus < bestTime_start_subway && bestTime_start_bus == bestTime_start_taxi)
                {
                    intermediate_start_with_taxi.setArrivingTime(t + bestTime_start_bus);

                }
                else if (bestTime_start_taxi < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_taxi.setArrivingTime(t + bestTime_start_taxi);

                }
                else if (bestTime_start_subway < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_taxi.setArrivingTime(t + bestTime_start_subway);
                }
                else
                {
                    intermediate_start_with_taxi.setArrivingTime(t + time_to_i);
                }
                intermediate_start_with_taxi.Dijkstra(i,"taxi");
                intermediate_bestTime_start_taxi = intermediate_start_with_taxi.getDijkstraList()[destination];
    
            }
            else
            {
                intermediate_bestTime_start_taxi = INT_MAX;
                
            }
            if ((*stations)[i].GetTaxi_SubwayStatus())
            {
                if (bestTime_start_bus < bestTime_start_taxi && bestTime_start_bus == bestTime_start_subway)
                {
                    intermediate_start_with_subway.setArrivingTime(t + bestTime_start_bus);

                }
                else if (bestTime_start_bus < bestTime_start_subway && bestTime_start_bus == bestTime_start_taxi)
                {
                    intermediate_start_with_subway.setArrivingTime(t + bestTime_start_bus);

                }
                else if (bestTime_start_taxi < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_subway.setArrivingTime(t + bestTime_start_taxi);

                }
                else if (bestTime_start_subway < bestTime_start_bus && bestTime_start_taxi == bestTime_start_subway)
                {
                    intermediate_start_with_subway.setArrivingTime(t + bestTime_start_subway);
                }
                else
                {
                    intermediate_start_with_subway.setArrivingTime(t + time_to_i);
                }
                intermediate_start_with_subway.Dijkstra(i,"subway");
                intermediate_bestTime_start_subway = intermediate_start_with_subway.getDijkstraList()[destination];
            }
            else
            {
                intermediate_bestTime_start_subway = INT_MAX;
            }
            
            if(intermediate_bestTime_start_bus <= intermediate_bestTime_start_taxi
            && intermediate_bestTime_start_bus <= intermediate_bestTime_start_subway)
            {
                time_to_destination = intermediate_bestTime_start_bus;
                j = intermediate_start_with_bus.getIndexFromParents(i,destination);
                bus_status_to_destination = intermediate_start_with_bus.getParents()[j].first.first.getBusStatus();
                taxi_status_to_destination = intermediate_start_with_bus.getParents()[j].first.first.getTaxiStatus();
                subway_status_to_destination = intermediate_start_with_bus.getParents()[j].first.first.getSubwayStatus();
                bus_line_to_destination = intermediate_start_with_bus.getParents()[j].first.first.getBus_Line();
                subway_taxi_line_to_destination = intermediate_start_with_bus.getParents()[j].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    second_copy_parents[j] = intermediate_start_with_bus.getParents()[j];
                }
            }
            if (intermediate_bestTime_start_taxi <= intermediate_bestTime_start_bus
            && intermediate_bestTime_start_taxi <= intermediate_bestTime_start_subway) 
            {
                time_to_destination = intermediate_bestTime_start_taxi;
                j = intermediate_start_with_taxi.getIndexFromParents(i,destination);
                bus_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getBusStatus();
                taxi_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getTaxiStatus();
                subway_status_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getSubwayStatus();
                bus_line_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getBus_Line();
                subway_taxi_line_to_destination = intermediate_start_with_taxi.getParents()[j].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    second_copy_parents[j] = intermediate_start_with_taxi.getParents()[j];
                }
            }
            if (intermediate_bestTime_start_subway <= intermediate_bestTime_start_bus
            && intermediate_bestTime_start_subway <= intermediate_bestTime_start_taxi)
            {
                time_to_destination = intermediate_bestTime_start_subway;
                j = intermediate_start_with_subway.getIndexFromParents(i,destination);
                bus_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBusStatus();
                taxi_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getTaxiStatus();
                subway_status_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getSubwayStatus();
                bus_line_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getBus_Line();
                subway_taxi_line_to_destination = intermediate_start_with_subway.getParents()[j].first.first.getSubway_Taxi_Line();
                for (int j = 0; j < N; j++)
                {
                    second_copy_parents[j] = intermediate_start_with_subway.getParents()[j];
                }
            }
            if ((time_to_i + time_to_destination) < min_time && (time_to_i + time_to_destination) != 0)
            {
                min_time = (time_to_i + time_to_destination);
                index_min_time = i;
                for (int j = 0; j < N; j++)
                {
                    third_copy_parents[j] = first_copy_parents[j];
                }
                for (int j = 0; j < N; j++)
                {
                    forth_copy_parents[j] = second_copy_parents[j];
                }
                
            }
        }
    }
    cout << "\n" << (*stations)[source].GetName() << " -> ";
    cout << (*stations)[destination].GetName() << "   Best-Time : "  
    << min_time<<" minutes" << '\n'<< '\n';
    Besttime bt;
    bt.Print(stations,index_min_time,third_copy_parents);
    bt.Print(stations,destination,forth_copy_parents);
    std::cout << '\n';
    cout << "Arriving Time : ";
    (t+min_time).printTime();
    
    
}