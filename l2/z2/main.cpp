#include <iostream>
#include "Matrix.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main(int argc, char *argv[]) {

    int t, n, m, k;
    cin >> t;
    cin >> n;
    cin >> m;
    cin >> k;
    int value;
    auto *matrix = new Matrix(n,m,k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> value;
            matrix->addValue(i, j, value);
        }
    }
    auto *simulated_annealing= new SimulatedAnnealing(t, matrix);
    simulated_annealing->search();
    delete simulated_annealing;
//    simulated_annealing->printBestSolution();



}