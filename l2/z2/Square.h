//
// Created by asia on 23.04.2020.
//

#ifndef ZADANIE2_SQUARE_H
#define ZADANIE2_SQUARE_H


#include "Matrix.h"

class Square {
private:
    int x, y;
    int height, width;
    int value;
    int id;
public:
    void setId(int id);

    int getId() const;

private:

    Matrix *matrix;
    static const int POSSIBLE_SIZE = 8;
    const int POSSIBLE_VALUES[POSSIBLE_SIZE] = {0, 32, 64, 128, 160, 192, 223, 255};

    int getMeanValue();

    int getClosestPossible(double mean);

public:
    int getX() const;

    void setX(int x);

    void setY(int y);

    void setHeight(int height);

    void setWidth(int width);

    int getHeight() const;

    int getWidth() const;

    int getValue() const;

    int getY() const;
    void changeValue(int value);


    Square(int x, int y, int height, int width, Matrix *matrix);
    Square(const Square&squareToCopy);
//    ~Square();

    double getDistance();

    int getEndX() const;

    int getEndY() const;
    void updateValue();

};


#endif //ZADANIE2_SQUARE_H
