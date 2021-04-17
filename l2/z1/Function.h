//
// Created by asia on 19.04.2020.
//

#ifndef ZADANIE1_FUNCTION_H
#define ZADANIE1_FUNCTION_H

#endif //ZADANIE1_FUNCTION_H

#include <vector>

using namespace std;

class Function {
public:
    virtual double getFunctionValue(vector<double> x)=0;

protected:
    virtual double getSquaredSum(vector<double> x)=0;
};