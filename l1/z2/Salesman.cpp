#include "Salesman.h"
#include<iostream>
#include <random>

using namespace std;

Salesman::Salesman(int n) {
    this->n = n;
    this->graph = new int *[n];
    for (int i = 0; i < n; i++) {
        this->graph[i] = new int[n];
    }
}

void Salesman::addEdge(int i, int j, int cost) {
    this->graph[i][j] = cost;
}
/**
 * Liczy koszt ścieżki
 * @param path
 * @return
 */
int Salesman::getPathCost(vector<int> path) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        cost += graph[path[i]][path[i + 1]];
    }
    return cost;
}

/**
 * Generuje początkową ścieżkę metodą zachłanną
 * @return
 */
vector<int> Salesman::initPath() {
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    vector<int> greedyPath;
    greedyPath.push_back(0);
    visited[0] = true;
    for (int i = 0; i < n; i++) {
        greedyPath.push_back(findMinEdge(greedyPath.back(), visited));
    }
    return greedyPath;
}
/**
 * Generuje losową ścieżkę zaczynającą się w pierwszym mieście
 * @return
 */
vector<int> Salesman::randomPath() {
    vector<int> randomPath;
    for (int i = 0; i < n; i++) {
        randomPath.push_back(i);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n - 1);
    for (int k = 1; k < n; k++) {
        int i = dis(gen);
        int j = dis(gen);
        swap(randomPath[i],randomPath[j]);
    }
    randomPath.push_back(0);
    return randomPath;
}

/**
 * Znajduje wierchołek, który ma najmniejszą odległość do vertex
 * Pomocnicza do initPath()
 * @param vertex
 * @param visited
 * @return
 */
int Salesman::findMinEdge(int vertex, bool *visited) {
    int minVertex = 0;
    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            minVertex = i;
            break;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            if (graph[vertex][i] < graph[vertex][minVertex]) {
                minVertex = i;
            }
        }
    }
    visited[minVertex] = true;
    return minVertex;
}

int Salesman::getN() const {
    return n;
}

Salesman::~Salesman() {
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete [] graph;
}
