#include "NonOrGraph.h"

#define EXEPTION(reason, message) Exeption((reason), (message), __LINE__, __FUNCSIG__)

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
			throw EXEPTION(betweens_one, "vertex is not adjacent to this");
		}
	}
	catch (Exeption e) {
		e.print();
	}
}