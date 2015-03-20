#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"
#include "Vertex.h"

using namespace std;


// ����� ����������� ������ ������ ������� ������� 
void task1_3() {
	Graph graph;
	cout << "Task 3: " << endl << endl;
	graph.scan("input.txt");
	graph.show();
	int vertex_id;

	cout << "Enter vertex index: ";
	cin  >> vertex_id;
	cout << "Indegree of vertex "
		 << vertex_id << ": "
		 << graph.indegree(vertex_id)
		 << endl;
}

// ������� �� ����� ������ �������
void task2_25() {
	cout << endl << "Task 25: "
		 << endl << endl;

	NonOrGraph graph;
	graph.scan("input.txt");
	graph.show();
	int vertex_id;

	cout << "Enter vertex index: ";
	cin  >> vertex_id;

	graph.removeVertex(vertex_id);
	cout << "After removing:" << endl;
	graph.show();
}

// ������� ������ ��������� �������,
// ����������� ������������ ���� ��������.
void task3_6() {
	Graph graph1; graph1.scan("input1.txt");
	Graph graph2; graph2.scan("input2.txt");
	Graph graph3 = intersection(graph1, graph2);
	graph3.show();
}

// ��������, �������� �� ������ ������ �������.
void task4_14() {
	Graph graph;
	//graph.scan("task4_14.txt");
	cout << ((graph.isConnected())? "Yes\n" : "No\n");
	/*graph.addEdge(1, 3, 0);
	graph.removeEdge(2, 3);
	graph.addEdge(2, 1, 0);
	graph.addVertex(4);*/
	cout << ((graph.isConnected())? "Yes\n" : "No\n");
}

// ���������, ����� �� �� ����� ������� �����-���� ������� ���,
// ����� ���������� ������.
void task5_21() {}