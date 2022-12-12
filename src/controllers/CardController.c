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

bool canPutTable(Card card, Card table)
{
    return card.suit == table.suit || card.value == table.value;
}

char* getValue(Card card)
{
    char values[][2] = {"A","1","2","3","4","5","6","7","8","9","10","V","D","R","C"};

    char* value = values[card.value];

    return value;
}

char* getSuit(Card card)
{
    char suits[][4] = {"♦","♣","♥","♠"};

    char* suit = suits[card.suit];

    return suit;
}

char* getCard(Card card)
{
    char* result = malloc(6 * sizeof(char));

    strncpy(result, getValue(card), 2);

    strcpy(result + 1 + (card.value == 10), getSuit(card));

    return result;
}

#endif