#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

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
bool checkMyTurn(char* id, char* myID)
{
    return strcasecmp(id, myID) == 0;
}

Hand discardAndUpdate(Hand hand, int index, int handSize)
{
    Hand newHand = malloc((handSize - 1) * sizeof(Card));

    for (int i = 0, j = 0; i < handSize; i++, j++)
    {
        if (i == index) i++;

        newHand[j] = hand[i];
    }

    printf("DISCARD %s", getCard(hand[index]));

    if (hand[index].value == A)
    {
        printf("%s", getSuit(newHand[0]));
    }

    printf("\n");

    return newHand;
}

bool checkTableAndAct(Card table)
{
    if (table.value != V && table.value != C)
    {
        return false;
    }

    if (table.value == V) buy(2);
    if (table.value == C) buy(4);

    return true;
}

#endif