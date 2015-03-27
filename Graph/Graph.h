#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "Vertex.h"

using namespace std;

struct Exeption {
	Exeption(int reason, string message, int line, string func);
	void print();
	string message;
	int reason;
	string line;
	string func;
};

class Graph {
public:
    Graph() { };
	bool exists(int id);			 						// проверить на наличие вершины в графе
    void addVertex(int id);		 							// добавить вершину 
    void addEdge(int from, int to, int weight); 			// добавить дугу
    int getWeight(int from, int to);			 			// получить вес ребра
    int size();									 			// размерность графа
    void show();								 			// отобразить граф
	Vertex* getVertex(int id);		 						// доступ к вершине по имени
    Vertex* operator[](int id);	 							// доступ к вершине по имени
	void removeVertex(int removable_id);		 			// удалить вершину
	void removeEdge(int from_, int to_);		 			// удалить дугу
	int indegree(int id);						 			// полустепень захода
	void scan(string fileName);					  			// считать граф из файла
	vector<Vertex*> vertices();								// возвращает список смежности
	void dfs(int i, vector<bool> &used);					// обход графа в глубину
	void dfs(int i, vector<bool> &used, vector<char> cycle);// обход графа в глубину (цветные вершины)
	void bfs(int i);										// обход графа в ширину
	bool isConnected();										// проверка графа на связность
	int edgesNumber();										// количество ребер
	bool isTree();											// проверка является ли граф деревом

protected:
    vector<Vertex*> vertexList;
};

Graph intersection(Graph graph1, Graph graph2);
