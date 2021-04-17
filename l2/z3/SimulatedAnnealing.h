//
// Created by asia on 19.04.2020.
//

#ifndef ZADANIE1_SIMULATEDANNEALING_H
#define ZADANIE1_SIMULATEDANNEALING_H



#include "Board.h"


class SimulatedAnnealing {
public:

    SimulatedAnnealing(int time, Board *board);
    ~SimulatedAnnealing();

    void search();
    void printBestPath();

private:
    int timeLimit;
    string bestPath;
    Board *board;
    string tweak(string path);

    double decreaseTemperature(double temperature);

    string reduceOpposite(string path);

    int quality(string path);

    bool probability(string r, string s, double temperature);

    double getRandomNumber(double a, double b);


};


#endif //ZADANIE1_SIMULATEDANNEALING_H
