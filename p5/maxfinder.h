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
	int numComputers, numTerminals;

	Vector<Vertex> original, flow, residual;
	Vertex source, drain, *terminals, *others;

	QuadraticHashTable<Vertex> *vertices;

	MaxFinder(const Computer *comps, int numComputers, int numTerminals);
	long char2LongIP(char const *address);
	void findMaxPath(Vector<Vertex> graph);
	int calcMaxFlow(Edge *edges, int numEdges);
}; // class MaxFinder




#endif
