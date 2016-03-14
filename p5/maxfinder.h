// Author: Jacqueline Barcena, Felix Ng
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "LinkedList.h"
#include "vector.h"


class MaxFinder
{
public:
	Vertex *source, drain, *terminals, *others;

	QuadraticHashTable<Vertex> *vertices;

	MaxFinder(const Computer *comps, int numComputers, int numTerminals);
	long char2LongIP(char *address);
	void findMaxPath(Edge *graph);
	int calcMaxFlow(Edge *edges, int numEdges);
}; // class MaxFinder




#endif
