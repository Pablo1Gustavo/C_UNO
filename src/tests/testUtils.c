#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "../definitions/Card.h"

void test(char* name, bool result)
{
    if (result) printf("✅ \033[0;32m");
    else        printf("❌ \033[0;31m");

    printf(
        "%s: %s.\n",
        name,
        result ? "passed" : "failed"
    );

    printf("\033[0m");
}

bool assertHandsEquals(Hand a, Hand b, int len)
{
    bool assert = true;

    for (int i = 0; i < len; i++)
    {
        // printf("%d %d || %d %d\n", a[i].value, b[i].value, a[i].suit, b[i].suit);
        assert &= 
            a[i].value == b[i].value &&
            a[i].suit == b[i].suit
        ;
    }

    return assert;
}