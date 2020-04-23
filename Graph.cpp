#include "Graph.h"

Graph::Graph(){     // constructor

}
void Graph::addVertex(int v){      // add a new vertex
    g[v].clear();
}
void Graph::addEdge(int u, int v, TransactionRecord & x){    // add a new edge
    if(g.find(v) == g.end()){
        g[v].clear();
    }
    g[u][v].addRecord(x);
}
void Graph::assignEdge(int u, int v, Edge & e){       // assign a new edge between 2 vertices
    g[u][v] = e;
}
void Graph::reset(int u, int v){             // clear the edge between 2 vertices
    g[u][v] = Edge(); 
}
map<int, Edge> & Graph::operator[](int v){      // a reference is returned
    return g[v];
}
Edge Graph::getWeight(int u, int v){      // return edge corresponding to 2 vertices
    if(g.find(u) != g.end() and g[u].find(v) != g[u].end()){
        return g[u][v];
    }
    return Edge();
}
void Graph::deleteVertex(int u){      // remove vertex from the graph
    for(auto it = g.begin(); it != g.end(); it++){
        it->second.erase(u);
    }
    g.erase(u);
}
vector<int> Graph::getVertices(){       // return all vertices
    vector<int> v;
    for(auto it : g){
        v.push_back(it.first);
    }
    return v;
}

ostream & operator<<(ostream & stream, Graph & g){    
    for(auto it : g.g){
        stream<<it.first<<" ";
        for(auto e : it.second){
            stream<<e.first<<" "<<g[it.first][e.first]<<" ";
        }
        stream<<"-1 ";
    }
    stream<<"-2"<<endl;
    return stream;
}

ofstream & operator<<(ofstream & stream, Graph & g){    // operator to write graph into the file
    for(auto it : g.g){
        stream<<it.first<<" ";
        for(auto e : it.second){
            stream<<e.first<<" "<<g[it.first][e.first]<<" ";
        }
        stream<<"-1 ";
    }
    stream<<"-2"<<endl;
    return stream;
}

istream & operator>>(istream & stream, Graph & g){
    int c;
    while(stream>>c){
        if(c == -2){
            return stream;
        }
        g.addVertex(c);
        int d;
        while(stream>>d){
            if(d == -1){
                break;
            }
            Edge w;
            stream>>w;
            g.assignEdge(c, d, w);
        }
    }
}

ifstream & operator>>(ifstream & stream, Graph & g){
    int c;
    while(stream>>c){
        if(c == -2){
            return stream;
        }
        g.addVertex(c);
        int d;
        while(stream>>d){
            if(d == -1){
                break;
            }
            Edge w;
            stream>>w;
            g.assignEdge(c, d, w);
        }
    }
}
