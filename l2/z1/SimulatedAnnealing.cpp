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
SimulatedAnnealing::SimulatedAnnealing(int time, vector<double> initialSolution, Function *function) {
    this->timeLimit=time;
    this->initialSolution=initialSolution;
    this->function=function;
}

void SimulatedAnnealing::search() {
    time_t startTime = time(nullptr);
    vector<double> s=initialSolution;
    bestSolution=s;
    vector<double> r;
    double temperature=timeLimit*1000;
    while (time(nullptr) - startTime < timeLimit && temperature>=pow(10,-10)) {
        for (int i=0;i<10000; i++) {
            r = tweak(s, temperature);
            if(quality(r) < quality(s) ){
                s=r;
                break;
            }
            if (probability(r, s, temperature)) {
                s = r;
            }
            if ((time(nullptr) - startTime >timeLimit)){
                break;
            }
        }
        temperature=decreaseTemperature(temperature);
        if(quality(s)<quality(bestSolution)){
            bestSolution=s;
        }
    }

}

vector<double> SimulatedAnnealing::tweak(vector<double> solution,double temperature) {
    double range=0;
    for (double & i : solution) {
        range+=abs(i);
    }
    range/=4;
    for (double & i : solution) {
        i+=getRandomNumber(-range,range);
    }
    return solution;
}

double SimulatedAnnealing::quality(vector<double> solution) {
    return function->getFunctionValue(solution);
}

double SimulatedAnnealing::getRandomNumber(double a, double b){
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(a, b);
    return dis(gen);
}
bool SimulatedAnnealing::probability(vector<double> r, vector<double> s, double temperature) {
    double number=getRandomNumber(0,1);
    return number<exp((quality(s)-quality(r))/temperature);
}

double SimulatedAnnealing::decreaseTemperature(double temperature) {
    return temperature*0.95;
}

void SimulatedAnnealing::printBestSolution() {
    for(double value:bestSolution){
        cout<<value<<" ";
    }
    cout<<function->getFunctionValue(bestSolution)<<endl;

}


