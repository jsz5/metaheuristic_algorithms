//
// Created by asia on 23.04.2020.
//

#include "Square.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

Square::Square(int x, int y, int height, int width, Matrix *matrix) {
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->matrix = matrix;
    this->value = getMeanValue();
}

int Square::getMeanValue() {
    double mean = 0;
    for (int j = x; j < getEndX(); j++) {
        for (int i = y; i < getEndY(); i++) {
            mean += matrix->getValue(j, i);
        }
    }
    mean /= (width * height);
    return getClosestPossible(mean);
}

int Square::getClosestPossible(double mean) {
    int closest = POSSIBLE_VALUES[0];
    for (int i = 1; i < POSSIBLE_SIZE; i++) {
        if (abs(round(mean) - POSSIBLE_VALUES[i]) < abs(round(mean) - closest)) {
            closest = POSSIBLE_VALUES[i];
        }
    }
    return closest;

}

double Square::getDistance() {
//    cout<<"x "<<x<<" y "<<y<<" endX "<<getEndX()<<" endY "<<getEndY()<<" value "<<value<<endl;
    double distance = 0;
    for (int j = x; j < getEndX(); j++) {
        for (int i = y; i < getEndY(); i++) {
            distance += pow(matrix->getValue(j, i) - value, 2);
        }
    }
    return distance;
}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}

int Square::getEndY() const {
    return y + width;
}

int Square::getEndX() const {
    return x + height;
}

int Square::getValue() const {
    return value;
}

int Square::getHeight() const {
    return height;
}

int Square::getWidth() const {
    return width;
}

void Square::setX(int x) {
    this->x = x;
}

void Square::setY(int y) {
    this->y = y;
}

void Square::setHeight(int height) {
    this->height = height;
}

void Square::setWidth(int width) {
    this->width = width;
}

void Square::updateValue() {
    this->value = getMeanValue();
}

int Square::getId() const {
    return id;
}

void Square::setId(int id) {
    this->id = id;
}

void Square::changeValue(int value) {
    this->value = value;
}

Square::Square(const Square &squareToCopy) {
    x = squareToCopy.x;
    y = squareToCopy.y;
    height = squareToCopy.height;
    width = squareToCopy.width;
    value = squareToCopy.value;
    id = squareToCopy.id;
    matrix = squareToCopy.matrix;
}

//Square::~Square() {
//    delete (matrix);
//}


