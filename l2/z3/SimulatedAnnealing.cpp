//
// Created by asia on 19.04.2020.
//

#include "SimulatedAnnealing.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <cmath>
#include <random>
#include <cstdio>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(int time, Board *board) {
    this->timeLimit = time;
    this->board = board;
}

void SimulatedAnnealing::search() {
    time_t startTime = time(nullptr);
    string s = board->initPath();
    bestPath = s;
    string r;
    double temperature = timeLimit * 1000;
    while (time(nullptr) - startTime < timeLimit || temperature >= pow(10, -10)) {
        for (int i = 0; i < 10000; i++) {
            r = tweak(s);
            r = board->pathToExit(r);
            if (!r.empty()) {
                if (quality(r) < quality(s)) {
                    s = r;
                    break;
                }
                if (probability(r, s, temperature)) {
                    s = r;
                }
            }
            if ((time(nullptr) - startTime > timeLimit)) {
                break;
            }
        }
        temperature = decreaseTemperature(temperature);
        if (quality(s) < quality(bestPath)) {
            bestPath = s;
        }
    }

}

/**
 * Usuwa pojedyncze przeciwne ruchy np LR i DU
 * @param path
 * @return
 */
string SimulatedAnnealing::reduceOpposite(string path) {
    for (int i = 0; i < path.size() - 1; i++) {
        if ((path[i] == 'U' && path[i + 1] == 'D') || (path[i] == 'D' && path[i + 1] == 'U') ||
            (path[i] == 'R' && path[i + 1] == 'L') || (path[i] == 'L' && path[i + 1] == 'R')) {
            path.erase(i, 2);
        }
    }
    return path;
}

string SimulatedAnnealing::tweak(string path) {
    int i = getRandomNumber(0, path.size() - 1);
    int j = getRandomNumber(0, path.size() - 1);;
    swap(path[i], path[j]);
    return reduceOpposite(path);
}

int SimulatedAnnealing::quality(string path) {
    return path.size();
}

double SimulatedAnnealing::getRandomNumber(double a, double b) {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis(a, b);
    return dis(gen);
}

bool SimulatedAnnealing::probability(string r, string s, double temperature) {
    double number = getRandomNumber(0, 1);
    return number < exp((quality(s) - quality(r)) / temperature);
}

double SimulatedAnnealing::decreaseTemperature(double temperature) {
    return temperature * 0.95;
}

void SimulatedAnnealing::printBestPath() {
    cout << bestPath.length() << endl;
    cerr << bestPath << endl;
}

SimulatedAnnealing::~SimulatedAnnealing() {
    delete (board);
}


