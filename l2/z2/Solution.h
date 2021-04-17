//
// Created by asia on 25.04.2020.
//

#ifndef ZADANIE2_SOLUTION_H
#define ZADANIE2_SOLUTION_H


#include "Square.h"
#include<map>
class Solution {
private:
    vector< Square *> squares_list;
    Matrix *matrix;
    Matrix *originalMatrix;


public:
    Solution( vector< Square *>   squares, Matrix *originalMatrix);
    Solution(Solution *solution);
    ~Solution();
    double getDistance();

    void printSolution();

    int getSquaresSize();

    Square *getSquare(int position);

    vector<int> getPossibleOperations(Square *square);

    Square *getNeighbour(Square *square, int edge);

    void part(Square *square, int remaining, int edge);

    void merge(Square *square, int edge);
    void updateMatrix();
};


#endif //ZADANIE2_SOLUTION_H
