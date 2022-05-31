//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_AUTORIT_H
#define UNTITLED3_AUTORIT_H


#include <ostream>
#include "Edge.h"

class AutoRit : public Edge{
public:
    float afstand;

    AutoRit();

    AutoRit(int vertex1, int vertex2, float afstand, float afstandPrijs);

    float getWeight() override;

    friend ostream &operator<<(ostream &os, const AutoRit &rit);
};


#endif //UNTITLED3_AUTORIT_H
