//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_VLUCHT_H
#define UNTITLED3_VLUCHT_H

#include <ostream>
#include "Edge.h"

class Vlucht : public Edge {
public:
    float kosten;
    float pBagageKwijt;

    Vlucht(int vertex1, int vertex2, float kosten, float pBagageKwijt, float bagageKosten);

    float getWeight() override;

    friend ostream &operator<<(ostream &os, const Vlucht &vlucht);
};

#endif //UNTITLED3_VLUCHT_H
