using namespace std;

#include "DijkstraNode.h"
#include <fstream>


#pragma once
class DijkstraPathfinder
{
private:
	List<DijkstraNode> nodes;

    void RegisterNodes(DijkstraNode& targetNode, DijkstraNode& neighbor, size_t cost)
    {
        if (cost == -1)
            return;

        int targetIndex = nodes.IndexOf(targetNode);
        int neighborIndex = nodes.IndexOf(neighbor);

        if (targetIndex != -1)
        {

            if (neighborIndex == -1)
            {
                nodes.Add(neighbor);
                neighborIndex = nodes.Count() - 1;
            }
        }
        else
        {
            //target node is not present, create it
            nodes.Add(targetNode);
            targetIndex = nodes.Count() - 1;

            if (neighborIndex == -1)
            {
                nodes.Add(neighbor);
                neighborIndex = nodes.Count() - 1;
            }
        }

        nodes[targetIndex].AddNeighbor(&nodes[neighborIndex], cost);
    }
    void PrintPathForNode(size_t toIndex)
    {
        DijkstraNode* currentNode = &nodes[toIndex];
        List<DijkstraNode*> pathList;
        while (currentNode != nullptr)
        {
            pathList.Add(currentNode);
            currentNode = currentNode->pathFrom;
        }
        pathList.Reverse();



            for (size_t i = 0; i < pathList.Count(); i++)
            {
                if (i != pathList.Count() - 1)
                    cout << pathList[i]->name << " " << pathList[i]->distance << " ---> ";
                else
                    cout << pathList[i]->name << " " << pathList[i]->distance << endl;
            }
            cout << endl;

    }
    int ParseTravelCost(String stringToParse)
    {
        //stringToParse.Trim();
        int result = -1;
        if (sscanf_s(stringToParse.GetArrayPointer(), "%i", &result) != 1)
        {
            if (stringToParse != "N/A")
            {
                //cerr << "Error: expected token integer type or <N/A>, got something else - " << stringToParse << endl;
                throw exception("expected token integer type or <N/A>, got something else");
            }
        }
        return result;
    }
    void ParseNodes(const String& txtFileName)
    {
        List<String> lines;

        //read from file
        ifstream inputStream;
        inputStream.open(txtFileName.GetArrayPointer());

        if (!inputStream)
            throw exception("file could not be opened");

        char readBuffer[128];
        while (!inputStream.eof())
        {
            inputStream.getline(readBuffer, 128, '\n');
            lines.Add(readBuffer);
        }
        inputStream.clear();
        inputStream.close();
        //now we have all file lines...

        //split lines and fill allNodes
        for (size_t i = 0; i < lines.Count(); i++)
        {
            List<String> parts = String::LazySplit((lines[i]), ';');

            if (parts.Count() != 4)
            {
                // cerr << "Error at line " << i + 1 << ": expected token count 4, got " << parts.Count() << endl;
                throw exception("invalid token count");
            }

            for (size_t i = 0; i < parts.Count(); i++)
                parts[i].Trim();

            String fromNodeName = parts[0];
            String toNodeName = parts[1];
            int directCost = ParseTravelCost(parts[2]);
            int reverseCost = ParseTravelCost(parts[3]);

            DijkstraNode targetNode(fromNodeName);
            DijkstraNode neighborNode(toNodeName);

            RegisterNodes(targetNode, neighborNode, directCost);
            RegisterNodes(neighborNode, targetNode, reverseCost);
        }

        cout << "\nCreated grid. Node count: " << nodes.Count() << endl;
        for (size_t i = 0; i < nodes.Count(); i++)
        {
            cout << i << ": " << nodes[i].name << endl;
            for (size_t j = 0; j < nodes[i].GetNeighboursCount(); j++)
                cout << "   --->" << nodes[i].GetNeighour(j)->name << " " << nodes[i].GetTravelCost(j) << endl;
        }
    }

public:

    size_t GetNodeCount()
    {
        return nodes.Count();
    }
    DijkstraPathfinder(const String& txtFileName)
	{
        ParseNodes(txtFileName);
	}
    long FindPath(size_t fromIndex, size_t toIndex)
    {
        if (fromIndex < 0 || fromIndex > nodes.Count() - 1 || toIndex < 0 || toIndex > nodes.Count() - 1)// || fromIndex == toIndex)
            throw invalid_argument("invalid index");

        //init distances
        for (size_t i = 0; i < nodes.Count(); i++)
            nodes[i].distance = SIZE_MAX;

        //init start node
        nodes[fromIndex].distance = 0;
        nodes[fromIndex].pathFrom = nullptr;

        Queue<DijkstraNode*> searchFronier;
        searchFronier.Enqueue(&nodes[fromIndex]);

        while (searchFronier.Count() > 0)
        {
            DijkstraNode* current = searchFronier.Dequeue();
            
            for (size_t i = 0; i < current->GetNeighboursCount(); i++)
            {
                DijkstraNode* neighbor = current->GetNeighour(i);
                size_t newDistance = current->distance + current->GetTravelCost(i);

                if (neighbor->distance == SIZE_MAX)
                {
                    neighbor->distance = newDistance;
                    neighbor->pathFrom = current;
                    searchFronier.Enqueue(neighbor);
                }
                else if (newDistance < neighbor->distance)
                {
                    neighbor->distance = newDistance;
                    neighbor->pathFrom = current;
                }
            }

            //sort frontier by distances?
            //no, its A* prerogative
            //why not A*?
        }

        if (nodes[toIndex].distance != SIZE_MAX)
        {
            cout << "Calculated path distance from " << nodes[fromIndex].name << " to " << nodes[toIndex].name << " is " << nodes[toIndex].distance << endl;
            PrintPathForNode(toIndex);
            return nodes[toIndex].distance;
        }
        else
        {
            cout << "Path from " << nodes[fromIndex].name << " to " << nodes[toIndex].name << " doen't exist " << endl << endl;
            return -1;
        }
        
        
    }
};

