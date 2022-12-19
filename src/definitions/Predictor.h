#ifndef PREDICTOR_DEF
#define GAME_DEF

#include "Card.h"

#define SELF_WEIGHT 1
#define OPPONENT_WEIGHT 0

// map to count values and suits
typedef struct
{
    int values[VALUES_NUM];
    int suits[SUITS_NUM];
}
Analyzer;

#endif
