//
// Created by asia on 19.04.2020.
//

#include "SimulatedAnnealing.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(int time, Matrix *matrix) {
    this->timeLimit = time;
    this->matrix = matrix;

}

void SimulatedAnnealing::search() {
    time_t startTime = time(nullptr);
    Solution *s = initSolution();
    Solution *bestSolution=s;
    double temperature = timeLimit * 10000;
    while (time(nullptr) - startTime < timeLimit && temperature >= pow(10, -5)) {
        for (int i = 0; i < 500; i++) {
            Solution *r = tweak(s);
            if (r->getDistance() < s->getDistance()) {
                s = new Solution(r);
                break;
            }
            else if (probability(r, s, temperature)) {
                s  = new Solution(r);
            }
            delete r;
        }
        temperature = decreaseTemperature(temperature);
        if (s->getDistance() < bestSolution->getDistance()) {
           bestSolution = new Solution(s);
        }
        if(temperature < pow(10, -5)){
            break;
        }
    }
    delete s;
    cout<<bestSolution->getDistance()<<endl;
    bestSolution->printSolution();
    delete bestSolution;

}

/**
 * Numery operacji:
 * Merge: 1-górny sąsiad, 2-prawy, 3-dolny, 4-lewy
 * Dzielenie: 5-w poziomie, 6-w pionie
 * @param solution
 * @param temperature
 * @return
 */
Solution *SimulatedAnnealing::tweak(Solution *solution) {
    auto *copy=new Solution(solution);
    int s=getRandomNumber(0,copy->getSquaresSize()-1);
    Square *square=copy->getSquare(s);
    vector<int > operations=copy->getPossibleOperations(square);
    if(operations.empty()){
        return copy;
    }
    int operation=operations[getRandomNumber(0,operations.size()-1)];

    if(operation==5){
        int partNumber=getRandomNumber(matrix->getK(),square->getHeight()-matrix->getK());
        copy->part(square,partNumber,operation);
    }else if(operation==6){
        int partNumber=getRandomNumber(matrix->getK(),square->getWidth()-matrix->getK());
        copy->part(square,partNumber,operation);
    }else{
        copy->merge(square,operation);
    }
    return copy;
}




int SimulatedAnnealing::getRandomNumber(int a, int b) {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

bool SimulatedAnnealing::probability(Solution* r, Solution *s, double temperature) {
    double number = getRandomNumber(0, 1);
    return number < exp((r->getDistance() - s->getDistance()) / temperature);
}

double SimulatedAnnealing::decreaseTemperature(double temperature) {
    return temperature *(1-0.001);
}

Solution *SimulatedAnnealing::initSolution() {
    vector< Square *>  initSquares;
    int columns = floor(matrix->getM() / matrix->getK());
    int rows = floor(matrix->getN() / matrix->getK());
    int x = 0, y = 0;
    int height, width;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            height = matrix->getK();
            width = matrix->getK();
            if (i == rows - 1) {
                height = matrix->getN() % matrix->getK() + matrix->getK();
            }
            if (j == columns - 1) {
                width = matrix->getM() % matrix->getK() + matrix->getK();
            }
            initSquares.push_back(new Square(x, y, height, width, matrix));
            y += matrix->getK();
        }
        x += matrix->getK();
        y = 0;
    }
    auto *initSolution=new Solution(initSquares,matrix);
    return initSolution;
}

SimulatedAnnealing::~SimulatedAnnealing() {
    delete matrix;

}


