// Author: Jacqueline Barcena, Felix Ng
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "LinkedList.h"

using namespace std;

MaxFinder::MaxFinder(const Computer *comps, int numComputers, int numTerminals) {
	source = new Vertex;
	drain = new Vertex;
	terminals = new Vertex[numTerminals];
	others = new Vertex[numComputers - numTerminals - 1];
	short v = 0;

	vertices = new QuadraticHashTable<Vertex> (*source, numComputers * 2);

	// 1. store computers address into int
	// 2. store vertices into hash

		//cout << numComputers << " " << numTerminals << endl;
		for (int i = 0; i < numTerminals ; i++) {
			terminals[i] = comps[i];
			terminals[i].index = v++;
			vertices->insert(terminals[i]);
			cout << terminals[i].index << " " << terminals[i].intAddr << endl;
		}

		for (int i = 0; i < numComputers - numTerminals - 1; i++) {
			others[i] = comps[numTerminals + i];
			others[i].index = v++;
			vertices->insert(others[i]);
			cout << others[i].index << " " << others[i].intAddr << endl;
		}

		*drain = comps[numComputers-1];
		drain->index = v++;
		vertices->insert(*drain);
		cout << drain->index << " " << drain->intAddr << endl;

	
	








} // MaxFinder()

void MaxFinder::findMaxPath(Edge *graph) {

}

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges) {
	// edges holds G
	// create G_r = G and G_f = empty;

	Edge *residual = new Edge[numEdges];

	for(int i = 0; i < numEdges; i++) {
		residual[i] = edges[i];
	}

	// find a MaxPath p from s to t in G_r


	// first, need to create back edges



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