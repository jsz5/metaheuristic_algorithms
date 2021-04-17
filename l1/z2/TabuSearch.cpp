#include "TabuSearch.h"
#include <iostream>
#include <ctime>



TabuSearch::TabuSearch(Salesman *salesman, int time) {
    this->salesman = salesman;
    this->tabuLegth = salesman->getN() / 2;
    this->timeLimit=time;
}

/**
 * Tabusearch dla problemu TSP
 */
void TabuSearch::tabuSearch() {
    time_t startTime = time(nullptr);
    bestPath = salesman->initPath();
    cout<<salesman->getPathCost(bestPath)<<endl;

    vector<int> localBestPath, path;
    int c = 0;
    int noBetter=0;
    vector<int> initPath=salesman->initPath();
    while (time(nullptr)- startTime < timeLimit) {
        path=initPath;
        localBestPath=initPath;
        while(noBetter<10000 && time(nullptr)- startTime < timeLimit) {
            c++;
            removeOldFromTabu(c);
            path = findBestNeighbour(c,noBetter, path);
            localBestPath = betterQuality(path, localBestPath);
            noBetter++;
        }
        bestPath = betterQuality(localBestPath, bestPath);
        initPath=salesman->randomPath();
        noBetter=0;
    }
}

/**
 * Permutuje ścieżkę zmieniając każde dwa wierzchołki
 * Szuka ścieżki o najmniejszym koszcie
 * Żaden z zamienianych wierzchołków nie może być w tabu
 * @param c
 * @param noBetter
 * @param initPath
 * @return
 */
vector<int> TabuSearch::findBestNeighbour(int c, int &noBetter, vector<int> initPath) {

    vector<int> path = initPath;
    vector<int> localBestPath = initPath;

    for (int i = 1; i < path.size() - 2; i++) {
        for (int j = i + 1; j < path.size() - 2; j++) {
            if (notTabu(i, j)) {
                swap(path[i], path[j]);
                if (salesman->getPathCost(path) < salesman->getPathCost(localBestPath)) {
                    localBestPath = path;
                    tabuList.push_back(Tabu{i, c});
                    tabuList.push_back(Tabu{j, c});
                }
                path = bestPath;
            }
        }
    }
    return localBestPath;
}


void TabuSearch::printBestPath() {
    cout<<salesman->getPathCost(bestPath)<<endl;
    for (int k : bestPath) {
        cout << k+1 << " ";
    }
    cout<<endl;
}
/**
 * Usuwa z listy tabu stare wierzchołki
 * @param c
 */
void TabuSearch::removeOldFromTabu(int c) {
    if (!tabuList.empty()) {
        if (c - tabuList.front().time > tabuLegth) {
            tabuList.erase(tabuList.begin());
            tabuList.erase(tabuList.begin());
        }
    }
}

/**
 * Sprawdza czy wierzchołek należy do tabu
 * @param i
 * @param j
 * @return
 */
bool TabuSearch::notTabu(int i, int j) {
    for (Tabu tabu:tabuList) {
        if (tabu.vertex == i || tabu.vertex == j) {
            return false;
        }
    }
    return true;
}

vector<int> TabuSearch::betterQuality(vector<int> path1, vector<int> path2) {
    if (salesman->getPathCost(path1) < salesman->getPathCost(path2)) {
        return path1;
    }
    return path2;
}

