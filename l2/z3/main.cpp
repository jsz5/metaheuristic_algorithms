#include <iostream>
#include "Board.h"
#include "SimulatedAnnealing.h"

using namespace std;




int main() {
    try {
        int t,n,m;
        cin >>t>>n>>m;
        string field;
        auto *board = new Board(n, m);
        for (int i = 0; i < n; i++) {
            cin >>field;
            for (int j = 0; j < m; j++) {
                board->addField(i, j, field[j] - 48);
            }
        }
  
        auto *simulatedAnnealing=new SimulatedAnnealing(t, board);
        simulatedAnnealing->search();
        simulatedAnnealing->printBestPath();
        delete simulatedAnnealing;

    }catch (...){
        cout<<"Niepoprawne dane.\n";
    }

}
