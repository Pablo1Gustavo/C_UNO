#ifndef CARD_CONTROLLER
#define CARD_CONTROLLER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../definitions/Card.h"
#include "../definitions/Game.h"

Card readCard(char* cardIn)
{
    Card card;

    int i;

    for (i = 0 ;; i++)
    {
        char curr = cardIn[i];

        if (curr >= '1' && curr <= '9')
        {
            card.value = curr - '0';
        }
        else if (curr == '0') card.value = 10;

        else if (curr == 'V') card.value = V;
        else if (curr == 'D') card.value = D;
        else if (curr == 'R') card.value = R;
        else if (curr == 'C') card.value = C;

        else break;
    }

    char suitIN[4];

    for (int j = 0; cardIn[i] != '\0'; i++, j++)
    {
        suitIN[j] = cardIn[i];
    }

    if      (strcmp(suitIN, "♦") == 0) card.suit = DIAMONDS;
    else if (strcmp(suitIN, "♣") == 0) card.suit = CLUBS;
    else if (strcmp(suitIN, "♥") == 0) card.suit = HEARTS;
    else if (strcmp(suitIN, "♠") == 0) card.suit = SPADES;

    return card;
}

#endif