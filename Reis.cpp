//
// Created by Finn on 30/05/2022.
//

#include "Reis.h"

Reis::Reis() {}

void Reis::addEdge(Edge* e) {
    if(e->vertex_1==endPoint) {endPoint = e->vertex_2;}
    else if(e->vertex_2==endPoint) {endPoint = e->vertex_1;}
    else{throw invalid_argument("edge does not connect to path");}
    edges.push(e);
    weight += e->weight;
}

bool Reis::operator > (Reis const& r) {
    return this->weight>r.weight;
}

bool Reis::operator < (const Reis &r) {
    return this->weight<r.weight;
}

ostream &operator<<(ostream &os, Reis &reis) {
    os << "edges: " << endl;
    stack<Edge*> s;
    while(!reis.edges.empty()){
        s.push(reis.edges.top());
        reis.edges.pop();
    }
    while(!s.empty()){
        os << "    " << *s.top() << endl;
        reis.edges.push(s.top());
        s.pop();
    }
    os << "totaalprijs: " << reis.weight;
    return os;
}
