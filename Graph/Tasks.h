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
	graph.scan("taskII_21.txt");
	graph.show();
	for (int i = 0; i < graph.size(); i++) {
		graph.removeVertex(i);
		//graph.show();
		if (graph.isTree()) {
			foo = true;
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
		graph.scan("taskII_21.txt");
	}
	//cout << (foo ? "Yes\n" : "No\n");
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

bool isPermutation(vector<int> vec1tmp, vector<int> vec2tmp) {

	std::sort(vec1tmp.begin(), vec1tmp.end());
	std::sort(vec2tmp.begin(), vec2tmp.end());

	return (vec1tmp == vec2tmp);

}

/*
 * ����� ��� ���������� ����� ������� (not approved) 
 */
void taskII_32() {
	Graph graph;
	graph.scan("taskII_32.txt");
	graph.show();
	vector<Vertex*> vertices = graph.vertices();
	vector < vector <int> > cicles(0);

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

		
		bool permutation = false;
		for (int i = 0; i < cicles.size(); i++) {
			if (isPermutation(cicle, cicles[i]))
				permutation = true;
		}

		if (!permutation) {
			cicles.push_back(cicle);
		}
	}

	for (int i = 0; i < cicles.size(); i++) {
		for (int j = cicles[i].size() - 1; j >= 0; j--) {
			cout << cicles[i].at(j) << " -> ";
		}
		cout << cicles[i].at(cicles[i].size() - 1);
		cout << endl;
	}

}

/*
 * ��� ���������� ����������������� ���� �� N ������ � M �����.
 * ��������� ����� � ��� ������ ������������ ����. �������� ��������.
 */
void taskIII() {

	NonOrGraph graph;
	graph.scan("taskIII.txt");
	graph.show();
	vector<Vertex*> vertices = graph.vertices();
	vector <pair<int, pair<int, int>>> edges;



	for (int i = 0; i < graph.size(); i++) {
		for(map<Vertex*, int>::iterator it = vertices[i]->adjMap.begin();
										it != vertices[i]->adjMap.end();
										it ++) {
			edges.push_back(make_pair(
					vertices[i]->index,
					make_pair(it->first->index, it->second)
				)
			);
		}
	}

	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].first << "-" << edges[i].second.first <<  " | " << edges[i].second.second << endl;
	}
}

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



