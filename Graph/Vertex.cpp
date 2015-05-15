#include "Vertex.h"
#include "Graph.h"

void Vertex::breakEdge(Vertex* vertex) {
	if (isConnected(vertex->index)) {
		adjMap.erase(adjMap.find(vertex));
	}
	/*else {
		throw Exeption(vertex->index, "vertex is not adjacent to this"); 
	}*/
}

void Vertex::printOriented() {
    for(map<Vertex*, int>::iterator it = adjMap.begin();
									it != adjMap.end();
									it++) {
        cout << "  " << index << " --(" << it->second << ")-> " << it->first->index << endl;
    }
	if (adjMap.size() == 0) 
		cout << "  " << index << " <isolated>" << endl;
}

void Vertex::printNonOriented() {
    for(map<Vertex*, int>::iterator it = adjMap.begin();
									it != adjMap.end();
									it++) {
        cout << "  " << index << " <-(" << it->second << ")-> " << it->first->index << endl;
    }
	if (adjMap.size() == 0) 
		cout << "<isolated>" << index << endl;
}

bool Vertex::isConnected(int id) {
	for(map<Vertex*, int>::iterator it = adjMap.begin();
									it != adjMap.end();
									it++) {
		if (it->first->index == id) {
			return true;
			break;
		}
	}
	return false;
}