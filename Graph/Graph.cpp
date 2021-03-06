#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#define PRINT_EXEPTION() print(__FILE__, __LINE__, __FUNCTION__)

using namespace std;

/*------------------- Exeption DEFINING --------------------*/

Exeption::Exeption(int reason, string message) {
	this->reason = reason;
	this->message = message;
}

void Exeption::print(string file, int line, string func) {
	cout << "EXEPTION:      " << message << endl 
		 << "  Reason elem: " << reason  << endl
		 << "  File:        " << file	 << endl
		 << "  Line:        " << line    << endl 
		 << "  Function:    " << func    << endl
		 << endl;
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
			throw Exeption(id, "no such element");
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
		e.PRINT_EXEPTION();
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
					throw Exeption(0, "edge between given vertices already exists");
				}
			}
		}
	}
	catch (Exeption e) {
		e.PRINT_EXEPTION();
	}
}

int Graph::getWeight(int from, int to) {
	try {
		return getVertex(from)->adjMap[getVertex(to)];
	}
	catch (Exeption e) {
		e.PRINT_EXEPTION();
	}
}

void Graph::show() {
	cout << endl;
	for (int i = 0; i < vertexList.size(); i++) {
		vertexList[i]->printOriented();
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
		e.PRINT_EXEPTION();
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
			throw Exeption(to_, "vertex is not adjacent to this");
		}
	}
	catch (Exeption e) {
		e.PRINT_EXEPTION();
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
		e.PRINT_EXEPTION();
	}
}

void Graph::scan(string stringFileName) {
	vertexList.clear();
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



void Graph::dfs(int i, map<int, bool> &used) {
    used[i] = true;
	Vertex* curVertex = getVertex(i);
	for(map<Vertex*, int>::iterator it =  curVertex->adjMap.begin();
									it != curVertex->adjMap.end();
									it ++) {
        if (used[it->first->index] == false) {
            dfs(it->first->index, used);
        }
    }
}

bool Graph::isConnected() {
	bool isConnected;
    map<int, bool> used;
	for (int j = 0; j < size(); j++) {
		used[vertexList[j]->index] == false;
	}

	for (int i = 0; i < vertexList.size(); i++) {
		dfs(vertexList[i]->index, used);
		for (int j = 0; j < size(); j++) {
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

