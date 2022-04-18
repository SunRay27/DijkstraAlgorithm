#pragma once
#include "Collections.h"

class DijkstraNode
{
private:
    List<DijkstraNode*> neighbours;
    List<long> costs;
public:
    DijkstraNode* pathFrom;
    size_t distance;
    String name;

    DijkstraNode(const String& name)
    {
        pathFrom = nullptr;
        distance = 0;
        this->name = name;
    }
    
    //cities have unique names?
    //in my world - yes
    //therefore there i no need in unique IDs
    bool operator==(DijkstraNode& toCompare)
    {
        return this->name == toCompare.name;
    }
    bool operator !=(DijkstraNode& toCompare)
    {
        return !(*this == toCompare);
    }
    friend bool operator<(DijkstraNode& l, DijkstraNode& r)
    { 
        return l.distance < r.distance; 
    }
    friend bool operator>(DijkstraNode& l, DijkstraNode& r)
    {
        return l.distance > r.distance;
    }
    long GetTravelCost(size_t neighborIndex)
    {
        return costs[neighborIndex];
    }

    void AddNeighbor(DijkstraNode* neighbor, size_t travelCost)
    {
        neighbours.Add(neighbor);
        costs.Add(travelCost);
    }
    DijkstraNode* GetNeighour(size_t neighborIndex)
    {
        return neighbours[neighborIndex];
    }
    size_t GetNeighboursCount()
    {
        return neighbours.Count();
    }
    bool ContainsNeighbor(DijkstraNode* neighbor)
    {
        return neighbours.Contains(neighbor);
    }
};