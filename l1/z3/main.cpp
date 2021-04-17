#include <stdexcept>
#include "Board.h"
#include "TabuSearch.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

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
        auto tabuSearch = new TabuSearch(board, t);
        tabuSearch->tabuSearch();
        tabuSearch->printBestPath();
    }catch (...){
        cout<<"Niepoprawne dane.\n";
    }
}