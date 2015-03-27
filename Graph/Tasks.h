#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Graph.h"
#include "Vertex.h"

using namespace std;


// Найти полустепень захода данной вершины орграфа 
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

// Удалить из графа данную вершину
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

// Вывести список смежности орграфа,
// являющегося пересечением двух заданных.
void task3_6() {
	Graph graph1; graph1.scan("input1.txt");
	Graph graph2; graph2.scan("input2.txt");
	Graph graph3 = intersection(graph1, graph2);
	graph3.show();
}

// Выяснить, является ли орграф сильно связным.
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

// Проверить, можно ли из графа удалить какую-либо вершину так,
// чтобы получилось дерево.
void task5_21() {
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

vector<int> BFS(Graph &graph, int start, queue<int> &q, map<int, char> &used) {
	vector<int> cicle;
	bool breakFlag = false;
	q.push(start);
	used[start] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		
		cicle.push_back(v);
		
		for(map<Vertex*, int>::iterator it = graph[v]->adjMap.begin();
										it != graph[v]->adjMap.end();
										it ++) {
			int to = it->first->index;
			if (to == start) {
				cicle.push_back(to);
				breakFlag = true;
				break;
			}
			if (used[to] == 0) {
				used[to] = 1;
				q.push(to);
			}
		}
		if (breakFlag)
			break;
	}
	return cicle;
}

// Найти все кратчайшие циклы орграфа
void task6_32() {
	Graph graph;
	graph.scan("task6_32.txt");
	vector<Vertex*> vertices = graph.vertices();

	for (int i = 0; i < graph.size(); i++) {
		queue<int> q;
		map<int, char> used;
		for (int i = 0; i < graph.size(); i++) {
			used.insert(make_pair(vertices[i]->index, 0));
		}
		vector<int> cicle = BFS(graph, vertices[i]->index, q, used);
		for (int j = 0; j < cicle.size(); j++) {
			cout << cicle[j] << " ";
		}
		cout << endl;
	}
}