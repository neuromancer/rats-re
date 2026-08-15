#ifndef RATS_TYPES_H
#define RATS_TYPES_H

typedef struct HighScore {
    char name[22];
    short level;
    long score;
} HighScore;

typedef struct BombData {
    int x;
    int y;
} BombData;

#endif
