#ifndef PREDICTOR_SERVICE
#define PREDICTOR_SERVICE

#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "../definitions/Card.h"
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

int valueStatus(Analyzer self, Analyzer oppoent, Value value)
{
    int valueStatus = self.values[value] * SELF_WEIGHT;
    valueStatus -= oppoent.values[value] * OPPONENT_WEIGHT;

    return valueStatus;
}

int suitStatus(Analyzer self, Analyzer oppoent, Suit suit)
{
    int suitStatus = self.suits[suit] * SELF_WEIGHT;
    suitStatus -= oppoent.suits[suit] * OPPONENT_WEIGHT;

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
            int currValueStatus = valueStatus(self, opponent, hand[i].value);
            int currSuitStatus = suitStatus(self, opponent, hand[i].suit);

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
