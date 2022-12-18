#include "services/GameService.c"

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char myID[MAX_ID_SIZE];
    char param[MAX_LINE];
    char action[MAX_ACTION];

    scanf("PLAYERS %[^\n]\n", param);

    scanf("YOU %s\n", myID);

    scanf("HAND %[^\n]\n", param);
    Hand myHand = readHand(param);
    
    int handSize = 7;

    scanf("TABLE %s\n", param);
    Card tableCard = readCard(param);

    Action currAct;
    bool tableChecked;

    while (1) {
        do // Listening
        {
            tableChecked = false;
            scanf("%s %s", action, param);
            
            currAct = readAction(action);

            if (currAct == DISCARD)
            {
                tableCard = readCard(param);

                if (canChangeColor(tableCard))
                {
                    scanf("%s", param);
                    tableCard.suit = readSuit(param);
                }
            }
            else if (currAct == BUY)
            {
                scanf("%[^\n]s", param);
                
                tableChecked = true;
            }

        } while (currAct != TURN || !checkMyTurn(param, myID));

        // My turn
        int toBuy = checkTableToBuy(tableCard, &tableChecked);

        if (toBuy == 0)
        {
            toBuy = 1;

            for (int i = 0; i < handSize; i++)
            {
                if (canPutTable(myHand[i], tableCard))
                {
                    discard(myHand[i], &tableCard);
                    dropCardAndUpdate(i, myHand, &handSize);

                    toBuy = 0;
                    break;
                }
            }
        }
        if (toBuy > 0)
        {
            say("Baka Baka!! ᗜ-ᗜ");
            buy(toBuy);

            for (int i = 0; i < toBuy; i++)
            {
                scanf("%s", param);
                addCardAndUpdate(readCard(param), myHand, &handSize);
            }
        }
    }

    free(myHand);

    return 0;
}