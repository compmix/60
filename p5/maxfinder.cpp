// Author: Jacqueline Barcena, Felix Ng
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "BinaryHeap.h"

using namespace std;

MaxFinder::MaxFinder(const Computer *comps, int numComputers,
  int numTerminals)
{
	source = new Computer;
	terminals = new Computer[numTerminals];
	others = new Computer[numComputers - numTerminals - 1];


	cout << numComputers << " " << numTerminals << endl;

	for (int i = 0; i < numTerminals ; i++) {
		terminals[i] = comps[i];
		cout << terminals[i].address << endl;
	}

	for (int i = 0; i < numComputers - numTerminals - 1; i++) {
		others[i] = comps[numTerminals + i];
		cout << others[i].address << endl;
	}

	*source = comps[numComputers-1];

	cout << source->address << endl;


} // MaxFinder()


int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{
  return 0;  // bad result :(
} // calcMaxFlow()



/*
Tips:
- use Ford-Fulkerson
- dijkstra with maxHeap
- modify weiss code to work faster


Ford-Fulkerson
0. set G_r = G
1. find a MaxPath p from source s to drain t in G_r
	a. use Dijkstra's longest path algorithm
2. Remove p from G_r
	a. decrease flow from forward edge
	b. increase flow from backward edge
3. Add p to G_f
4. Repeat 1-3


Dijkstra's Algorithm (Max)
0. table of vertices with dv, pv
1. v = findMax && v is unknown
2. mark v as known
3. update all adjacent vertices of v
	a. dv_w, pv_w
	b. dv_w = max(dv_w, dv_v + c_vw)



*/