#include <iostream>
#include "num_vec.h"
#include "vec3.h"
#include "matrix.h"

int main() {
    auto vec1 = num_vec<float>(3, new float[3] {1, 2, 3});
    auto vec2 = num_vec<float>(3, new float[3] {4, 5, 6});
    auto vec3 = num_vec<float>(3, new float[3] {7, 8, 9});

    auto mat1 = matrix<float>(3, new num_vec<float>[3] {vec1, vec2, vec3});
    mat1.print();
}