#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include "Vertex.h"

using namespace std;

struct Exeption {
	Exeption(int reason, string message);
	void print(string file, int line, string func);
	string message;
	int reason;
};

class Graph {
public:
    Graph() { };
	bool exists(int id);			 						// ��������� �� ������� ������� � �����
    void addVertex(int id);		 							// �������� ������� 
    void addEdge(int from, int to, int weight); 			// �������� ����
    int getWeight(int from, int to);			 			// �������� ��� �����
    int size();									 			// ����������� �����
    void show();								 			// ���������� ����
	Vertex* getVertex(int id);		 						// ������ � ������� �� �����
    Vertex* operator[](int id);	 							// ������ � ������� �� �����
	void removeVertex(int removable_id);		 			// ������� �������
	void removeEdge(int from_, int to_);		 			// ������� ����
	int indegree(int id);						 			// ����������� ������
	void scan(string fileName);					  			// ������� ���� �� �����
	vector<Vertex*> vertices();								// ���������� ������ ���������
	void dfs(int i, map<int, bool> &used);					// ����� ����� � �������
	void dfs(int i, vector<bool> &used, vector<char> cycle);// ����� ����� � ������� (������� �������)
	void bfs(int i);										// ����� ����� � ������
	bool isConnected();										// �������� ����� �� ���������
	int edgesNumber();										// ���������� �����
	bool isTree();											// �������� �������� �� ���� �������

protected:
    vector<Vertex*> vertexList;
};

Graph intersection(Graph graph1, Graph graph2);
