#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../definitions/Card.h"
#include "../definitions/Game.h"
#include "CardController.c"

Hand readHand(char* complement)
{
    int cardsNum = 0;

    for (int i = 4; complement[i] != '\0'; i++)
    {
        if (complement[i] == ' ') cardsNum++;
    }

    Hand hand = malloc(cardsNum * sizeof(Card));

    char* t = strtok(strdup(complement), " ");
    
    for (int i = 0; i < cardsNum; i++)
    {
        t = strtok(NULL, " ");
        
        hand[i] = readCard(t);
    }

    return hand;
}

Action readAction(char* action)
{
    if (strcmp(action, "SAY") == 0)      return SAY;
    if (strcmp(action, "DISCARD") == 0)  return DISCARD;
    if (strcmp(action, "BUY") == 0)      return BUY;
}

#endif