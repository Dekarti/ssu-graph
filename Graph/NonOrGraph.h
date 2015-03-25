#include "Graph.h"
#include "Vertex.h"

class NonOrGraph : public Graph {
public:
	void addEdge(int, int, int);
	void removeEdge(int, int);
	bool isConnected();
	bool isTree();
};