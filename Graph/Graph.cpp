#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#define EXEPTION(reason, message) Exeption((reason), (message), __LINE__, __FUNCSIG__)

using namespace std;

/*------------------- EXEPTION DEFINING --------------------*/

Exeption::Exeption(int reason, string message, int line, string funcsig) {
	this->reason = reason;
	this->message = message;
	this->line = line;
	this->func = funcsig;
}

void Exeption::print() {
	cout << "EXEPTION: " << message << " | "
		 << reason << " | " << line << " | "
		 << func   << endl  << endl;
}

/*-------------------- GRAPH DEFINING -----------------------*/

int Graph::size() { return vertexList.size(); }

bool Graph::exists(int id) {
	for (int i = 0; i < size(); i++) {
		if (vertexList[i]->index == id) {
			return true;
			break;
		}
	}
	return false;
}

Vertex* Graph::getVertex(int id) {
	for (int i = 0; i < size();) {
		if (vertexList[i]->index == id) {
			return vertexList[i];
		}
		else if (i == size() - 1) { 
			throw EXEPTION(id, "no such element");
		}
		else {
			i++;
		}
	}
}

Vertex* Graph::operator [](int id) {
	try {
		return getVertex(id);
	}
	catch (Exeption e) {
		e.print();
	}
}

void Graph::addVertex(int id) { vertexList.push_back(new Vertex(id)); }

void Graph::addEdge(int from, int to, int weight) {
	try {
		Vertex* vertexTo;
		Vertex* vertexFrom;
		for (int i = 0; i < vertexList.size(); i++) {
			if (vertexList[i]->index == to)
				vertexTo = vertexList[i];
		}

		for (int i = 0; i < vertexList.size(); i++) {
			if (vertexList[i]->index == from) {
				vertexFrom = vertexList[i];
				if (!vertexFrom->isConnected(to)) {
					vertexFrom->adjMap.insert(pair<Vertex*, int>(vertexTo, weight));
				}
				else {
					throw EXEPTION(0, "edge between given vertices already exists");
				}
			}
		}
	}
	catch (Exeption e) {
		e.print();
	}
}

int Graph::getWeight(int from, int to) {
	try {
		return getVertex(from)->adjMap[getVertex(to)];
	}
	catch (Exeption e) {
		e.print();
	}
}

void Graph::show() {
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		vertexList[i]->print();
		cout << endl;
	}
}

void Graph::removeVertex(int removable_id) {

	Vertex* removable;
	try {
		removable = getVertex(removable_id);
		for (int i = 0; i < size(); i++) {
			vertexList[i]->breakEdge(removable);
		}

		int id = -1;
		for (int i = 0; i < size(); i++) {
			if (vertexList[i]->index == removable_id)
				id = i;
		}	
		if (id != -1)
			vertexList.erase(vertexList.begin() + id);
	}
	catch (Exeption e) {
		e.print();
	}
}

void Graph::removeEdge(int from_, int to_) {
	Vertex* from;
	Vertex* to;
	try {
		from = getVertex(from_);
		to = getVertex(to_);
		if (from->isConnected(to_)) {
			from->breakEdge(to);
		}
		else {
			throw EXEPTION(to_, "vertex is not adjacent to this");
		}
	}
	catch (Exeption e) {
		e.print();
	}
}

int Graph::indegree(int id) {
	int indegree = 0;
	try {
		Vertex* vertex = getVertex(id);
		for (int i = 0; i < size(); i++) {
			if (vertexList[i]->isConnected(id))
				indegree++;
		}
		return indegree;
	}
	catch (Exeption e) {
		e.print();
	}
}

void Graph::scan(string stringFileName) {
	wchar_t fileName[1024];
	for (int i = 0; i < stringFileName.size(); i++) {
		fileName[i] = stringFileName[i];
	}
	fileName[stringFileName.size()] = '\0';
	std::ifstream in;
	in.open(fileName);

	if (in.is_open()) {
		int i;
		std::string str;
		getline(in, str);
		std::stringstream s(str);
		while(s >> i) {
			addVertex(i);
		}

		getline(in, str);
		int from, to, weight;
		while(in) {
			std::stringstream s2(str);
			while (s2 >> from >> to >> weight) {
				addEdge(from, to, weight); 
			}
			getline(in, str);
		}
	}
}

vector<Vertex*> Graph::vertices() {
	return vertexList;
}

void Graph::dfs(int i, vector<bool> &used) {
    used[i] = true;
    map<Vertex*, int>::const_iterator iter;
    for(map<Vertex*, int>::iterator it = vertexList[i]->adjMap.begin();
									it != vertexList[i]->adjMap.end();
									it ++) {
        if (!used[it->first->index]) {
            dfs(it->first->index, used);
        }
    }
}

bool Graph::isConnected() {
	bool isConnected;
    vector<bool> used(vertexList.size(), 0);
	for (int i = 0; i < vertexList.size(); i++) {
		used.assign(used.size(), 0);
		dfs(vertexList[i]->index, used);
		for (int j = 0; j < used.size(); j++) {
			if(used[vertexList[j]->index] == false)
				return false;
		}
	}
    return true;
}

int Graph::edgesNumber() {
	int edgesCounter = 0;
	for (int i = 0; i < size(); i++) {
		edgesCounter += vertexList[i]->adjMap.size();
	}
	return edgesCounter;
}

bool Graph::isTree() {
	return isConnected() && (edgesNumber() == vertexList.size() - 1);
}

Graph intersection(Graph graph1, Graph graph2) {
	vector<Vertex*> graph1List = graph1.vertices(),
					graph2List = graph2.vertices();

	vector<int> sharedVertices;

	for (int i = 0; i < graph1List.size(); i++) {
		for (int j = 0; j < graph2List.size(); j++) {
			if (graph1List[i]->index == graph2List[j]->index)
				sharedVertices.push_back(graph1List[i]->index);
		}
	}

	vector<int> vertices;
	for (int i = 0; i < graph1.size(); i++) {
		vertices.push_back(graph1List[i]->index);
	}

	vector<int> nonsharedVertices;
	set<int> s1(sharedVertices.begin(), sharedVertices.end());
	set<int> s2(vertices.begin(), vertices.end());
	vector<string> v3;	
	set_symmetric_difference(s1.begin(),
							 s1.end()  ,
							 s2.begin(),
							 s2.end()  ,
							 std::back_inserter(nonsharedVertices));

	for (int i = 0; i < nonsharedVertices.size(); i++) {
		graph1.removeVertex(nonsharedVertices[i]);
	}
	return graph1;
}

