#ifndef PREDICTOR_SERVICE
#define PREDICTOR_SERVICE

#include <string.h>

#include "../definitions/Predictor.h"

void initAnalyzer(Analyzer* analyzer, Hand hand, int handSize)
{
    memset(analyzer->values, 0, VALUES_NUM * sizeof(int));
    memset(analyzer->suits, 0, SUITS_NUM * sizeof(int));

    for (int i = 0; i < handSize; i++)
    {
        analyzer->values[hand[i].value]++;
        analyzer->suits[hand[i].suit]++;
    }
}

#endif
