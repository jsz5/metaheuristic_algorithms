#include <stdexcept>
#include "Salesman.h"
#include "TabuSearch.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[]) {

    int t, n;
    cin >> t;
    cin >> n;
    int cost;
    auto *salesman = new Salesman(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost;
            salesman->addEdge(i, j, cost);
        }
    }
    auto tabuSearch = new TabuSearch(salesman, t);
    tabuSearch->tabuSearch();
    tabuSearch->printBestPath();


}