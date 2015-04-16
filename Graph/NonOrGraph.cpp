#include "NonOrGraph.h"

#define PRINT_EXEPTION() print(__FILE__, __LINE__, __FUNCTION__)

void NonOrGraph::addEdge(int betweens_one, int betweens_two, int weight) {
	Vertex* betweensOne;
	Vertex* betweensTwo;
    for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i]->index == betweens_one)
            betweensOne = vertexList[i];
    }

	for (int i = 0; i < vertexList.size(); i++) {
        if (vertexList[i]->index == betweens_two)
            betweensTwo = vertexList[i];
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
		if (used[vertexList[i]->index] == false)
			return false;
	}
	return true;
}

bool NonOrGraph::isTree() {
	return isConnected()
		&& (edgesNumber() == vertexList.size() - 1);
}
