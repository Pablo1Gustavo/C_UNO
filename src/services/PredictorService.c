#ifndef PREDICTOR_SERVICE
#define PREDICTOR_SERVICE

#include <string.h>
#include <limits.h>

#include "CardService.c"
#include "../definitions/Predictor.h"

void initAnalyzer(Analyzer* analyzer, Hand hand, int handSize)
{
    memset(analyzer->values, 0, VALUES_NUM * sizeof(Value));
    memset(analyzer->suits, 0, SUITS_NUM * sizeof(Suit));

    for (int i = 0; i < handSize; i++)
    {
        analyzer->values[hand[i].value]++;
        analyzer->suits[hand[i].suit]++;
    }
}

void analyzeNew(Analyzer* analyzer, Card card)
{
    analyzer->values[card.value]++;
    analyzer->suits[card.suit]++;
}

void revertAnalyzer(Analyzer* analyzer, Card card)
{
    analyzer->values[card.value]--;
    analyzer->suits[card.suit]--;
}

Suit chooseSuit(Analyzer self)
{
    Suit desired = DIAMONDS;

    for (Suit s = 0; s < SUITS_NUM; s++)
    {
        if (self.suits[s] > self.suits[desired])
        {
            desired = s;
        }
    }

    return desired;
}

int calcStatus(Analyzer self, Analyzer oppoent, Card card, bool isValue)
{
    if (isValue)
    {
        int valueStatus = self.values[card.value] * SELF_WEIGHT;
        valueStatus -= oppoent.values[card.value] * OPPONENT_WEIGHT;

        return valueStatus;
    }

    int suitStatus = self.suits[card.suit] * SELF_WEIGHT;
    suitStatus -= oppoent.suits[card.suit] * OPPONENT_WEIGHT;

    return suitStatus;
}

int chooseCard(Analyzer self, Analyzer opponent, Card table, Hand hand, int handSize)
{
    int max = INT_MIN;
    int maxIndex = -1;

    for (int i = 0; i < handSize; i++)
    {
        if (canPutTable(hand[i], table))
        {
            int currValueStatus   = calcStatus(self, opponent, hand[i], 1);
            int currSuitStatus    = calcStatus(self, opponent, hand[i], 0);

            if (currValueStatus + currSuitStatus > max)
            {
                max = currValueStatus + currSuitStatus;
                maxIndex = i;
            }
        }
    }

    return maxIndex;
}

#endif
