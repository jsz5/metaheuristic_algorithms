//
// Created by asia on 20.04.2020.
//

#include "Matrix.h"
#include <iostream>
#include <cmath>


Matrix::Matrix(int n, int m, int k) {
    this->n = n;
    this->m = m;
    this->k = k;
    this->matrix = new int *[m];
    for (int i = 0; i < n; i++) {
        this->matrix[i] = new int[m];
    }
}

void Matrix::addValue(int i, int j, int value) {
    matrix[i][j] = value;
}

void Matrix::printMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int Matrix::getN() const {
    return n;
}

int Matrix::getM() const {
    return m;
}


int Matrix::getK() const {
    return k;
}

int Matrix::getValue(int i, int j) {
    return matrix[i][j];
}

Matrix::Matrix(const Matrix &matrixToCopy) {
    n = matrixToCopy.n;
    m = matrixToCopy.m;
    k = matrixToCopy.k;
    matrix = new int *[matrixToCopy.m];
    for (int i = 0; i < n; i++) {
        this->matrix[i] = new int[matrixToCopy.m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = matrixToCopy.matrix[i][j];
        }
    }

}

Matrix::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[]matrix[i];
    }
    delete (matrix);
}



