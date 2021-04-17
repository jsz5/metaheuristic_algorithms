//
// Created by asia on 19.04.2020.
//

#ifndef ZADANIE1_SIMULATEDANNEALING_H
#define ZADANIE1_SIMULATEDANNEALING_H


#include "Matrix.h"
#include "Square.h"
#include "Solution.h"
#include <vector>

using namespace std;

class SimulatedAnnealing {
public:
    SimulatedAnnealing(int time, Matrix *matrix);
    ~SimulatedAnnealing();

    void search();

    void printBestSolution();

private:
    static const int POSSIBLE_SIZE = 8;
    const int POSSIBLE_VALUES[POSSIBLE_SIZE] = {0, 32, 64, 128, 160, 192, 223, 255};
    Matrix *matrix;

    int timeLimit;
//    Solution *bestSolution;
    Solution  *initSolution();
    Solution * tweak(Solution  *solution);

    bool probability(Solution *r, Solution *s, double temperature);

    double decreaseTemperature(double temperature);

    int getRandomNumber(int a, int b);


};


#endif //ZADANIE1_SIMULATEDANNEALING_H
