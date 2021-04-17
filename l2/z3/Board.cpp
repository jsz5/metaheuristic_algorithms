#include "Board.h"
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

Board::Board(int n, int m) {
    this->n = n;
    this->m = m;
    this->board = new int *[n];
    this->visited = new bool *[n];
    for (int i = 0; i < n; i++) {
        this->board[i] = new int[m];
        this->visited[i] = new bool[m];
    }
}


void Board::addField(int i, int j, int type) {
    if (type == 8) {
        stops.push_back(Field{i, j});
    }
    if (type == 5) {
        start = Field{i, j};
    }
    this->board[i][j] = type;
}


string Board::initPath()  {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
        }
    findExit(start.i, start.j);
    reverse(path.begin(), path.end());
    return path;
}

bool Board::findExit(int x, int y) {
    for (auto & stopField : stops) {
        if (x == stopField.i && y == stopField.j) {
            return true;
        }
    }
    if (board[x][y] == 1 || visited[x][y]) return false;
    visited[x][y] = true;
    if (x != 0) 
        if (findExit(x - 1, y)) {
            path.push_back('U');
            return true;
        }
    if (x != m - 1) 
        if (findExit(x + 1, y)) {
            path.push_back('D');
            return true;
        }
    if (y != 0)  
        if (findExit(x, y - 1)) {
            path.push_back('L');
            return true;
        }
    if (y != n - 1) 
        if (findExit(x, y + 1)) {
            path.push_back('R');
            return true;
        }
    return false;
}


/**
 * Zwraca true jeżeli field jest ścianą false w.p.p
 * @param field
 * @return
 */
bool Board::checkWall(Field field) {
    return board[field.i][field.j] == 1;
}

/**
 * Zwraca true jeżeli field jest wyjściem false w.p.p
 * @param field
 * @return
 */
bool Board::checkExit(Field field) {
    return board[field.i][field.j] == 8;
}

/**
 * Sprawdza czy ścieżka prowadzi do wyjścia
 * @param path
 * @return
 */
string Board::pathToExit(string path) {
    Field agent = start;
    for (int i = 0; i < path.size(); i++) {
        switch (path[i]) {
            case 'U':
                agent.i--;
                if (checkWall(agent)) {
                    return "";
                }
                if (checkExit(agent)) {

                    return  path.substr(0,i+1);
                }
                break;
            case 'D':
                agent.i++;
                if (checkWall(agent)) {
                    return "";
                }
                if (checkExit(agent)) {
                    return  path.substr(0,i+1);
                }
                break;
            case 'L':
                agent.j--;
                if (checkWall(agent)) {
                    return "";
                }
                if (checkExit(agent)) {
                    return  path.substr(0,i+1);
                }
                break;
            case 'R':
                agent.j++;
                if (checkWall(agent)) {
                    return "";
                }
                if (checkExit(agent)) {
                    return  path.substr(0,i+1);
                }
                break;
        }
    }
    return "";
}

Board::~Board() {
    for (int i = 0; i < n; i++) {
        delete[] board[i];
        delete []visited[i];
    }
    delete[] board;
    delete visited;
}
