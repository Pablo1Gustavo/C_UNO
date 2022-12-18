#ifndef GAME_SERVICE
#define GAME_SERVICE

#include "../definitions/Game.h"
#include "CardService.c"

void debugHand(Hand hand, int handSize)
{
    fprintf(stderr, "[ ");

    for (int i = 0; i < handSize; i++)
    {
        fprintf(stderr, "%s ", getCard(hand[i]));
    }

    fprintf(stderr, "]\n");
}

Hand readHand(char* complement)
{
    int cardsNum = 0;

    for (int i = 4; complement[i] != '\0'; i++)
    {
        if (complement[i] == ' ') cardsNum++;
    }

    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));

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
    if (strcmp(action, "SAY") == 0)     return SAY;
    if (strcmp(action, "DISCARD") == 0) return DISCARD;
    if (strcmp(action, "BUY") == 0)     return BUY;
    
    return TURN;
}


void say(char* message)
{
    printf("SAY \e[1m\x1b[41m\x1b[30m%s\033[0m\n", message);
}

void buy(int n)
{
    printf("BUY %d\n", n);
}

void discard(Card card, Card* tableCard)
{
    tableCard->value = card.value;
    tableCard->suit = card.suit;

    printf("DISCARD %s", getCard(card));

    if (canChangeColor(card))
    {
        printf(" %s", getSuit(card));
    }

    printf("\n");
}

bool checkMyTurn(char* id, char* myID)
{
    return strcasecmp(id, myID) == 0;
}

int checkTableToBuy(Card table, bool* tableChecked)
{
    if (*tableChecked) return 0;

    *tableChecked = true;

    if (table.value == V)   return 2;
    if (table.value == C)   return 4;

    return 0;
}

void dropCardAndUpdate(int index, Hand hand, int* handSize)
{
    for (int i = index; i < *handSize - 1; i++)
    {
        hand[i] = hand[i + 1];
    }

    (*handSize)--;
}

void addCardAndUpdate(Card newCard, Hand hand, int* handSize)
{
    hand[*handSize] = newCard;

    (*handSize)++;
}

#endif