//
// Created by Finn on 30/05/2022.
//

#include <iostream>
#include "Edge.h"

Edge::Edge(int vertex1, int vertex2, float weight) : vertex_1(vertex1), vertex_2(vertex2), weight(weight) {}

std::ostream &operator<<(std::ostream &os, const Edge &edge) {
    os << "vertex_1: " << edge.vertex_1 << " vertex_2: " << edge.vertex_2 << " prijs: " << edge.weight;
    return os;
}

Edge::Edge() : vertex_1(0), vertex_2(0), weight(0) {}
