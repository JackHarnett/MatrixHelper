//
// Created by Jack on 23/02/2019.
//

#ifndef MATRIXHELPER_SQUARE_MAR_H
#define MATRIXHELPER_SQUARE_MAR_H


#include "matrix.h"

template <class T>
class square_mat : public matrix<T> {

public:

    square_mat(int size, num_vec<T> *rows) : matrix<T>(size, rows) {
        if(this->rows != this->cols) throw std::runtime_error("Matrix is not square.");
    }

    explicit square_mat(matrix<T> mat) : matrix<T>(mat) {}

    int getSize() {
        return this->cols;
    }

    T trace() {
        T sum = 0;
        for(int i = 0; i < this->cols; i++) {
            sum += this->terms[i].get(i);
        }

        return sum;
    }

    /**
     * Creates an nxn matrix of 0s.
     */
    static std::unique_ptr<square_mat<T>> zeros(int n) {
        std::vector<num_vec<T>> rows;

        for(int i = 0; i < n; i++) {
            num_vec<T> row(n, new T[n] {0});
            rows.push_back(row);
        }

        return std::make_unique<square_mat<T>>(n, &rows[0]);
    }

    /**
     * Creates an nxn identity matrix.
     */
    static std::unique_ptr<square_mat<T>> ident(int n) {
        auto mat = zeros(n);

        for(int i = 0; i < n; i++) {
           mat->set(i, i, 1);
        }

        return mat;
    }
};


#endif //MATRIXHELPER_SQUARE_MAR_H
