#ifndef LIST1_BOARD_H
#define LIST1_BOARD_H

#include <vector>
#include <string>

using namespace std;
struct Field {
    int i;
    int j;
};

class Board {
private:
    int **board;
    int n, m;
    Field start, stop;
    bool checkStop(Field stopCandidate, string &path, char direction);

    bool go(Field &agent, string &path, char direction);

public:
    Board(int n, int m);
    ~Board();
    void addField(int i, int j, int cost);

    void printBoard();

    string initPath();
    int getSize();

    bool pathToExit(string path1);

    bool checkWall(Field field);

    bool checkExit(Field field);
};


#endif //LIST1_BOARD_H
