// Author: Jacqueline Barcena, Felix Ng
#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "BinaryHeap.h"
#include "QuadraticProbing.h"
#include "LinkedList.h"
#include "vector.h"

using namespace std;


MaxFinder::MaxFinder(const Computer *comps, int numComps, int numTerms) {
	numComputers = numComps;
	numTerminals = numTerms;
	terminals = new Vertex[numTerminals];
	others = new Vertex[numComputers - numTerminals - 1];
	short v = 0;

	vertices = new QuadraticHashTable<Vertex> (source, numComputers * 2);

	// 1. store computers address into int
	// 2. store vertices into hash

		// store Terminals
		cout << numComputers << " " << numTerminals << endl;
		for (int i = 0; i < numTerminals ; ++i) {
			terminals[i] = comps[i];
			terminals[i].index = v++;
			cout << "Inserting: " << terminals[i].index << " " << terminals[i].intAddr << " " << comps[i].address << endl;
			original.insert(terminals[i]);
			vertices->insert(terminals[i]);
			

			// create source to terminals edges
			Edge2 tmpEdge;
			tmpEdge.capacity = -1;
			tmpEdge.dest = terminals[i].index;
			tmpEdge.destAddr = char2LongIP(comps[i].address);
			source.edges.insert(tmpEdge);

		}

		// store normal computers
		for (int i = 0; i < numComputers - numTerminals - 1; ++i) {
			others[i] = comps[numTerminals + i];
			others[i].index = v++;
			cout << "Inserting: " << others[i].index << " " << others[i].intAddr << " " << comps[numTerminals + i].address << endl;
			original.insert(others[i]);
			vertices->insert(others[i]);

		}

		// store drain computer
		drain = comps[numComputers-1];
		drain.index = v++;
		cout << "Inserting: " << drain.index << " " << drain.intAddr << " " << comps[numComputers - 1].address << endl;
		original.insert(drain);
		vertices->insert(drain);


	// use the index to detect similar ip address, eg 11.1.1.1 and 1.11.1.1 both have intAddr 11111
} // MaxFinder()

long MaxFinder::char2LongIP(char const *address) {
	long intAddr = 0;

	for (int i = 0; address[i] != '\0'; ++i) {
                    if(address[i] == '.') continue;

                    intAddr = intAddr*10 + address[i] - '0';
    }

    return intAddr;
} // char2LongIP

void MaxFinder::findMaxPath(Vector<Vertex> graph) {
/*
// Dijkstra's Algorithm (Max)
0. table of vertices with dv, pv
1. v = findMax && v is unknown
2. mark v as known
3. update all adjacent vertices of v
	a. dv_w, pv_w
	b. dv_w = max(dv_w, dv_v + c_vw)
*/
	// 0. table of vertices with dv, pv
	bool *kn = new bool[graph.size()];
	int *dv = new int[graph.size()];
	int *pv = new int[graph.size()];
	BinaryHeap<Edge2> vertexHeap;

	memset(kn, 0, graph.size() * sizeof(bool));
	memset(dv, 0, graph.size() * sizeof(int));
	memset(pv, 0, graph.size() * sizeof(int));


	// 1. start from the source, push vertices into heap, update tables
	for(int i = 0; i < source.edges.size(); ++i) {
		vertexHeap.insert(source.edges[i]);
		dv[source.edges[i].dest] = 0;
		pv[source.edges[i].dest] = -1;
		cout << "dv: " << dv[i] << " pv: " << pv[i] << endl;
	}

	for(int i = 0; i < numComputers; ++i) {
		//cout << "dv: " << dv[i] << " pv: " << pv[i] << endl;
	}


	while(!vertexHeap.isEmpty()) {
	
	Edge2 tmpEdge = vertexHeap.deleteMax();

	if(kn[tmpEdge.dest] == 1) continue;

		// 2. take biggest vertex, mark as known
		Vertex currentVertex = graph[tmpEdge.dest];
		kn[currentVertex.index] = 1;
		cout << tmpEdge.dest << " is now known. Checking edges" << endl;

		// 3. update all adjacent vertices of v
		for(int i = 0; i < currentVertex.edges.size() ; ++i) {
			vertexHeap.insert(currentVertex.edges[i]);

			// update vertices if dv is bigger than current one
			cout << dv[currentVertex.edges[i].dest] << endl;
			if(dv[currentVertex.edges[i].dest] < currentVertex.edges[i].capacity + dv[currentVertex.index]) {
				dv[currentVertex.edges[i].dest] = currentVertex.edges[i].capacity + dv[currentVertex.index];
				pv[currentVertex.edges[i].dest] = currentVertex.index;
			}
			cout << "dv: " << dv[currentVertex.edges[i].dest] << " pv: " << pv[currentVertex.edges[i].dest] << endl;
		}

		// 4. repeat until all true

	} // while stuff in heap

}

int MaxFinder::calcMaxFlow(Edge *edges, int numEdges) {

	// 0. store edge information within vertices
	for(int i = 0; i < numEdges; ++i) {
		Vertex src, dest;
		Edge2 tmpEdge;

		src.intAddr = char2LongIP(edges[i].src);
		dest.intAddr = char2LongIP(edges[i].dest);

		src = vertices->find(src);
		dest = vertices->find(dest);
		vertices->remove(src);
		vertices->remove(dest);
		
		// store forward edges
		tmpEdge.capacity = edges[i].capacity;
		tmpEdge.dest = dest.index;
		tmpEdge.destAddr = dest.intAddr;
		src.edges.insert(tmpEdge);
		original[src.index] = src;

		// store back edges
		tmpEdge.capacity = 0;
		tmpEdge.dest = src.index;
		tmpEdge.destAddr = src.intAddr;
		dest.edges.insert(tmpEdge);
		original[dest.index] = src;

		// update hash table
		vertices->insert(src);
		vertices->insert(dest);
		
		cout << "src index: " << src.index << " -> " << dest.index << endl;
		//cout << dest.edges[src.edges.end()].dest << " -> " << src.edges[src.edges.end()].dest << endl; 
	}


	// Ford-Fulkerson
	residual = original; 		// set G_r = G


	// find a MaxPath p from s to t in G_r
	findMaxPath(residual);




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