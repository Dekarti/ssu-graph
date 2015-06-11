#include "NonOrGraph.h"

#define PRINT_EXEPTION() print(__FILE__, __LINE__, __FUNCTION__)

void NonOrGraph::addEdge(int betweens_one, int betweens_two, int weight) {

	Vertex* betweensOne;
	Vertex* betweensTwo;

    for (int i = 0; i < vertexList.size(); i++) {
		if (vertexList[i]->index == betweens_one) {
            betweensOne = vertexList[i];
		}
    }

	for (int i = 0; i < vertexList.size(); i++) {
		if (vertexList[i]->index == betweens_two) {
            betweensTwo = vertexList[i];
		}
    }

	betweensOne->adjMap.insert(pair<Vertex*, int>(betweensTwo, weight));
	betweensTwo->adjMap.insert(pair<Vertex*, int>(betweensOne, weight));

}

void NonOrGraph::removeEdge(int betweens_one, int betweens_two) {
	Vertex* betweensOne;
	Vertex* betweensTwo;
	try {
		betweensOne = getVertex(betweens_one);
		betweensTwo = getVertex(betweens_two);
		if (betweensOne->isConnected(betweens_two) && betweensTwo->isConnected(betweens_one)) {
			betweensOne->breakEdge(betweensTwo);
			betweensTwo->breakEdge(betweensOne);
		}
		else {
			throw Exeption(betweens_one, "vertex is not adjacent to this");
		}
	}
	catch (Exeption e) {
		e.PRINT_EXEPTION();
	}
}

bool NonOrGraph::isConnected() {
    map<int, bool> used;
	for (int j = 0; j < vertexList.size(); j++) {
		used[vertexList[j]->index] == false;
	}

	dfs(vertexList[0]->index, used);
	for (int i = 0; i < vertexList.size(); i++) {
		if (used[vertexList[i]->index] == false) {
			return false;
		}
	}
	return true;
}

bool NonOrGraph::isTree() {
	/*if (!isConnected())
		cout << "Is not connected" << endl;
	if (edgesNumber() != vertexList.size() - 1)
		cout << "M <> N - 1";*/
	return isConnected()
		&& (edgesNumber() == vertexList.size() - 1);
}

void NonOrGraph::scan(string stringFileName) {
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

vector< pair<int, pair<int, int>> > NonOrGraph::edges() {

	vector< pair<int, pair<int, int>> > edges(0);

	for (int i = 0; i < vertexList.size(); i++) {
		for(map<Vertex*, int>::iterator it = vertexList[i]->adjMap.begin();
											it != vertexList[i]->adjMap.end();
											it++)
		{
			int weight = it->second;
			int from   = vertexList[i]->index;
			int to     = it->first->index;
			
			bool exists = false;
	
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].second.first == to && edges[i].second.second == from) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				edges.push_back(make_pair(weight, make_pair(from, to)));
			}
		}
	}

	return edges;

}

void NonOrGraph::show() {

	cout << endl;
	vector< pair<int, pair<int, int>> > edges = this->edges();
	for (int i = 0; i < edges.size(); i++) {
		cout << edges[i].second.first << " <--("
			 << edges[i].first << ")--> "
			 << edges[i].second.second << endl;
	}
	cout << endl;

}

int NonOrGraph::edgesNumber() {

	int edgesCounter = 0;
	for (int i = 0; i < size(); i++) {
		edgesCounter += vertexList[i]->adjMap.size();
	}
	return edgesCounter / 2;

}