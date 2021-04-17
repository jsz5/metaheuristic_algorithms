#include "TabuSearch.h"
#include <iostream>
#include <ctime>
#include <random>

TabuSearch::TabuSearch(Board *board, int time) {
    this->board = board;
    this->tabuLegth = 4 * board->getSize();
    this->timeLimit = time;
    this->permutationCount = board->getSize();
}

/**
 * Tabusearch znajduje najkrótszą ścieżkę do wyjścia przez agenta
 */
void TabuSearch::tabuSearch() {
    time_t startTime = time(nullptr);
    bestPath = board->initPath();
    string localBestPath = bestPath;
    string path= bestPath;
    int count=permutationCount;
    while (time(nullptr) - startTime < timeLimit) {
        localBestPath = bestPath;
        path= bestPath;
        while(time(nullptr) - startTime < timeLimit && count--){
            path = pathPermutation(path);
            localBestPath = betterQuality(path, localBestPath);
            addToTabu(path);
        }
        if (localBestPath.size() < bestPath.size() ) {
            bestPath=localBestPath;
        }
        count=permutationCount;
    }
}

 /**
  * Usuwa pojedyncze przeciwne ruchy np LR i DU
  * @param path
  * @return
  */
string TabuSearch::reduceOpposite(string path){
    for(int i=0; i<path.size()-1; i++){
        if((path[i]=='U'&&path[i+1]=='D')||(path[i]=='D'&&path[i+1]=='U')||(path[i]=='R'&&path[i+1]=='L')||(path[i]=='L'&&path[i+1]=='R')){
            path.erase(i,2);
        }
    }
    return path;
}


/**
 *  Permutuje na ścieżce losowo wybrane dwa ruchy
 * @param path
 * @return
 */
string TabuSearch::pathPermutation(string path){
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, path.size()-1);
    int i=dis(gen);
    int j=dis(gen);
    swap(path[i],path[j]);
    return reduceOpposite(path);
}


/**
 * Zwraca true jeżeli ruch nie jest tabu, false w.p.p
 * @param path
 * @return
 */
bool TabuSearch::notTabu(string path) {
    for (string tabu:tabuList) {
        if (tabu == path) {
            return false;
        }
    }
    return true;
}

/**
 * Zwraca lepszą ścieżkę (krótszą)
 * @param path1
 * @param path2
 * @return
 */
string TabuSearch::betterQuality(string path1, string path2) {
    if (board->pathToExit(path1) && notTabu(path1) && path1.size() < path2.size() ) {
        return path1;
    }
    return path2;
}

/**
 * Dodaje do tabu, a w przypadku gdy tabu ma maksymalną długość usuwa pierwszy element na zasadzie FIFO
 * @param path
 */
void TabuSearch::addToTabu(string path) {
    if (tabuList.size() == tabuLegth) {
        tabuList.erase(tabuList.begin());
    }
    tabuList.push_back(path);
}
/**
 * Długość ścieżki oraz ścieżka
 */
void TabuSearch::printBestPath() {
    cout<<bestPath.length()<<endl;
    cout<<bestPath<<endl;
}
