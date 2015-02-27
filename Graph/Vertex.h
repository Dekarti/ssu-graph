#pragma once

#include <map>
#include <iostream>

using namespace std;

class Vertex {
public:
    Vertex() { }
    Vertex(int id) { index = id; }  // конструктор
	void breakEdge(Vertex*);			// оборвать связь с данной вершиной
	bool isConnected(int);			// проверка на наличие связи с данной вершиной
	void print();					// отобразить вершину

    int index;				
    map<Vertex*, int> adjMap;
};