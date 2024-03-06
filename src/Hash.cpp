#include "../include/Hash.hpp"
#include <iostream>
Hash::Hash()
{
    for (int i = 0; i < N; i++)
    {
        hashTable[i].SetName("");
    }
}
 int Hash::hashFunction(Station station)
{
    int sum = 0;
    int key = -1;
    for (int i = 0; i < station.GetName().size(); i++)
    {
        sum += station.GetName()[i];
    }
    int i = 1;
    key = sum % N;
    while(hashTable[key].GetName() != "")
    {
        key = key + ((3*i)%N);
        key = key % N;
        i++;
    }
    if (i > maximum_i)
    {
        maximum_i = i;
    }
    hashTable[key] = station;
    return key;
}
int Hash::returnKey(std::string station)
{
    int sum = 0;
    int key = -1;
    for (int i = 0; i < station.size(); i++)
    {
        sum += station[i];
    }
    int i = 0;
    key = sum % N ;
    while(hashTable[key].GetName() != station)
    {
        if (i > maximum_i)
        {
            return -1;
        }
        key = key + ((3*i)%N);
        key = key % N;
        i++;
    }
    return key;
}
int Hash::getMaximumI()
{
    std::cout << maximum_i << std::endl;
}