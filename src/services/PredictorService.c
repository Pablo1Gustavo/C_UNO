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

Suit chooseMaxSuit(Analyzer self)
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


int findCardByValue(Value value, Card table, Hand hand, int handSize)
{
    for (int i = 0; i < handSize; i++)
    {
        if (canPutTable(hand[i], table) && hand[i].value == value)
        {
            return i;
        }
    }
    return -1;
}

int chooseSpecialCard(Card table, Hand hand, int handSize)
{
    int index_C = findCardByValue(C, table, hand, handSize);

    if (index_C > 0) return index_C;

    int index_V = findCardByValue(V, table, hand, handSize);

    if (index_V > 0) return index_V;

    int index_R = findCardByValue(R, table, hand, handSize);

    if (index_R > 0) return index_R;

    return -1;
}

int getMaxSuitFrequency(Analyzer self, int handSize)
{
    float maxFrequency = self.suits[chooseMaxSuit(self)] / (float)handSize;

    return maxFrequency * 100;
}

int valueStatus(Analyzer self, Analyzer oppoent, Value value)
{
    int valueStatus = self.values[value] * SELF_WEIGHT;
    valueStatus -= oppoent.values[value] * OPP_WEIGHT;

    return valueStatus;
}

int suitStatus(Analyzer self, Analyzer oppoent, Suit suit)
{
    int suitStatus = self.suits[suit] * SELF_WEIGHT;
    suitStatus -= oppoent.suits[suit] * OPP_WEIGHT;

    return suitStatus;
}


// random number between 0 and 100
int randomPercentage(int auxSeed)
{
    srand(time(NULL) + auxSeed);

    return rand() % 101;
}

int chooseCard(Analyzer self, Analyzer opponent, Card table, Hand hand, int handSize)
{
    int max = INT_MIN;
    int maxIndex = chooseSpecialCard(table, hand, handSize);

    if (maxIndex > 0 && randomPercentage(handSize) < CHOOSE_SPEC_CARD_PROB) 
    {
        return maxIndex;
    }

    int index_A =  findCardByValue(A, table, hand, handSize);

    if (index_A > 0 && handSize / getMaxSuitFrequency(self, handSize) > DESIRED_SUIT_FREQ)
    {
        return index_A;
    }

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
