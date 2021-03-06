//
// Created by Jack on 21/02/2019.
//

#ifndef MATRIXHELPER_VECTOR_H
#define MATRIXHELPER_VECTOR_H

#include <memory>
#include <vector>
#include <cmath>

template <class T>
class num_vec {

protected:

    /**
     * The terms of the vector
     */
    std::vector<T> terms;


public:

    /**
     * The size of the vector
     */
    const int size;

    num_vec(int size, const T* vals) : size(size), terms(std::vector<T>(vals, vals+size)) {}

    void print() {
        typename std::vector<T>::iterator it;

        std::cout << "{ ";
        for(it = terms.begin(); it != terms.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << "}" << std::endl;
    }

    /**
     * Creates new vector; does not mutate existing.
     */
    std::unique_ptr<num_vec<T>> operator* (T fact) const {
        auto * temp = new T[size];
        typename std::vector<T>::iterator it;

        int j = 0;
        for(it = terms.begin(); it != terms.end(); it++, j++) {
            *(temp + j) = *it * fact;
        }

        return std::make_unique<num_vec<T>>(size, temp);
    }

    T square_magnitude() {
        T square_sum = 0;

        typename std::vector<T>::iterator it;
        for(it = terms.begin(); it != terms.end(); it++) {
            square_sum += pow(*it, 2);
        }

        return square_sum;
    }

    T magnitude() {
        return sqrt(square_magnitude());
    }

    /**
     * Creates new vector; does not mutate existing.
     */
    num_vec<T> norm() {
        return *this * (1/sqrt(square_magnitude()));
    }

    /**
     * @throw runtime_error if vectors are different sizes.
     */
    T dot(num_vec<T>& other) const {
        if(this->size != other.size)
            throw std::runtime_error("Vector dimensions do not agree - cannot calculate dot product.");

        T temp = 0;

        for(int i = 0; i < this->size; i++) {
            temp += this->terms[i] * other.terms[i];
        }

        return temp;
    }

    T get(int idx) const {
        return terms[idx];
    }

    void set(int idx, T val) {
        terms[idx] = val;
    }
};


#endif //MATRIXHELPER_VECTOR_H
