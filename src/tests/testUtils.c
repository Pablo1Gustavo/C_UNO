#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../definitions/Card.h"

void test(char* name, bool result)
{
    if (result) printf("✅ \033[0;32m");
    else        printf("❌ \033[0;31m");

    printf(
        "%s: %s\n",
        name,
        result ? "passed" : "failed"
    );

    printf("\033[0m");
}

bool assertHandsEquals(Hand a, int lenA, Hand b, int lenB)
{
    bool assert = true;

    int maxLen = lenA > lenB ? lenA : lenB; 

    for (int i = 0; i < maxLen; i++)
    {
        assert &= 
            a[i].value == b[i].value &&
            a[i].suit == b[i].suit
        ;
    }

    return assert;
}