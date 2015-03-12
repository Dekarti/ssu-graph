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
	bool exists(int);			 		// ��������� �� ������� ������� � �����
    void addVertex(int);		 		// �������� ������� 
    void addEdge(int, int, int); 		// �������� ����
    int getWeight(int, int);	 		// �������� ��� �����
    int size();					 		// ����������� �����
    void show();				 		// ���������� ����
	Vertex* getVertex(int);		 		// ������ � ������� �� �����
    Vertex* operator[](int);	 		// ������ � ������� �� �����
	void removeVertex(int);		 		// ������� �������
	void removeEdge(int, int);	 		// ������� ����
	int indegree(int);			 		// ����������� ������
	void scan(string fileName);  		// ������� ���� �� �����
	vector<Vertex*> vertices();		// ���������� ������ ���������

protected:
    vector<Vertex*> vertexList;
};

Graph intersection(Graph graph1, Graph graph2);
