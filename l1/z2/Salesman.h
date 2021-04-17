
#ifndef LIST1_SALESMAN_H
#define LIST1_SALESMAN_H

#include <vector>

using namespace std;

class Salesman {
private:
    int **graph;
    int n;

    int findMinEdge(int vertex, bool *visited);

public:
    explicit Salesman(int n);
    ~Salesman();

    int getN() const;

    void addEdge(int i, int j, int cost);

    int getPathCost(vector<int> path);

    vector<int> initPath();

    vector<int> randomPath();
};


#endif //LIST1_SALESMAN_H
