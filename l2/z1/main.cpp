#include <iostream>

#include "SalomonsFunction.h"
#include "SimulatedAnnealing.h"

int main() {
    try {
        int t,x;
        cin >>t;
        vector<double>initial;
        for (int i = 0; i < 4; i++) {
            cin >>x;
            initial.push_back(x);
        }

        auto simulatedAnnealing=new SimulatedAnnealing(t,initial,new SalomonsFunction());
        simulatedAnnealing->search();
        simulatedAnnealing->printBestSolution();
        delete simulatedAnnealing;

    }catch (...){
        cout<<"Niepoprawne dane.\n";
    }

    return 0;
}
