//
// Created by asia on 25.04.2020.
//

#include "Solution.h"
#include <iostream>
#include <cmath>

using namespace std;

Solution::Solution( vector< Square *> squares, Matrix *originalMatrix) {
    this->matrix = new Matrix(originalMatrix->getN(), originalMatrix->getM(), originalMatrix->getK());
    this->squares_list = squares;
    this->originalMatrix = originalMatrix;
    for (int s = 0; s < squares_list.size(); s++) {
        squares_list[s]->setId(s);
    }
   updateMatrix();

}

double Solution::getDistance() {
    double distance = 0;
    for(int i=0; i<squares_list.size(); i++){
            distance += squares_list[i]->getDistance();
    }

    distance=distance / (originalMatrix->getN() * originalMatrix->getM());
    return distance;


}

void Solution::printSolution() {
    for (int i = 0; i < matrix->getN(); i++) {
        for (int j = 0; j < matrix->getM(); j++) {
        cerr<<squares_list[matrix->getValue(i,j)]->getValue()<<" ";
        }
        cerr<<endl;
    }

}

int Solution::getSquaresSize() {
    return squares_list.size();
}

Square *Solution::getSquare(int i) {
    return squares_list[i];
}

Square *Solution::getNeighbour(Square *square, int edge) {
    if (square->getX() - 1 >= 0 && edge == 1) {
        return squares_list[matrix->getValue(square->getX()-1, square->getY())];
    } else if (square->getEndX() < matrix->getN() && edge == 3) {
        return squares_list[matrix->getValue(square->getEndX(), square->getY())];
    } else if (square->getY() - 1 >= 0 && edge == 4) {
        return squares_list[matrix->getValue(square->getX() , square->getY()-1)];
    } else if (square->getEndY() < matrix->getM() && edge == 2) {
        return squares_list[matrix->getValue(square->getX(), square->getEndY())];
    }
    return nullptr;
}

vector<int> Solution::getPossibleOperations(Square *square) {
    vector<int> operations;
    Square *neighbour;
    neighbour = getNeighbour(square, 1);
    if (neighbour != nullptr && square->getWidth() == neighbour->getWidth() && square->getY()==neighbour->getY()) {
        operations.push_back(1);
    }
    neighbour = getNeighbour(square, 3);
    if (neighbour != nullptr && square->getWidth() == neighbour->getWidth() && square->getY()==neighbour->getY()) {
        operations.push_back(3);
    }
    neighbour = getNeighbour(square, 2);
    if (neighbour != nullptr && square->getHeight() == neighbour->getHeight() && square->getX()==neighbour->getX()) {
        operations.push_back(2);
    }
    neighbour = getNeighbour(square, 4);
    if (neighbour != nullptr && square->getHeight() == neighbour->getHeight() && square->getX()==neighbour->getX()) {
        operations.push_back(4);
    }

    if(square->getHeight()>=2*matrix->getK()){
        operations.push_back(5);
    }
    if(square->getWidth()>=2*matrix->getK()){
        operations.push_back(6);
    }
    return operations;
}

void Solution::part(Square *square, int remaining, int edge) {
    Square* newSquare;
    if(edge==5){
        square->updateValue();
        newSquare=new Square(square->getX()+remaining,square->getY(),square->getHeight()-remaining,square->getWidth(),originalMatrix);
        square->setHeight(remaining);
    }else{
        square->updateValue();
        newSquare=new Square(square->getX(),square->getY()+remaining,square->getHeight(),square->getWidth()-remaining,originalMatrix);
        square->setWidth(remaining);
    }
    squares_list.push_back(newSquare);
    newSquare->setId(getSquaresSize()-1);
    updateMatrix();

}

void Solution::merge(Square *square, int edge) {
    Square *neighbour=getNeighbour(square,edge);
    if(edge==1){
        square->setX(neighbour->getX());
        square->setHeight(square->getHeight()+neighbour->getHeight());
    }else if(edge==3){
        square->setHeight(square->getHeight()+neighbour->getHeight());
    }else if(edge==4){
        square->setY(neighbour->getY());
        square->setWidth(square->getWidth()+neighbour->getWidth());
    }else{
        square->setWidth(square->getWidth()+neighbour->getWidth());
    }
    square->updateValue();
    squares_list.erase(squares_list.begin()+neighbour->getId());
//    squares_list.erase(neighbour->getId());
    updateMatrix();
}

void Solution::updateMatrix() {
    for (int s = 0; s < squares_list.size(); s++) {
        squares_list[s]->setId(s);
        for (int j = squares_list[s]->getX(); j < squares_list[s]->getEndX(); j++) {
            for (int i = squares_list[s]->getY(); i < squares_list[s]->getEndY(); i++) {
                matrix->addValue(j, i, s);
            }
        }
    }
}

Solution::Solution(Solution *solution) {
    originalMatrix=solution->originalMatrix;
    for(int i=0; i<solution->squares_list.size(); i++){
        squares_list.push_back(new Square(*solution->squares_list[i]));
    }
    matrix=new Matrix(*solution->matrix);
}

Solution::~Solution() {
    for(auto & i : squares_list){
        delete (i);
    }
    delete (matrix);
}

