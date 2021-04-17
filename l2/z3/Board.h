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
    Field start;
    vector<Field> stops;

    bool** visited;
    string path;



public:
    Board(int n, int m);
    ~Board();
    void addField(int i, int j, int cost);

    string initPath();

    string pathToExit(string path1);

    bool checkWall(Field field);

    bool checkExit(Field field);

    bool findExit(int x, int y);
};


#endif //LIST1_BOARD_H
