//
// Created by asia on 20.04.2020.
//

#ifndef ZADANIE2_MATRIX_H
#define ZADANIE2_MATRIX_H

#include <vector>



using namespace std;

class Matrix {
private:
    int n, m, k;
    int **matrix;

public:
    int getN() const;

    int getK() const;

    int getM() const;

    Matrix(int n, int m, int k);
    Matrix(const Matrix&matrixToCopy);

    void addValue(int i, int j, int value);

    void printMatrix();

    int getValue(int i, int j);

    ~Matrix();

};


#endif //ZADANIE2_MATRIX_H
