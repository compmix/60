// Author: Jacqueline Barcena, Felix Ng
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"
#include "BinaryHeap.h"

class MaxFinder
{
public:
	Computer *source, drain, *terminals, *others;

	MaxFinder(const Computer *comps, int numComputers, int numTerminals);
	int calcMaxFlow(Edge *edges, int numEdges);
}; // class MaxFinder




#endif
