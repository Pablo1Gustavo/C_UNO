#ifndef CARD_CONTROLLER
#define CARD_CONTROLLER

#include "../definitions/Card.h"

Value readValue(char* card)
{
    if      (card[1] == '0') return 10;
    else if (card[0] == 'A') return A;
    else if (card[0] == 'V') return V;
    else if (card[0] == 'D') return D;
    else if (card[0] == 'R') return R;
    else if (card[0] == 'C') return C;

    return card[0] - '0';
}

Suit readSuit(char* suit)
{
    if      (strcmp(suit, "♦") == 0) return DIAMONDS;
    else if (strcmp(suit, "♣") == 0) return CLUBS;
    else if (strcmp(suit, "♥") == 0) return HEARTS;
    
    return SPADES;
}

Card readCard(char* cardIn)
{
    Card card;
    card.value = readValue(cardIn);

    char suit[4];

    int i = (cardIn[1] == '0') + 1;

    strcpy(suit, cardIn + i);

    card.suit = readSuit(suit);

    return card;
}

#endif