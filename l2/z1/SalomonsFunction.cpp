//
// Created by asia on 19.04.2020.
//

#include <cmath>
#include <iostream>
#include "SalomonsFunction.h"


double SalomonsFunction::getFunctionValue(vector<double> x) {
    double sum=getSquaredSum(x);
    double root=sqrt(sum);
    return 1-cos(2*M_PI*root)+(0.1*root);
}

double SalomonsFunction::getSquaredSum(vector<double> x) {
    double result=0;
    for (double value : x) {
        result += pow(value, 2);
    }
    return result;
}
