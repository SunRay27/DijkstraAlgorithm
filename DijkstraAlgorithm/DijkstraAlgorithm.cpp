using namespace std;
#include <iostream>
#include "DijkstraPathfinder.h"


int main()
{
	SetConsoleOutputCP(1251);

	//make sure that nodes.txt is written in cyrillic windows (1 byte per char)
	String fileName = "nodes.txt";

	//it just works @Todd Howard
	//as always - no leaks 
	DijkstraPathfinder graph(fileName);

	//find all paths from all nodes to all nodes
	for (size_t i = 0; i < graph.GetNodeCount(); i++)
		for (size_t j = 0; j < graph.GetNodeCount(); j++)
			graph.FindPath(i, j);

}



