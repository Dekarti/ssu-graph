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
	bool exists(int);			 		// проверить на наличие вершины в графе
    void addVertex(int);		 		// добавить вершину 
    void addEdge(int, int, int); 		// добавить дугу
    int getWeight(int, int);	 		// получить вес ребра
    int size();					 		// размерность графа
    void show();				 		// отобразить граф
	Vertex* getVertex(int);		 		// доступ к вершине по имени
    Vertex* operator[](int);	 		// доступ к вершине по имени
	void removeVertex(int);		 		// удалить вершину
	void removeEdge(int, int);	 		// удалить дугу
	int indegree(int);			 		// полустепень захода
	void scan(string fileName);  		// считать граф из файла
	vector<Vertex*> vertices();		// возвращает список смежности

protected:
    vector<Vertex*> vertexList;
};

Graph intersection(Graph graph1, Graph graph2);
