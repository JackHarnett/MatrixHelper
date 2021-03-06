//
// Created by Jack on 22/02/2019.
//

#ifndef MATRIXHELPER_VECT3_H
#define MATRIXHELPER_VECT3_H

#include <memory>
#include "num_vec.h"

template <class T>
class vec3 : public num_vec<T> {

public:

    vec3(int size, const T *vals) : num_vec<T>(size, vals) {}

    std::unique_ptr<vec3<T>> cross(const vec3<T>& other) const {
        T first  = (this->terms[1] * other.terms[2]) - (this->terms[2] * other.terms[1]);
        T second = (this->terms[2] * other.terms[0]) - (this->terms[0] * other.terms[2]);
        T third  = (this->terms[0] * other.terms[1]) - (this->terms[1] * other.terms[0]);

        return std::make_unique<vec3<T>>(3, new T[3] {first, second, third});
    }
};



#endif //MATRIXHELPER_VECT3_H
