//
// Created by Finn on 30/05/2022.
//

#include "TreinRit.h"

TreinRit::TreinRit(int vertex1, int vertex2, float tijd, float tijdPrijs) :
    Edge(vertex1, vertex2, tijd*tijdPrijs), tijd(tijd) {}

float TreinRit::getWeight() {
    return 0;
}

ostream &operator<<(ostream &os, const TreinRit &rit) {
    os << static_cast<const Edge &>(rit) << " tijd: " << rit.tijd;
    return os;
}
