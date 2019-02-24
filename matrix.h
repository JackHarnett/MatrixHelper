//
// Created by Jack on 22/02/2019.
//

#ifndef MATRIXHELPER_MATRIX_H
#define MATRIXHELPER_MATRIX_H


#include <memory>
#include <vector>
#include "num_vec.h"
#include <algorithm>

template <class T>
class matrix {

protected:

    /**
     * Each row is represented by a num_vector.
     */
    std::vector<num_vec<T>> terms;

public:

    /**
     * Y size
     */
    const int rows;

    /**
     * X size
     */
    const int cols;

    /**
     * @throw runtime_error if the rows are not of equal size.
     */
    matrix(int size, num_vec<T>* rows) : rows(size), cols(rows[0].size) {
        terms = std::vector<num_vec<T>>(rows, rows+size);
        std::vector<num_vec<T>> actual;

        std::copy_if(terms.begin(), terms.end(), std::back_inserter(actual), [&rows](num_vec<T> x) {
            return x.size == rows[0].size;
        });

        if(actual.size() != terms.size()) throw std::runtime_error("Matrix row dimensions do not agree.");
    }

    matrix(const matrix& other) : rows(other.rows), cols(other.cols), terms(other.terms) {}


    void print() {
        typename std::vector<num_vec<T>>::iterator it;

        for(it = terms.begin(); it != terms.end(); it++) {
            it->print();
        }
    }

    /**
     * Creates a new transposed matrix - does not mutate existsing.
     */
    std::unique_ptr<matrix<T>> transpose() const {
        int rows = this->cols;
        int cols = this->rows;

        std::vector<num_vec<T>> row_vec;
        row_vec.reserve(rows);

        for(int i = 0; i < rows; i++) {
            auto temp = new T[cols];

            for(int j = 0; j < cols; j++) {
                temp[j] = this->terms[j].get(i);
            }

            row_vec.push_back(num_vec(cols, temp));
            delete[] temp;
        }

        return std::make_unique<matrix<T>>(row_vec.size(), &row_vec[0]);
    }

    std::unique_ptr<matrix<T>> operator*(matrix<T>& other) const {
        // dimensions of first matrix
        int n = this->cols;
        int m = this->rows;

        // dimensions of the second matrix
        int o = other.cols;
        int p = other.rows;

        std::vector<num_vec<T>> mat;

        if(this->cols != other.rows)
            throw std::runtime_error("Matrix dimensions do not agree - cannot multiply");

        for(int i = 0; i < n; i++) {
            std::vector<T> vec;

            for(int j = 0; j < o; j++) {
                T sum = 0;

                for(int k = 0; k < m; k++) {
                    sum += this->terms[i].get(k) * other.terms[k].get(j);
                }

                vec.push_back(sum);
            }

            mat.push_back(num_vec(vec.size(), &vec[0]));
        }

        return std::make_unique<matrix<T>>(mat.size(), &mat[0]);
    }

    T get(int x, int y) {
        return terms[y].get(x);
    }

};

#endif //MATRIXHELPER_MATRIX_H
