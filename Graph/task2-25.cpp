#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"

using namespace std;

void task2_25() {
	cout << endl << "Task 25: "
		 << endl << endl;

	NonOrGraph graph2;
	graph2.scan("input1.txt");
	graph2.show();

	cout << "Enter vertex index: ";
	cin  >> vertex_id;

	graph2.removeVertex(vertex_id);
	cout << "After removing:" << endl;
	graph2.show();
}