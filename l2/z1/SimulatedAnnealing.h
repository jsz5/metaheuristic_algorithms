//
// Created by asia on 19.04.2020.
//

#ifndef ZADANIE1_SIMULATEDANNEALING_H
#define ZADANIE1_SIMULATEDANNEALING_H


#include "SalomonsFunction.h"



class SimulatedAnnealing {
public:
    SimulatedAnnealing(int time, vector<double> initialSolution, Function *function);
    void search();
    void printBestSolution();

private:
    int timeLimit;
    Function *function;
    vector<double> initialSolution;
    vector<double> bestSolution;
    vector<double> tweak(vector<double> solution,double temperature);
    double quality(vector<double> solution);
    bool probability(vector<double> r,vector<double> s,double temperature);
    double decreaseTemperature(double temperature);


    double getRandomNumber(double a, double b);
};


#endif //ZADANIE1_SIMULATEDANNEALING_H
