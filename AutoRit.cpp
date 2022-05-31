//
// Created by Finn on 30/05/2022.
//

#include "AutoRit.h"

AutoRit::AutoRit(int vertex1, int vertex2, float afstand, float afstandPrijs) :
    Edge(vertex1, vertex2, afstand*afstandPrijs), afstand(afstand) {}

ostream &operator<<(ostream &os, const AutoRit &rit) {
    os << static_cast<const Edge &>(rit) << " afstand: " << rit.afstand;
    return os;
}

float AutoRit::getWeight() {
    return 0;
}

AutoRit::AutoRit() {}
