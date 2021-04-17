#include "Board.h"
#include<iostream>

using namespace std;

Board::Board(int n, int m) {
    this->n = n;
    this->m = m;
    this->board = new int *[n];
    for (int i = 0; i < n; i++)
        this->board[i] = new int[m];
}


void Board::addField(int i, int j, int type) {
    if (type == 8) {
        stop = Field{i, j};
    }
    if (type == 5) {
        start = Field{i, j};
    }
    this->board[i][j] = type;
}

/**
 * Przy generowaniu x0 sprawdza, czy agent trafił na wyjście
 * @param stopCandidate
 * @param path
 * @param direction
 * @return
 */
bool Board::checkStop(Field stopCandidate, string &path, char direction) {
    if (stopCandidate.i == stop.i && stopCandidate.j == stop.j) {
        path.push_back(direction);
        return true;
    }
    return false;
}

/**
 * Przy generowaniu x0 metoda, kóra porusza agentem
 * Zwraca true, gdy agent trafił do wyjścia, false w przeciwnym wypadku
 * @param agent
 * @param path
 * @param direction
 * @return
 */
bool Board::go(Field &agent, string &path, char direction) {
    switch (direction) {
        case 'R':
            while (agent.j < m - 2) { //agent idzie w prawo przy górnej ścianie
                agent.j++;
                path.push_back('R');
                if (checkStop(Field{agent.i - 1, agent.j}, path, 'U')) {
                    return true;
                }
            }
            return checkStop(Field{agent.i, agent.j + 1}, path, 'R');
        case 'U':
            while (agent.i > 1) { //agent idzie do góry przy lewej ścianie
                agent.i--;
                path.push_back('U');
                if (checkStop(Field{agent.i, agent.j - 1}, path, 'L')) {
                    return true;
                }
            }
            return checkStop(Field{agent.i - 1, agent.j}, path, 'U');
        case 'L':
            while (agent.j > 1) { //agent idzie w lewo przy dolnej ścianie
                agent.j--;
                path.push_back('L');
                if (checkStop(Field{agent.i + 1, agent.j}, path, 'D')) {
                    return true;
                }
            }
            return checkStop(Field{agent.i, agent.j - 1}, path, 'L');
        case 'D':
            while (agent.i < n - 2) { //agent idzie w dół przy prawej ścianie
                agent.i++;
                path.push_back('D');
                if (checkStop(Field{agent.i, agent.j + 1}, path, 'R')) {
                    return true;
                }
            }
            return checkStop(Field{agent.i + 1, agent.j}, path, 'D');
    }
}

/**
 * Generuje x0. Agent porusza się najpierw w lewo do ściany, a następnie do góry, w prawo itd
 * okrążając całą plansze przy ściankach
 * @return
 */
string Board::initPath() {
    string path;
    Field agent = start;
    while (agent.j > 1) { //agent idzie w lewo do ściany
        agent.j--;
        path.push_back('L');
    }
    if (checkStop(Field{agent.i, agent.j - 1}, path, 'L')) {
        return path;
    }
    if (go(agent, path, 'U')) {
        return path;
    }
    if (go(agent, path, 'R')) {
        return path;
    }
    if (go(agent, path, 'D')) {
        return path;
    }
    if (go(agent, path, 'L')) {
        return path;
    }
    if (go(agent, path, 'U')) {
        return path;
    }
    return path;
}

int Board::getSize() {
    return n*m;
}
/**
 * Zwraca true jeżeli field jest ścianą false w.p.p
 * @param field
 * @return
 */
bool Board::checkWall(Field field){
    return board[field.i][field.j] == 1;
}
/**
 * Zwraca true jeżeli field jest wyjściem false w.p.p
 * @param field
 * @return
 */
bool Board::checkExit(Field field){
    return board[field.i][field.j] == 8;
}

/**
 * Sprawdza czy ścieżka prowadzi do wyjścia
 * @param path
 * @return
 */
bool Board::pathToExit(string path){
    Field agent=start;
    for(int i=0; i<path.size(); i++){
        switch(path[i]){
            case 'U':
                agent.i--;
                if(checkWall(agent)){
                    return false;
                }
                if(checkExit(agent)){
                    return true;
                }
                break;
            case 'D':
                agent.i++;
                if(checkWall(agent)){
                    return false;
                }
                if(checkExit(agent)){
                    return true;
                }
                break;
            case 'L':
                agent.j--;
                if(checkWall(agent)){
                    return false;
                }
                if(checkExit(agent)){
                    return true;
                }
                break;
            case 'R':
                agent.j++;
                if(checkWall(agent)){
                    return false;
                }
                if(checkExit(agent)){
                    return true;
                }
                break;
        }
    }
    return false;
}

Board::~Board() {
    for (int i = 0; i < n; i++) {
        delete[] board[i];
    }
    delete [] board;
}
