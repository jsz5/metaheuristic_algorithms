//
// Created by asia on 19.04.2020.
//

#ifndef ZADANIE1_SALOMONSFUNCTION_H
#define ZADANIE1_SALOMONSFUNCTION_H

#include "SalomonsFunction.h"

#include <vector>
#include "Function.h"
using namespace std;

class SalomonsFunction: public Function {
public:
    double getFunctionValue(vector<double> x) override;

private:
    double getSquaredSum(vector<double> x) override ;
};


#endif //ZADANIE1_SALOMONSFUNCTION_H
