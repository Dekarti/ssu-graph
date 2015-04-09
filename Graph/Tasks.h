#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Graph.h"
#include "Vertex.h"

using namespace std;

/*
 * ����� ����������� ������ ������ ������� ������� 
 */
void taskIa_3() {
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

/*
 * ������� �� ����� ������ �������
 */
void taskIa_25() {
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

/*
 * ������� ������ ��������� �������,
 * ����������� ������������ ���� ��������.
 */
void taskIb_6() {
	Graph graph1; graph1.scan("input1.txt");
	Graph graph2; graph2.scan("input2.txt");
	Graph graph3 = intersection(graph1, graph2);
	graph3.show();
}

/*
 * ��������, �������� �� ������ ������ �������.
 */
void taskII_14() {
	Graph graph;
	//graph.scan("task4_14.txt");
	cout << ((graph.isConnected())? "Yes\n" : "No\n");
	/*graph.addEdge(1, 3, 0);
	graph.removeEdge(2, 3);
	graph.addEdge(2, 1, 0);
	graph.addVertex(4);*/
	cout << ((graph.isConnected())? "Yes\n" : "No\n");
}

/*
 * ���������, ����� �� �� ����� �������
 * �����-���� ������� ���, ����� ���������� ������.
 */
void taskII_21() {
	NonOrGraph graph;
	bool foo = false;
	graph.scan("task5_21.txt");
	for (int i = 0; i < graph.size(); i++) {
		graph.removeVertex(graph.size() - i - 1);
		if (graph.isTree()) {
			foo = true;
		}
		graph.addVertex(graph.size() - i - 1);
	}
	cout << (foo ? "Yes\n" : "No\n");
}

map<int, int> BFS(Graph &graph, int start, queue<int> &q, map<int, char> &used) {
	vector<int> cicle;
	map<int, int> parents;
	bool breakFlag = false;
	q.push(start);
	used[start] = 1;
	parents.insert(make_pair(start, -1));
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for(map<Vertex*, int>::iterator it = graph[v]->adjMap.begin();
										it != graph[v]->adjMap.end();
										it ++) {
			int to = it->first->index;
			if (to == start) {
				parents[to] = v;
				breakFlag = true;
				break;
			}
			if (used[to] == 0) {
				used[to] = 1;
				q.push(to);
				parents.insert(make_pair(to, v));
			}
		}
		if (breakFlag)
			break;
	}
	return parents;
}

/*
 * ����� ��� ���������� ����� �������
 */
void taskII_32() {
	Graph graph;
	graph.scan("task6_32.txt");
	vector<Vertex*> vertices = graph.vertices();

	for (int i = 0; i < graph.size(); i++) {
		queue<int> q;
		map<int, char> used;
		for (int i = 0; i < graph.size(); i++) {
			used.insert(make_pair(vertices[i]->index, 0));
		}
		map<int, int> parents = BFS(graph, vertices[i]->index, q, used);

		vector<int> cicle;
		int v = parents[vertices[i]->index];
		cicle.push_back(vertices[i]->index);
		while (v != vertices[i]->index) {
			cicle.push_back(v);
			v = parents[v];
		}
		cicle.push_back(vertices[i]->index);
		for (int i = cicle.size() - 1; i >= 0; i--)
			cout << cicle[i] << (!i? "" : " -> ");
		cout << endl;
	}
}

/*
 * ��� ���������� ����������������� ���� �� N ������ � M �����.
 * ��������� ����� � ��� ������ ������������ ����. �������� ��������.
 */
void taskIII() {}

/*
 * �������������� ������� - ������������ ���������� �� ���� �����������
 * ���������� �� ������ ������ �� ������ �������.
 * ����� ������ ����� - ����������� �� ���������������� ��� ������.
 *
 *		a. � ����� ��� ����� �������������� ����.
 *
 */
void taskIV_11a() {}

/*
 * ������� ����� ���������� ����� �� u �� v1 � v2.
 *
 *		b. � ����� ��� ������ �������������� ����.
 *
 */
void taskIV_4b() {}

/*
 * ������� ���������� ���� �� ������� u �� ������� v.
 *
 *		c. � ����� ����� ���� ����� �������������� ����.
 *
 */
void taskIV_12c() {}



