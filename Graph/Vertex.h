#pragma once

#include <map>
#include <iostream>

using namespace std;

class Vertex {
public:
    Vertex() { }
    Vertex(int id) { index = id; }  // �����������
	void breakEdge(Vertex*);			// �������� ����� � ������ ��������
	bool isConnected(int);			// �������� �� ������� ����� � ������ ��������
	void print();					// ���������� �������

    int index;				
    map<Vertex*, int> adjMap;
};