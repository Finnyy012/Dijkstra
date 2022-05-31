//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_EDGE_H
#define UNTITLED3_EDGE_H

#include <ostream>

using namespace std;

class Edge {
public:
    int vertex_1;
    int vertex_2;
    float weight;

    Edge();

    Edge(int vertex1, int vertex2, float weight);

    virtual float getWeight()=0;

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge);
};


#endif //UNTITLED3_EDGE_H
