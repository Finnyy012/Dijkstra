//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_TREINRIT_H
#define UNTITLED3_TREINRIT_H

#include <ostream>
#include "Edge.h"

class TreinRit : public Edge {
public:
    float tijd;

    float getWeight() override;

    TreinRit(int vertex1, int vertex2, float tijd, float tijdPrijs);

    friend ostream &operator<<(ostream &os, const TreinRit &rit);
};


#endif //UNTITLED3_TREINRIT_H
