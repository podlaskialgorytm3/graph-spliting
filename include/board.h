#ifndef BOARD_
#define BOARD_

typedef struct board
{
    int node; // -1 oznacza że nie istnieje taki node
    int x;
    int y;
    struct board *next;
} board, *boardPtr;

#endif