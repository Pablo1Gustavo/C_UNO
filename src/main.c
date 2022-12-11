#include <stdio.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char temp[MAX_LINE];
    char my_id[MAX_ID_SIZE];

    scanf("PLAYERS %[^\n]s\n", temp);
    scanf("YOU %s\n", my_id);
    scanf("HAND %[^\n]s\n", temp);
    scanf("TABLE %s\n", temp);

    char id[MAX_ID_SIZE];
    char action[MAX_ACTION];
    char complement[MAX_LINE];

    while (1) {
        while (strcmp(action, "TURN") || strcmp(complement, my_id))
        {
            scanf("%s %s", action, complement);

        }
        debug("----- MINHA VEZ -----");

        char card[] = "A♥ ♥";
        printf("DISCARD %s\n", card);
    }

    return 0;
}