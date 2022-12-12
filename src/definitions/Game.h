#ifndef GAME_DEF
#define GAME_DEF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

typedef enum GameAction {
    SAY, DISCARD, BUY, TURN
} Action;

#endif