//
// Created by Finn on 30/05/2022.
//

#include "Vlucht.h"

Vlucht::Vlucht(int vertex1, int vertex2, float kosten, float pBagageKwijt, float bagageKosten) :
    Edge(vertex1, vertex2, kosten+(pBagageKwijt*bagageKosten)), kosten(kosten), pBagageKwijt(pBagageKwijt) {}

float Vlucht::getWeight() {
    return 0;
}

ostream &operator<<(ostream &os, const Vlucht &vlucht) {
    os << static_cast<const Edge &>(vlucht) << " pBagageKwijt: " << vlucht.pBagageKwijt;
    return os;
}

