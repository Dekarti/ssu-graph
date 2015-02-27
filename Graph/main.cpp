#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "NonOrGraph.h"
#include "Vertex.h"

using namespace std;

int main() {

	/*
// task 3
	cout << "Task 3: " << endl << endl;
	Graph graph1;
	graph1.addVertex(5);
	graph1.addVertex(9);
	graph1.addVertex(7);
	graph1.addVertex(6);

	graph1.addEdge(5, 9, 1);
	graph1.addEdge(9, 7, 2);
	graph1.addEdge(7, 5, 3);
	graph1.addEdge(6, 7, 4);

	graph1.show();
	cout << "Indegree of vertex 7: " << graph1.indegree(7) << endl;

// task 25
	cout << endl << "Task 25: " << endl << endl;

	NonOrGraph graph2;
	graph2.addVertex(5);
	graph2.addVertex(9);
	graph2.addVertex(7);
	graph2.addVertex(6);

	graph2.addEdge(5, 9, 1);
	graph2.addEdge(9, 7, 2);
	graph2.addEdge(7, 5, 3);
	graph2.addEdge(6, 7, 4);

	graph2.show();
	graph2.removeVertex(7);
	cout << "After removing:" << endl;
	graph2.show();*/
	Graph graph;
	
	graph.scan("input.txt");
	graph.show();
	return 0;
}