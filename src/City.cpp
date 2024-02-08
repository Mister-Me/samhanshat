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
                        if((*path)[k].getBusDistance() != 0)
                        {
                            temp.setBusDistance((*path)[k].getBusDistance());
                            temp.setTrainTaxiDistance(0);
                        }
                        else if ((*path)[k].getTrainTaxiDistance() != 0)
                        {
                            temp.setBusDistance(0);
                            temp.setTrainTaxiDistance((*path)[k].getTrainTaxiDistance());
                        }
                        else
                        {
                            temp.setBusDistance(0);
                            temp.setTrainTaxiDistance(0);
                        }
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
             << "   " << adjMatrix[i][j].getTrainTaxiDistance() << ","<<adjMatrix[i][j].getBusDistance()<<'\n';
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

void City::Dijkstra(int source)
{
    bool sptSet[N]; 
    // sptSet[i] will be true if vertex i is
    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
 
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < N; i++)
        dijkstraList[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dijkstraList[source] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < N - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = MinDistance(dijkstraList, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < N; v++)
        {
            int weight=0;
            bool flag = false; // check existing path
            if(adjMatrix[u][v].getBusDistance()!=0 )
            {
                weight = adjMatrix[u][v].getBusDistance();
                flag= true;
            }
            else if(adjMatrix[u][v].getTrainTaxiDistance()!=0)
            {
                weight = adjMatrix[u][v].getTrainTaxiDistance();
                flag = true;
            }
            else
            {
                flag = false;
            }
            if (!sptSet[v] && flag
                && dijkstraList[u] != INT_MAX
                && dijkstraList[u] + weight < dijkstraList[v])
                dijkstraList[v] = dijkstraList[u] + weight;
        }
    }
}
void City::PrintPath(vector<Station> * S)
{
    for (int i = 0; i < N; i++)
    {
        cout << (*S)[i].GetName() << "  Distance :  " << dijkstraList[i] << '\n';
    }
    
}