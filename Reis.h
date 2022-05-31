//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_REIS_H
#define UNTITLED3_REIS_H

#include <queue>
#include <ostream>
#include <stack>
#include "Edge.h"
#include "Comparable.h"


class Reis : public Comparable<Reis> {
public:
    stack<Edge*> edges;
    float weight = 0;
    int endPoint = 0;

public:
    Reis();

    void addEdge(Edge* e);

    bool operator > (Reis const& r) override;

    bool operator < (Reis const& r) override;

    friend ostream &operator<<(ostream &os, Reis &reis);
};


#endif //UNTITLED3_REIS_H
