#ifndef PREDICTOR_DEF
#define GAME_DEF

#include "Card.h"

#include <time.h>
#include <stdlib.h>

// weights and salts
#define SELF_WEIGHT 10
#define OPP_WEIGHT 4
#define CHOOSE_SPEC_CARD_PROB 70
#define DESIRED_SUIT_FREQ 35

// map to count values and suits
typedef struct
{
    int values[VALUES_NUM];
    int suits[SUITS_NUM];
}
Analyzer;

#endif
