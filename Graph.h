#ifndef Graph_H
#define Graph_H

#include <bits/stdc++.h>
#include "Edge.h"
using namespace std;

class Graph {           // Implementation of a Dynamic Directed Graph Class with efficient support of vertex delete and addition
private :
    map<int, map<int, Edge>> g;     // adjacency list representation
public :
    Graph();
    void addVertex(int v);
    void addEdge(int u, int v, TransactionRecord & x);
    void assignEdge(int u, int v, Edge & e);
    void reset(int u, int v);
    map<int, Edge> & operator[](int v);
    Edge getWeight(int u, int v);
    void deleteVertex(int u);
    vector<int> getVertices();
    friend ostream & operator<<(ostream & stream, Graph & g);
    friend ofstream & operator<<(ofstream & stream, Graph & g);
    friend istream & operator>>(istream & stream, Graph & g);
    friend ifstream & operator>>(ifstream & stream, Graph & g);
};

#endif