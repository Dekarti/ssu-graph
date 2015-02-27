#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*------------------- EXEPTION DEFINING --------------------*/

Exeption::Exeption(int reason, string message) {
	this->reason = reason;
	this->message = message;
}

void Exeption::print() {
	cout << "EXEPTION: "
		 << message << ":" << reason << endl;
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
		e.print();
	}
}

void Graph::addVertex(int id) { vertexList.push_back(new Vertex(id)); }

void Graph::addEdge(int from, int to, int weight) {

    Vertex* vertexTo;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i]->index == to)
            vertexTo = vertexList[i];
    }
	
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i]->index == from)
			vertexList[i]->adjMap.insert(pair<Vertex*, int>(vertexTo, weight));
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

		int id;
		for (int i = 0; i < size(); i++) {
			if (vertexList[i]->index == removable_id)
				id = i;
		}	
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
			throw Exeption(to_, "vertex is not adjacent to this");
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

void Graph::scan(wchar_t* fileName) {
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