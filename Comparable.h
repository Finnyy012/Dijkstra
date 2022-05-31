//
// Created by Finn on 30/05/2022.
//

#ifndef UNTITLED3_COMPARABLE_H
#define UNTITLED3_COMPARABLE_H

template<typename T>
class Comparable {
    virtual bool operator > (T const& rhs)=0;

    virtual bool operator < (T const& rhs)=0;
};

#endif //UNTITLED3_COMPARABLE_H
