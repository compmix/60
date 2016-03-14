// Author: Jacqueline Barcena, Felix Ng
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "LinkedList.h"
#include "vector.h"

using namespace std;


MaxFinder::MaxFinder(const Computer *comps, int numComputers, int numTerminals) {
	source = new Vertex;
	terminals = new Vertex[numTerminals];
	others = new Vertex[numComputers - numTerminals - 1];
	short v = 0;

	vertices = new QuadraticHashTable<Vertex> (*source, numComputers * 2);

	// 1. store computers address into int
	// 2. store vertices into hash

		cout << numComputers << " " << numTerminals << endl;
		for (int i = 0; i < numTerminals ; i++) {
			terminals[i] = comps[i];
			terminals[i].index = v++;
			cout << "Inserting: " << terminals[i].index << " " << terminals[i].intAddr << " " << comps[i].address << endl;
			vertices->insert(terminals[i]);
			
		}

		for (int i = 0; i < numComputers - numTerminals - 1; i++) {
			others[i] = comps[numTerminals + i];
			others[i].index = v++;
			cout << "Inserting: " << others[i].index << " " << others[i].intAddr << " " << comps[numTerminals + i].address << endl;
			vertices->insert(others[i]);
			
		}

		drain = comps[numComputers-1];
		drain.index = v++;
		cout << "Inserting: " << drain.index << " " << drain.intAddr << " " << comps[numComputers - 1].address << endl;
		vertices->insert(drain);
		

	// use the index to detect similar ip address, eg 11.1.1.1 and 1.11.1.1 both have intAddr 11111
} // MaxFinder()

long MaxFinder::char2LongIP(char *address) {
	long intAddr = 0;

	for (int i = 0; address[i] != '\0'; ++i) {
                    if(address[i] == '.') continue;

                    intAddr = intAddr*10 + address[i] - '0';
    }

    return intAddr;
}

void MaxFinder::findMaxPath(Edge *graph) {

}

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges) {

	// 1. store edge information within vertices
	for(int i = 0; i < numEdges; ++i) {
		Vertex src, dest;
		Edge2 tmpEdge;

		//cout << edges[i].src << " -> " << edges[i].dest << endl;
		src.intAddr = char2LongIP(edges[i].src);
		dest.intAddr = char2LongIP(edges[i].dest);

		src = vertices->find(src); 
		dest = vertices->find(dest);

		cout << "src index: " << src.index << " -> " << dest.index << endl;

		tmpEdge.capacity = edges[i].capacity;
		tmpEdge.dest = char2LongIP(edges[i].dest);

		src.edges.insert(tmpEdge);

		tmpEdge.capacity = 0;
		tmpEdge.dest = char2LongIP(edges[i].src);
		dest.edges.insert(tmpEdge);

		//src.edges.insert(&edges[i], src.edges.first());
		cout << dest.edges[src.edges.size() - 1].dest << " -> " << src.edges[src.edges.size() - 1].dest << endl;

	}




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