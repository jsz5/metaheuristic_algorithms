#ifndef LIST1_TABUSEARCH_H
#define LIST1_TABUSEARCH_H


#include "Salesman.h"
#include <vector>

using namespace std;

struct Tabu {
    int vertex;
    int time;
};

class TabuSearch {
public:
    explicit TabuSearch(Salesman *salesman, int time);

    void tabuSearch();

    void printBestPath();

private:
    vector<int> bestPath;
    vector<Tabu> tabuList;
    int tabuLegth;
    int timeLimit;
    Salesman *salesman;


    void removeOldFromTabu(int c);

    bool notTabu(int i, int j);

    vector<int> betterQuality(vector<int> path1, vector<int> path2);

    vector<int> findBestNeighbour(int c, int &noBetter, vector<int> initPath);
};


#endif //LIST1_TABUSEARCH_H
