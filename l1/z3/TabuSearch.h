#ifndef LIST1_TABUSEARCH_H
#define LIST1_TABUSEARCH_H


#include "Board.h"
#include <vector>
#include <map>

using namespace std;


class TabuSearch {
public:
    explicit TabuSearch(Board *salesman, int time);

    void tabuSearch();

    void printBestPath();

private:
    string bestPath;
    vector<string> tabuList;
    int tabuLegth;
    int timeLimit;
    int permutationCount;
    Board *board;


    bool notTabu(string path);

    string betterQuality(string path1, string path2);

    void addToTabu(string path);

    string pathPermutation(string path);

    string reduceOpposite(string path);
};


#endif //LIST1_TABUSEARCH_H
