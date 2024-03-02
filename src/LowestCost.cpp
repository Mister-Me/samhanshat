#include "../include/LowestCost.hpp"

/*========================================================================== Cost ==========================================================================*/
/* filling adjacency matrix for calculating the best cost path */
LowestCost::LowestCost()
{
    parents = new pair<pair<Cost,int>,pair<int,int>>[N];
}
void LowestCost::fillCostMatrix(std::vector <Station>* stations, std::vector<Path>* path)
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

void LowestCost::printCostMatrix(std::vector <Station>* stations)
{
    for (int i = 0; i < costMatrix.size(); i++)
    {
        std::cout << (*stations)[i].GetName() <<'\n';
        for (int j = 0; j < costMatrix.size(); j++)
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
void LowestCost::dijkstraOnCost(int source,std::string vehicle)
{
    delete[] parents;
    parents = new pair<pair<Cost,int>,pair<int,int>>[N];
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
                if (vehicle == "bus")
                {
                    if(busCost != 0)
                    {
                        if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                traffic_time  = true;
                                busCost = bus.getCost_for_each_line_Traffic();
                            }
                            else
                            {
                                traffic_time  = false;
                            }
                            // minute_passed += bus.getMinute_gettingOn_gettingOff_Traffic();
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                            // traffic_time = true;
                            parents[nearestVertex].second.first = true;

                        }
                        else
                        {
                            // minute_passed += bus.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 
                            && stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour())<8
                            || (stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getMinute())==0))
                            {
                                busCost = bus.getCost_for_each_line_Traffic();
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                                traffic_time = true;
                                parents[nearestVertex].second.first = true;
                            }
                            else
                            {
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km());
                                traffic_time  = false;
                                parents[nearestVertex].second.first = false;
                            }

                        }
                        weight = busCost;
                        flag= true;
                        by_bus = true;
                        by_taxi = false;
                        by_subway = false;
                        parents[nearestVertex].first.first.setBusStatus(by_bus);
                        parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                        parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                        line = costMatrix[nearestVertex][vertexIndex].getBus_Line();
                        // parents[nearestVertex].first.first.setBus_Line(line);
                        // parents[nearestVertex].first.first.setSubway_Taxi_Line("");
                    }
                    else
                    {
                        flag = false;
                    }
                }
                else if (vehicle == "subway")
                {
                    if(subwayCost != 0)
                    {
                        if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                traffic_time  = true;
                                subwayCost = subway.getCost_for_each_line_Traffic();
                            }
                            else
                            {
                                traffic_time  = false;
                            }
                            // minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                            // traffic_time = true;
                            parents[nearestVertex].second.first = true;
                        }
                        else
                        {
                            // minute_passed += subway.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 
                            && stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour())< 8
                            || (stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getMinute())==0))
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                                traffic_time = true;
                                parents[nearestVertex].second.first = true;
                            }
                            else
                            {
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km());
                                traffic_time  = false;
                                parents[nearestVertex].second.first = false;
                            }

                        }
                        weight = subwayCost;
                        flag= true;
                        by_bus = false;
                        by_taxi = false;
                        by_subway = true;
                        parents[nearestVertex].first.first.setBusStatus(by_bus);
                        parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                        parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                        line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                        // parents[nearestVertex].first.first.setBus_Line("");
                        // parents[nearestVertex].first.first.setSubway_Taxi_Line(line);
                    }
                    else
                    {
                        flag = false;
                    }
                }
                else if (vehicle == "taxi")
                {
                    if(taxiCost != 0)
                    {
                        if (stoi(time_during_dijkstra.getHour()) >= 18 && stoi(time_during_dijkstra.getHour())<20
                        || (stoi(time_during_dijkstra.getHour()) == 20 
                        && stoi(time_during_dijkstra.getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                                && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                traffic_time  = true;
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            }
                            else
                            {
                                traffic_time  = false;
                            }
                            // minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                            // traffic_time = true;
                            parents[nearestVertex].second.first = true;
                        }
                        else
                        {
                            // minute_passed += taxi.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour() ) >= 18 && 
                            stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour())<20
                            || (stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour()) == 20 
                            && stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getMinute())==0))
                            {
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                                traffic_time = true;
                                parents[nearestVertex].second.first = true;
                            }
                            else
                            {
                                // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km());
                                traffic_time  = false;
                                parents[nearestVertex].second.first = false;
                            }

                        }
                        weight = taxiCost;
                        flag= true;
                        by_bus = false;
                        by_taxi = true;
                        by_subway = false;
                        parents[nearestVertex].first.first.setBusStatus(by_bus);
                        parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                        parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                        line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                        // parents[nearestVertex].first.first.setBus_Line("");
                        // parents[nearestVertex].first.first.setSubway_Taxi_Line(line);
                    }
                    else
                    {
                        flag = false;
                    }
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
                        if (stoi((time_during_dijkstra + parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                busCost = bus.getCost_for_each_line_Traffic();
                                //busTime  busTime + bus.getMinute_gettingOn_gettingOff();
                                traffic_time  = true;
                            }
                            else
                            {
                                traffic_time  = false;
                            }
                            // busCost = bus.getCost_for_each_line_Traffic();
                            //busTime  busTime + bus.getMinute_gettingOn_gettingOff_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time = true;

                            }
                            else
                            {
                                traffic_time = false;
                            }
                            // subwayCost = subway.getCost_for_each_line_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time = true;

                            }
                            else
                            {
                                traffic_time = false;
                            }
                            // subwayCost = subway.getCost_for_each_line_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && 
                        stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                traffic_time = true;
                            }
                            else 
                            {
                                traffic_time = false;
                            }
                            // taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            //taxiCost = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                            || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                traffic_time = true;
                            }
                            else 
                            {
                                traffic_time = false;
                            }
                            // taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            //taxiTime = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                        if (parents[nearestVertex].first.first.getBusStatus()
                        && parents[nearestVertex].first.first.getBus_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed+= bus.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getBusStatus()
                        && parents[nearestVertex].first.first.getBus_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed+= bus.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }

                        }
                        //minute_passed += bus.getMinute_gettingOn_gettingOff();
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
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && 
                        stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        if (parents[nearestVertex].first.first.getTaxiStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                            
                        }
                        else
                        {
                            
                            minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());

                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getTaxiStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += taxi.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed  += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                        }
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                if (by_subway)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        if (parents[nearestVertex].first.first.getSubwayStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                               minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getSubwayStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += subway.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                
                costDijkstraList[vertexIndex] = lowestCost + weight;
            }
        }
    }
}


void LowestCost::printDijkstraOnCost(std::vector <Station>* stations)
{
    for (int i = 0; i < N; i++)
    {
        cout << (*stations)[i].GetName() <<"    " << costDijkstraList[i]<<'\n';
    }
    
}

void LowestCost::print_cost(int currentVertex, vector<Station>* S,pair<pair<Cost,int>,pair<int,int>>* parent)
{
    Bus bus;
    Subway subway;
    Taxi taxi;
    if (parent[currentVertex].second.second == -1) {
        return;
    }
    print_cost(parent[currentVertex].second.second,S,parent);
    if(parent[currentVertex].first.first.getBusStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parent[currentVertex].first.first.getBus_Line()<<" , Bus ) " << '\n';
    }
    else if(parent[currentVertex].first.first.getSubwayStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parent[currentVertex].first.first.getSubway_Taxi_Line()<<" , Subway ) "<<'\n';
    }
    else if(parent[currentVertex].first.first.getTaxiStatus())
    {
        cout<<(*S)[currentVertex].GetName() << " ( "
        <<parent[currentVertex].first.first.getSubway_Taxi_Line()<<" , Taxi ) "<<'\n';
    }
}

void LowestCost::print_path_cost(std::vector<Station> * S,int origin,int destination)
{

    for (int vertexIndex = 0; vertexIndex < N; vertexIndex++) 
    {
        if (vertexIndex != origin && vertexIndex == destination) {
            // cout << "\n" << (*S)[origin].GetName() << " -> ";
            // cout << (*S)[vertexIndex].GetName() << "   Shortest-Distance : "  
            // << costDijkstraList[vertexIndex] << '\n'<< '\n';
            // print_cost(vertexIndex,destination,S);
            // std::cout << '\n';
            // cout << "Arriving Time : ";
            //arriving_time.printTime();
        }
    }

}
int LowestCost::getIndexFromParents(int i,int currentVertex)
{
    if (parents[currentVertex].second.second == i)
    {
        return currentVertex;
    }
    getIndexFromParents(i,parents[currentVertex].second.second);
}
pair<pair<Cost,int>,pair<int,int>>* LowestCost::getParents()
{
    return parents;
}
int * LowestCost::getCostDijkstraList()
{
    return costDijkstraList;   
}
void LowestCost::setArrivingTime(Time time)
{
    arriving_time = time;
}
Time LowestCost::getArrivingTime()
{
    return arriving_time;
}
void LowestCost::dijkstra(int source)
{
    delete[] parents;
    parents = new pair<pair<Cost,int>,pair<int,int>>[N];
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
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            busCost = bus.getCost_for_each_line_Traffic();
                        }
                        
                        
                    }
                    else
                    {
                        if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()).getHour())<8
                            || (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            busCost = bus.getCost_for_each_line_Traffic();
                        }
                        
                    }
                }

                if(subwayCost != 0)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            subwayCost = subway.getCost_for_each_line_Traffic();
                        }
                    }
                    else
                    {
                        if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()).getHour())<8
                            || (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            subwayCost = subway.getCost_for_each_line_Traffic();
                        }
                        
                    }
                }
                if(taxiCost != 0)
                {
                    
                    if (stoi(time_during_dijkstra.getHour()) >= 18 && stoi(time_during_dijkstra.getHour())<20
                        || (stoi(time_during_dijkstra.getHour()) == 20 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                                && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                        }
                    }
                    else
                    {
                        if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()).getHour()) == 20 
                                && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                        }
                        
                    }
                }
                busCost = busCost != 0 ? busCost : INT_MAX;
                taxiCost = taxiCost != 0 ? taxiCost : INT_MAX;
                subwayCost = subwayCost != 0 ? subwayCost : INT_MAX;
                if (busCost != INT_MAX && busCost < taxiCost && busCost < subwayCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        // minute_passed += bus.getMinute_gettingOn_gettingOff_Traffic();
                        // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                        if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            traffic_time  = true;
                        }
                        else
                        {
                            traffic_time  = false;
                        }
                        parents[nearestVertex].second.first = true;
                    }
                    else
                    {
                        // minute_passed += bus.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 
                            && stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour())<8
                            || (stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+ bus.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km_Traffic());
                            traffic_time = true;
                            parents[nearestVertex].second.first = true;
                        }
                        else
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance() * bus.getMinute_per_km());
                            traffic_time  = false;
                            parents[nearestVertex].second.first = false;
                        }

                    }
                    weight = busCost;
                    flag= true;
                    by_bus = true;
                    by_taxi = false;
                    by_subway = false;
                    parents[nearestVertex].first.first.setBusStatus(by_bus);
                    parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                    parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                    line = costMatrix[nearestVertex][vertexIndex].getBus_Line();
                    // parents[nearestVertex].first.first.setBus_Line(line);
                    // parents[nearestVertex].first.first.setSubway_Taxi_Line("");
                }
                if (taxiCost != INT_MAX && taxiCost < busCost && taxiCost < subwayCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 18 && stoi(time_during_dijkstra.getHour())<20
                        || (stoi(time_during_dijkstra.getHour()) == 20 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        // minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                        // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                        if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                                && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            traffic_time  = true;
                        }
                        else
                        {
                            traffic_time  = false;
                        }
                        parents[nearestVertex].second.first = true;
                    }
                    else
                    {
                        // minute_passed += taxi.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour() ) >= 18 && 
                            stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour())<20
                            || (stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getHour()) == 20 
                            && stoi((time_during_dijkstra+ taxi.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km_Traffic());
                            traffic_time = true;
                            parents[nearestVertex].second.first = true;
                        }
                        else
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * taxi.getMinute_per_km());
                            traffic_time  = false;
                            parents[nearestVertex].second.first = false;
                        }

                    }
                    weight = taxiCost;
                    flag= true;
                    by_bus = false;
                    by_taxi = true;
                    by_subway = false;
                    parents[nearestVertex].first.first.setBusStatus(by_bus);
                    parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                    parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                    // parents[nearestVertex].first.first.setBus_Line("");
                    // parents[nearestVertex].first.first.setSubway_Taxi_Line(line);
                }
                if (subwayCost != INT_MAX && subwayCost < taxiCost && subwayCost < busCost)
                {
                    if (stoi(time_during_dijkstra.getHour()) >= 6 && stoi(time_during_dijkstra.getHour())<8
                        || (stoi(time_during_dijkstra.getHour()) == 8 
                        && stoi(time_during_dijkstra.getMinute())==0))
                    {
                        // minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                        // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                        if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getHour())<8
                            || (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                        {
                            traffic_time  = true;
                        }
                        else
                        {
                            traffic_time  = false;
                        }
                        parents[nearestVertex].second.first = true;
                    }
                    else
                    {
                        // minute_passed += subway.getMinute_gettingOn_gettingOff();
                        if (stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour() ) >= 6 
                            && stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour())< 8
                            || (stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getHour()) == 8 
                            && stoi((time_during_dijkstra+ subway.getMinute_gettingOn_gettingOff()).getMinute())==0))
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km_Traffic());
                            traffic_time = true;
                            parents[nearestVertex].second.first = true;
                        }
                        else
                        {
                            // minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance() * subway.getMinute_per_km());
                            traffic_time  = false;
                            parents[nearestVertex].second.first = false;
                        }

                    }
                    weight = subwayCost;
                    flag= true;
                    by_bus = false;
                    by_taxi = false;
                    by_subway = true;
                    parents[nearestVertex].first.first.setBusStatus(by_bus);
                    parents[nearestVertex].first.first.setTaxiStatus(by_taxi);
                    parents[nearestVertex].first.first.setSubwayStatus(by_subway);
                    line = costMatrix[nearestVertex][vertexIndex].getSubway_Taxi_Line();
                    // parents[nearestVertex].first.first.setBus_Line("");
                    // parents[nearestVertex].first.first.setSubway_Taxi_Line(line);
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
                        if (stoi((time_during_dijkstra + parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff_Traffic() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                busCost = bus.getCost_for_each_line_Traffic();
                                //busTime  busTime + bus.getMinute_gettingOn_gettingOff();
                                traffic_time  = true;
                            }
                            else
                            {
                                traffic_time  = false;
                            }
                            
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time = true;

                            }
                            else
                            {
                                traffic_time = false;
                            }
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                subwayCost = subway.getCost_for_each_line_Traffic();
                                traffic_time = true;

                            }
                            else
                            {
                                traffic_time = false;
                            }
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && 
                        stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                traffic_time = true;
                            }
                            else 
                            {
                                traffic_time = false;
                            }
                            //taxiCost = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                        if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                        {
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                            && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                            || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                
                                taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                                traffic_time = true;
                            }
                            else 
                            {
                                traffic_time = false;
                            }
                            // taxiCost = taxiCost * taxi_cost_coefficient_traffic;
                            //taxiTime = taxiTime + taxi.getMinute_gettingOn_gettingOff_Traffic();
                            // traffic_time = true;
                        }
                        else
                        {
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
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
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 &&
                         stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                         || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        // minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                        if (parents[nearestVertex].first.first.getBusStatus()
                        && parents[nearestVertex].first.first.getBus_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                        }
                        else
                        {
                            
                            
                            minute_passed += bus.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second +bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 6 
                            && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+bus.getMinute_gettingOn_gettingOff_Traffic()).getHour())< 8 
                            || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+bus.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 8 &&
                             stoi((time_during_dijkstra+ parents[nearestVertex].first.second+bus.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                            // if (nearestVertex == source)
                            // {
                            //     cout << "in else "<< minute_passed << " index " << vertexIndex << '\n';
                            //     (time_during_dijkstra + 30).printTime();
                            //     // cout  << time_during_dijkstra.getHour()<<" "<<parents[nearestVertex].first.second <<" "<<bus.getMinute_gettingOn_gettingOff_Traffic() <<'\n';
                            //     cout  << stoi((time_during_dijkstra+ parents[nearestVertex].first.second +bus.getMinute_gettingOn_gettingOff_Traffic()).getHour())<<'\n';
                            // }
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getBusStatus()
                        && parents[nearestVertex].first.first.getBus_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += bus.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + bus.getMinute_gettingOn_gettingOff() + parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+bus.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed+= (costMatrix[nearestVertex][vertexIndex].getBusDistance()*bus.getMinute_per_km());
                            }
                        }
                        //minute_passed += bus.getMinute_gettingOn_gettingOff();
                    }
                    parents[vertexIndex].first.first.setBus_Line(line);
                    parents[vertexIndex].first.first.setSubway_Taxi_Line("");
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                else if (by_taxi || by_subway)
                {
                    parents[vertexIndex].first.first.setBus_Line("");
                    parents[vertexIndex].first.first.setSubway_Taxi_Line(line);
                }
                if (by_taxi)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 18 && 
                        stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        if (parents[nearestVertex].first.first.getTaxiStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                            
                        }
                        else
                        {
                            minute_passed += taxi.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second + taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) >= 18 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour())<20
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getHour()) == 20 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second+ taxi.getMinute_gettingOn_gettingOff_Traffic()).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());

                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getTaxiStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += taxi.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 18 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<20
                            || (stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 20 
                            && stoi((time_during_dijkstra+taxi.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed  += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*taxi.getMinute_per_km());
                            }
                        }
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                if (by_subway)
                {
                    if (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) >= 6 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour())<8
                        || (stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getHour()) == 8 
                        && stoi((time_during_dijkstra+ parents[nearestVertex].first.second).getMinute())==0))
                    {
                        if (parents[nearestVertex].first.first.getSubwayStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                               minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += subway.getMinute_gettingOn_gettingOff_Traffic();
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff_Traffic()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                           
                        }
                        
                    }
                    else
                    {
                        if (parents[nearestVertex].first.first.getSubwayStatus()
                        && parents[nearestVertex].first.first.getSubway_Taxi_Line() == line)
                        {
                            if (parents[nearestVertex].second.first)
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        else
                        {
                            minute_passed += subway.getMinute_gettingOn_gettingOff();
                            if (stoi((time_during_dijkstra + subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) >= 6 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour())<8
                            || (stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getHour()) == 8 
                            && stoi((time_during_dijkstra+subway.getMinute_gettingOn_gettingOff()+ parents[nearestVertex].first.second).getMinute())==0))
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km_Traffic());
                            }
                            else
                            {
                                minute_passed += (costMatrix[nearestVertex][vertexIndex].getTrainTaxiDistance()*subway.getMinute_per_km());
                            }
                        }
                        
                    }
                    parents[vertexIndex].first.second = minute_passed + parents[nearestVertex].first.second;
                }
                
                costDijkstraList[vertexIndex] = lowestCost + weight;
            }
        }
    }
}