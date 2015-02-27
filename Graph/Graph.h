#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "Vertex.h"

using namespace std;

struct Exeption {
	Exeption(int reason, string message);
	void print();
	string message;
	int reason;
};

class Graph {
public:
    Graph() { };
	bool exists(int);			// ��������� �� ������� ������� � �����
    void addVertex(int);		// �������� ������� 
    void addEdge(int, int, int); // �������� ����
    int getWeight(int, int);	// �������� ��� �����
    int size();					// ����������� �����
    void show();				// ���������� ����
	Vertex* getVertex(int);		// ������ � ������� �� �����
    Vertex* operator[](int);	// ������ � ������� �� �����
	void removeVertex(int);		// ������� �������
	void removeEdge(int, int);	// ������� ����
	int indegree(int);			// ����������� ������

protected:
    vector<Vertex*> vertexList;
};

