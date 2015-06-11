#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Graph.h"
#include "Vertex.h"

#define INF 10e6

using namespace std;

/*
 * Найти полустепень захода данной вершины орграфа 
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

/******************************************************************************************/

/*
 * Удалить из графа данную вершину
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

/******************************************************************************************/

/*
 * Вывести список смежности орграфа,
 * являющегося пересечением двух заданных.
 */
void taskIb_6() {
	Graph graph1; graph1.scan("input1.txt");
	Graph graph2; graph2.scan("input2.txt");
	Graph graph3 = intersection(graph1, graph2);
	graph3.show();
}

/******************************************************************************************/

/*
 * Выяснить, является ли орграф сильно связным.
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
 * Проверить, можно ли из графа удалить
 * какую-либо вершину так, чтобы получилось дерево.
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

/******************************************************************************************/

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
 * Найти все кратчайшие циклы орграфа (not approved) 
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

/******************************************************************************************/

bool comparator(pair<int, pair<int, int>> o1, pair<int, pair<int, int>> o2) {
	
	if (o1.first < o2.first)
		return true;
	else
		return false;

}

/*
 * Дан взвешенный неориентированный граф из N вершин и M ребер.
 * Требуется найти в нем каркас минимального веса. Алгоритм Краскала.
 */ 

void taskIII() {

	NonOrGraph graph;
	graph.scan("taskIII.txt");
	graph.show();
	vector<Vertex*> vertices = graph.vertices();
	vector <pair<int, pair<int, int>>> edges = graph.edges();
	std::sort(edges.begin(), edges.end(), comparator);

	vector< pair<int, pair<int, int>> > result;

	vector<int> trees(graph.size());
	for (int i = 0; i < graph.size(); i++) {
		trees[i] = vertices[i]->index;
	}

	for (int i = 0; i < edges.size(); i++) {

		int a = edges[i].second.first;
		int b = edges[i].second.second;
		int l = edges[i].first;

		if (trees[a] != trees[b]) {
			result.push_back(make_pair(l, make_pair(a, b)));
			int oldID = trees[b];
			int newID = trees[a];
			for (int j = 0; j < graph.size(); ++j) {
				if (trees[j] == oldID) {
					trees[j] = newID;
				}
			}
		}
	}
	
	NonOrGraph mst; 
	for (int i = 0; i < result.size(); i++) {
		mst.addVertex(result[i].second.first);
		mst.addVertex(result[i].second.second);
		mst.addEdge(
			result[i].second.first,
			result[i].second.second,
			result[i].first
		);
	}
	mst.show();
}

/******************************************************************************************/

vector< vector<int> > floid(NonOrGraph graph) {

	vector<Vertex*> vertices = graph.vertices();
	vector <pair<int, pair<int, int>>> edges = graph.edges();
	vector< vector<int> > distances(graph.size(), vector<int>(graph.size(), 5000));
	
	for (int i = 0; i < graph.size(); i++) {
		distances[i][i] = 0; 
	}

	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first;
		int b = edges[i].second.second;
		int l = edges[i].first;

		distances[a][b] = l;
		distances[b][a] = 1;
	}

	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.size(); j++) {
			for (int k = 0; k < graph.size(); k++) {
				distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
			}
		}
	}

	return distances;

}

/*
 * Эксцентриситет вершины - максимальное расстояние из всех минимальных
 * расстояний от других вершин до данной вершины.
 * Найти радиус графа - минимальный из эксцентриситетов его вершин.
 *
 *		a. В графе нет ребер отрицательного веса.
 *
 */


void taskIV_11a() {

	NonOrGraph graph;
	graph.scan("taskIV_11a.txt");
	graph.show();
	vector< vector<int> > distances = floid(graph);
	vector<int> eccentricitys(graph.size());

	for (int i = 0; i < distances.size(); i++) {
		eccentricitys[i] = *max_element(distances[i].begin(), distances[i].end());
	}

	cout << "\n\n";

	for (int i = 0; i < graph.size(); i++) {
		cout << endl;
		for (int j = 0; j < graph.size(); j++) {
			cout << distances[i][j] << "\t";
		}
		cout << " | " << eccentricitys[i];
	}

	cout << "\n\n";

	cout << "Radius: " << *min_element(eccentricitys.begin(), eccentricitys.end()) << "\n\n\n";

}

/******************************************************************************************/

map<int, int> dijkstra(int start, NonOrGraph graph) {
	
	map<int, int> distances;
	vector<Vertex*> vertices = graph.vertices();

	for (int i = 0; i < vertices.size(); i++) {
		distances.insert(make_pair(vertices[i]->index, INF));
	}

	map<int, bool> used;

	for (int i = 0; i < vertices.size(); i++) {
		used.insert(make_pair(vertices[i]->index, false));
	}


	distances[start] = 0;

	for (int i = 0; i < graph.size(); i++) {

		int v = -1;

		for (int j = 0; j < graph.size(); j++) {
			if (!used[j] && (v == -1 || distances[j] < distances[v])) {
				v = j;
			}
		}

		used[v] = true;
 
		for(map<Vertex*, int>::iterator it = graph[v]->adjMap.begin();
										it != graph[v]->adjMap.end();
										it ++)
		{
			int to = it->first->index;
			int len = it->second;

			if (distances[v] + len < distances[to]) {
				distances[to] = distances[v] + len;
			}
		}
	}

	return distances;

}

/*
 * Вывести длины кратчайших путей от u до v1 и v2.
 *
 *		b. В графе нет циклов отрицательного веса.
 *
 */
void taskIV_4b() {

	NonOrGraph graph;
	graph.scan("taskIV_4b.txt");
	graph.show();

	int u; cout << " u = "; cin >> u;

	int v1, v2;
	cout << " v1 = "; cin >> v1; 
	cout << " v2 = "; cin >> v2;

	map<int, int> distances = dijkstra(u, graph);

	cout << " " << u << " -> " << v1 << " = " << distances[v1] << endl;
	cout << " " << u << " -> " << v2 << " = " << distances[v2] << endl;
	
}

/*
 * Вывести кратчайший путь из вершины u до вершины v.
 *
 *		c. В графе могут быть циклы отрицательного веса.
 *
 */
void taskIV_12c() {

}



