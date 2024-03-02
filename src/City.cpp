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
void City::fillCostMatrix(std::vector <Station>* stations, std::vector<Path>* path)
{ 
    for (int i = 0; i < stations->size(); i++)
    {
        std::vector <Cost> row;
        for (int j = 0; j < stations->size(); j++)
        {
            Cost tempPath;
            if(i == j)
            {
                tempPath.setFirstST((*stations)[i].GetName());
                tempPath.setSecondST((*stations)[i].GetName());
                tempPath.setBusCost(0);
                tempPath.setSubwayCost(0);
                tempPath.setTaxiCost(0);
                tempPath.setBusDistance(0);
                tempPath.setTrainTaxiDistance(0);
                row.push_back(tempPath);
                
            }
            else
            {
                Cost temp;
                Bus bus;
                Taxi taxi;
                Subway subway;
                //searching in path vector for matching the station's name
                for (int k = 0; k < path->size(); k++)
                {
                    if(((*path)[k].getFirstST()==(*stations)[i].GetName() && (*path)[k].getSecondST()==(*stations)[j].GetName())
                    ||((*path)[k].getFirstST()==(*stations)[j].GetName() && (*path)[k].getSecondST()==(*stations)[i].GetName()))
                    {
                        temp.setFirstST((*stations)[i].GetName());
                        temp.setSecondST((*stations)[j].GetName());
                        if((*path)[k].getBusDistance() > 0)
                        {
                            temp.setBusCost(bus.getCost_for_each_line());
                        }
                        else
                        {
                            temp.setBusCost(0);
                        }
                        if((*path)[k].getTrainTaxiDistance() > 0)
                        {
                            temp.setTaxiCost(((*path)[k].getTrainTaxiDistance())*taxi.getCost_for_each_line());
                            temp.setSubwayCost(subway.getCost_for_each_line());
                        }
                        else
                        {
                            temp.setTaxiCost(0);
                            temp.setSubwayCost(0);
                        }
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
        costMatrix.push_back(row);
    }
}

void City::printCostMatrix(std::vector <Station>* stations)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        std::cout << (*stations)[i].GetName() <<'\n';
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            cout <<"firstST : "<<costMatrix[i][j].getFirstST() << "  secondST : " << costMatrix[i][j].getSecondST()
             << "   " << costMatrix[i][j].getSubwayCost() << " , "<<costMatrix[i][j].getTaxiCost()<<" , "<<
             costMatrix[i][j].getBusCost()<<"     "<<costMatrix[i][j].getSubway_Taxi_Line() 
             <<" , " << costMatrix[i][j].getBus_Line()<<'\n';
        }
        std::cout << '\n';
    }
}
//-------------------------------------------------------------
/* dijkstra implementation for the best cost path and invoks the print function */
void City::dijkstraOnCost(int source)
{
    /*added[i] will true if vertex i is included in shortest path tree or shortest distance from src to
    i is finalized*/
    std::vector<bool> added(N);
    Time time_during_dijkstra = arriving_time;
    // Initialize all distances as
    // INFINITE and added[] as false
    for (int vertexIndex = 0; vertexIndex < N;
         vertexIndex++) {
        costDijkstraList[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
 
    // Distance of source vertex from
    // itself is always 0
    Bus bus;
    Taxi taxi;
    Subway subway;

    costDijkstraList[source] = 0;
 
    // The starting vertex does not
    // have a parent
    parents[source].second.second = -1;
    parents[source].first.second = 0;
    // Find shortest path for all
    // vertices
    for (int i = 1; i < N; i++) {
        /*Pick the minimum distance vertex from the set of vertices not yet processed.
        nearestVertex is always equal to startNode in first iteration.*/
        int nearestVertex = -1;
        int lowestCost = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < N;
             vertexIndex++) {
            if (!added[vertexIndex] && costDijkstraList[vertexIndex] <lowestCost) 
            {
                nearestVertex = vertexIndex;
                lowestCost = costDijkstraList[vertexIndex];
            }
        }
        /* Mark the picked vertex as processed*/
        added[nearestVertex] = true;
 
        /* Update dist value of the adjacent vertices of the picked vertex.*/ 
        for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
        {
            int weight=0;
            bool flag = false; // check existing path
            bool by_bus = false;
            bool by_subway = false;
            bool by_taxi = false;
            bool traffic_time = false;
            int minute_passed = 0;
            std::string line="";
            int busCost = costMatrix[nearestVertex][vertexIndex].getBusCost();
            int taxiCost = costMatrix[nearestVertex][vertexIndex].getTaxiCost();
            int subwayCost = costMatrix[nearestVertex][vertexIndex].getSubwayCost();

            if(nearestVertex == source)
            {
                if(busCost != 0)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<=8)
                    {
                        busCost = bus.getCost_for_each_line_Traffic();
                    }
                }

                if(subwayCost != 0)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<=8)
                    {
                        subwayCost = subway.getCost_for_each_line_Traffic();
                    }
                }
                if(taxiCost != 0)
                {
                    
                    if (stoi(time_during_dijkstra.getHour()) >= 18 && stoi(time_during_dijkstra.getHour())<=20)
                    {
                        taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                    }
                }
                busCost = busCost != 0 ? busCost : INT_MAX;
                taxiCost = taxiCost != 0 ? taxiCost : INT_MAX;
                subwayCost = subwayCost != 0 ? subwayCost : INT_MAX;
                if (busCost != INT_MAX && busCost < taxiCost && busCost < subwayCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<=8)
                    {
                        minute_passed += bus.getMinute_gettingOn_gettingOff_Traffic();
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                        traffic_time = true;
                    }
                    else
                    {
                        minute_passed += bus.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 && stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour())<=8)
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                            traffic_time = true;
                        }
                        else
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km());
                            traffic_time  = false;
                        }

                    }
                    weight = busCost;
                    flag= true;
                    by_bus = true;
                    by_taxi = false;
                    by_subway = false;
                    line = costMatrix[nearestVertex][vertexIndex].getBus_Line();
                }
                if (taxiCost != INT_MAX && taxiCost < busCost && taxiCost < subwayCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 18 && stoi(time_during_dijkstra.getHour())<=20)
                    {
                        minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                        traffic_time = true;
                    }
                    else
                    {
                        minute_passed += taxi.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour() ) >= 18 && stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour())<=20)
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                            traffic_time = true;
                        }
                        else
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km());
                            traffic_time  = false;
                        }

                    }
                    weight = taxiCost;
                    flag= true;
                    by_bus = false;
                    by_taxi = true;
                    by_subway = false;
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                }
                if (subwayCost != INT_MAX && subwayCost < taxiCost && subwayCost < busCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<=8)
                    {
                        minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                        traffic_time = true;
                    }
                    else
                    {
                        minute_passed += subway.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 && stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour())<=8)
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                            traffic_time = true;
                        }
                        else
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km());
                            traffic_time  = false;
                        }

                    }
                    weight = subwayCost;
                    flag= true;
                    by_bus = false;
                    by_taxi = false;
                    by_subway = true;
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                }
                
                
            }
            else
            {
                //time_during_dijkstra  arriving_time + shortestTime;
                busCost = busCost != 0 ? busCost : INT_MAX;
                taxiCost = taxiCost != 0 ? taxiCost : INT_MAX;
                subwayCost = subwayCost != 0 ? subwayCost : INT_MAX;
                if(busCost != INT_MAX)
                {
                    
                    if(parents[nearestVertex].first.first.getBusStatus()
                    && costMatrix[nearestVertex][vertexIndex].getBus_Line() == parents[nearestVertex].first.first.getBus_Line())
                    {
                        if(parents[nearestVertex].second.first == true)
                        {
                            busCost = 0;
                            traffic_time = true;
                        }
                        else
                        {
                            traffic_time = false;
                            busCost = 0;
                        }
                    }
                    else if (costMatrix[nearestVertex][vertexIndex].getBus_Line() != parents[nearestVertex].first.first.getBus_Line())
                    {
                        if (stoi((time_during_dijkstra + parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                        {
                            busCost = bus.getCost_for_each_line_Traffic();
                            //busTime  busTime + bus.getMinute_gettingOn_gettingOff_Traffic();
                            traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<=8)
                            {
                                busCost = bus.getCost_for_each_line_Traffic();
                                //busTime  busTime + bus.getMinute_gettingOn_gettingOff();
                                traffic_time  = true;
                            }
                            else
                            {
                                busCost = bus.getCost_for_each_line();
                                traffic_time  = false;
                            }
                        }                        
                        
                    }
                }
                if (subwayCost!= INT_MAX)
                {
                    if(parents[nearestVertex].first.first.getSubwayStatus()
                    && costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() == parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if(parents[nearestVertex].second.first == true)
                        {
                            subwayCost = 0;
                            traffic_time = true;
                        }
                        else
                        {
                            traffic_time = false;
                            subwayCost = 0;
                        }
                    }
                    else if(parents[nearestVertex].first.first.getTaxiStatus()
                    && costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() == parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                        {
                            subwayCost = subway.getCost_for_each_line_Traffic();
                            traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<=8)
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time  = true;
                            }
                            else
                            {
                                subwayCost = subway.getCost_for_each_line();
                                traffic_time  = false;
                            }
                        }                        
                    }
                    else if (costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() != parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                        {
                            subwayCost = subway.getCost_for_each_line_Traffic();
                            traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<=8)
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time  = true;
                            }
                            else
                            {
                                subwayCost = subway.getCost_for_each_line();
                                traffic_time  = false;
                            }
                        }                        
                        
                    }
                }
                if(taxiCost != INT_MAX)
                {
                    
                    if(parents[nearestVertex].first.first.getTaxiStatus()
                    && costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() == parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if(parents[nearestVertex].second.first == true)
                        {
                            taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            traffic_time = true;
                        }
                        else
                        {
                            traffic_time = false;
                            taxiCost = taxiCost;
                        }
                    }
                    else if(parents[nearestVertex].first.first.getSubwayStatus()
                    && costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() == parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=20)
                        {
                            taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            //taxiCost = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                            traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<=20)
                            {
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                //taxiTime = taxiTime + taxi.getMinute_gettingOn_gettingOff();
                                traffic_time  = true;
                            }
                            else
                            {
                                taxiCost = taxiCost;
                                traffic_time  = false;
                            }
                        }  
                    }
                    else if (costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line() != 
                    parents[nearestVertex].first.first.getSubway_Taxi_Line())
                    {
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=20)
                        {
                            taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            //taxiTime = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                            traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<=20)
                            {
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                //taxiTime = taxiTime + taxi.getMinute_gettingOn_gettingOff();
                                traffic_time  = true;
                            }
                            else
                            {
                                //taxiCost = taxiTime + taxi.getMinute_gettingOn_gettingOff();
                                traffic_time  = false;
                            }
                        }                        
                        
                    }
                }
                if(busCost != INT_MAX && busCost < taxiCost && busCost < subwayCost)
                {                    
                    weight = busCost;
                    flag= true;
                    by_bus = true;
                    by_taxi = false;
                    by_subway = false;
                    line = costMatrix[nearestVertex][vertexIndex].getBus_Line();
                }
                else if (taxiCost!= INT_MAX && taxiCost < busCost && taxiCost < subwayCost)// equal conditions must be checked
                {
                    weight = taxiCost;
                    flag = true;
                    by_bus = false;
                    by_taxi = true;
                    by_subway = false;
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                }
                else if (subwayCost != INT_MAX && subwayCost < busCost && subwayCost < taxiCost)
                {
                    
                    weight = subwayCost;
                    flag = true;
                    by_bus = false;
                    by_taxi = false;
                    by_subway = true;
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                }
                // else if (busTime != INT_MAX && busTime == taxiTime && busTime < subwayTime)
                // {
                //     weight = busTime;
                //     flag= true;
                //     by_bus = true;
                //     by_taxi = false;
                //     by_subway = false;
                //     line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                // }
                // else if (busTime != INT_MAX && busTime < taxiTime && busTime == subwayTime)
                // {
                //     weight = busTime;
                //     flag= true;
                //     by_bus = true;
                //     by_taxi = false;
                //     by_subway = false;
                //     line = adjMatrix[nearestVertex][vertexIndex].getBus_Line();
                // }
                // else if (taxiTime != INT_MAX && taxiTime < busTime && taxiTime == subwayTime)
                // {
                //     weight = taxiTime;
                //     flag = true;
                //     by_bus = false;
                //     by_taxi = true;
                //     by_subway = false;
                //     line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                // }
                // else if (subwayTime != INT_MAX && subwayTime == busTime && subwayTime == taxiTime)
                // {
                //     weight = subwayTime;
                //     flag = true;
                //     by_bus = false;
                //     by_taxi = false;
                //     by_subway = true;
                //     line = adjMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                // }
                

            }
            if (!added[vertexIndex]&& costDijkstraList[nearestVertex] != INT_MAX && flag
             && ((lowestCost + weight) < costDijkstraList[vertexIndex])) 
            {
               // parents[vertexIndex].first.second = weight;
                parents[vertexIndex].second.first = traffic_time;
                parents[vertexIndex].second.second = nearestVertex;
                parents[vertexIndex].first.first.setBusStatus(by_bus);
                parents[vertexIndex].first.first.setTaxiStatus(by_taxi);
                parents[vertexIndex].first.first.setSubwayStatus(by_subway);
                if(by_bus)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                    {
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                        minute_passed+= bus.getMinute_gettingOn_gettingOff_Traffic();
                    }
                    else
                    {
                        minute_passed += bus.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                        {
                           minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                        }
                        else
                        {
                            minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                        }
                    }
                    parents[vertexIndex].first.first.setBus_Line(line);
                    parents[vertexIndex].first.first.setSubway_Taxi_Line("");
                    parents[vertexIndex].first.second = minute_passed+ parents[nearestVertex].first.second;
                }
                else if (by_taxi || by_subway)
                {
                    parents[vertexIndex].first.first.setBus_Line("");
                    parents[vertexIndex].first.first.setSubway_Taxi_Line(line);
                }
                if (by_taxi)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=20)
                    {
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                        minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                    }
                    else
                    {
                        minute_passed += taxi.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=20)
                        {
                            minute_passed  += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                        }
                        else
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                        }
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                if (by_subway)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<= 8)
                    {
                        minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                        minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                    }
                    else
                    {
                        minute_passed += subway.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<=8)
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                        }
                        else
                        {
                            minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                        }
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                
                costDijkstraList[vertexIndex] = lowestCost + weight;
            }
        }
    }
}

void City::printDijkstraOnCost(std::vector <Station>* stations)
{
    for (int i = 0; i < N; i++)
    {
        cout << (*stations)[i].GetName() <<"    " << costDijkstraList[i]<<'\n';
    }
    
}

void City::print_cost(int currentVertex,int destination, vector<Station>* S)
{
    Bus bus;
    Subway subway;
    Taxi taxi;
    if (currentVertex == -1) {
        return;
    }
    print_cost(parents[currentVertex].second.second,destination,S);
    if(parents[currentVertex].first.first.getBusStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parents[currentVertex].first.first.getBus_Line()<<" , Bus ) " << '\n';
    }
    else if(parents[currentVertex].first.first.getSubwayStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parents[currentVertex].first.first.getSubway_Taxi_Line()<<" , Subway ) "<<'\n';
    }
    else if(parents[currentVertex].first.first.getTaxiStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parents[currentVertex].first.first.getSubway_Taxi_Line()<<" , Taxi ) "<<'\n';
    }
}

void City::print_path_cost(std::vector<Station> * S,int origin,int destination)
{

    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
    {
        if (vertexIndex != origin && vertexIndex == destination) {
            cout << "\n" << (*S)[origin].GetName() << " -> ";
            cout << (*S)[vertexIndex].GetName() << "   Shortest-Distance : "  
            << costDijkstraList[vertexIndex] << '\n'<< '\n';
            print_cost(vertexIndex,destination,S);
            std::cout << '\n';
            // cout << "Arriving Time : ";
            //arriving_time.printTime();
        }
    }

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