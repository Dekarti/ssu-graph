#include "Graph.h"
#include "Vertex.h"

class NonOrGraph : public Graph {
public:
	void addEdge(int, int, int);
	void removeEdge(int, int);
	bool isConnected();
	bool isTree();
	void show();
	void scan(string fileName);
	vector< pair<int, pair<int, int>> > edges();
	int edgesNumber();										// количество ребер

};