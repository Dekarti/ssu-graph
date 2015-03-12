#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"

using namespace std;

void task1_3() {
// task 3
	Graph graph1;
	cout << "Task 3: " << endl << endl;
	graph1.scan("input1.txt");
	graph1.show();
	int vertex_id;

	cout << "Enter vertex index: ";
	cin  >> vertex_id;
	cout << "Indegree of vertex "
		 << vertex_id << ": "
		 << graph1.indegree(vertex_id)
		 << endl;
}