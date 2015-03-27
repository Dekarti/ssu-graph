#include <iostream>
#include <fstream>
#include <vector>
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

/*int cycle_st, cycle_end;

bool dfs (Graph &graph, int v, map<int, char> &used, map<int, char> &color) {
		color[v] = 1;
		for(map<Vertex*, int>::iterator it = graph[v]->adjMap.begin();
										it != graph[v]->adjMap.end();
										it ++) {
			int to = it->first->index;
			if (color[to] == 0) {
				used[to] = v;
				if (dfs (graph, to, used, color))
					return true;
			}
			else if (color[to] == 1) {
				cycle_end = v;
				cycle_st = to;
				return true;
			}
		}
		color[v] = 2;
		return false;
}*/

bool DFS(Graph &graph, int id, map<int, char> &color, vector<int> &p) {
	p.push_back(id);
	color.insert(make_pair(id, 1));
	for(map<Vertex*, int>::iterator it = graph[id]->adjMap.begin();
									it != graph[id]->adjMap.end();
									it++) {
		if (color[it->first->index] == 1) {
			return false;
		}
		else if (color[it->first->index] == 0 && DFS(graph, id, color, p)) {
			return true;
		} 
	}
	color[id] = 2;
	return true;
}

// Найти все кратчайшие циклы орграфа
void task6_32() {
	Graph graph;
	graph.scan("task6_32");
	map<int, char> color;
	vector<int> p;
	for (int i = 0; i < graph.size(); i++) {
		color.insert(make_pair(graph[i]->index, '0'));
	}

	DFS(graph, 1, color, p);

	for (int i = 0; i < p.size(); i++) {
		cout << p[i] << " ";
	}



	/*vector<int> cycle;
	cycle.push_back(cycle_st);
	for (int v = cycle_end; v != cycle_st; v = used[v])
		cycle.push_back(v);
	cycle.push_back(cycle_st);
	reverse(cycle.begin(), cycle.end());
	for (size_t i = 0; i < cycle.size(); ++i)
		cout << cycle[i] + 1 << " ";*/
}