#include "services/GameService.c"
#include "services/PredictorService.c"

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char myID[MAX_ID_SIZE];
    char param[MAX_LINE];
    char action[MAX_ACTION];

    Analyzer opponentAnalyzer;
    Analyzer youAnalyzer;

    scanf("PLAYERS %[^\n]\n", param);

    scanf("YOU %s\n", myID);

    scanf("HAND %[^\n]\n", param);
    Hand myHand = readHand(param);
    
    int handSize = 7;

    scanf("TABLE %s\n", param);
    Card tableCard = readCard(param);

    initAnalyzer(&youAnalyzer, myHand, handSize);
    initAnalyzer(&opponentAnalyzer, NULL, 0);

    Action currAct;
    bool tableChecked;

    while (1) {
        do // Listening
        {
            scanf("%s %s", action, param);
            
            currAct = readAction(action);

            if (currAct == DISCARD)
            {
                tableCard = readCard(param);

                analyzeNew(&opponentAnalyzer, tableCard);

                if (canChangeColor(tableCard))
                {
                    scanf("%s", param);
                    tableCard.suit = readSuit(param);
                }

                tableChecked = false;
            }
            else if (currAct == BUY)
            {
                tableChecked = true;
            }

        } while (currAct != TURN || !checkMyTurn(param, myID));

        // My turn
        int toBuy = checkTableToBuy(tableCard, &tableChecked);

        if (toBuy == 0)
        {
            toBuy = 1;

            int index = chooseCard(youAnalyzer, opponentAnalyzer, tableCard, myHand, handSize);

            if (index != -1)
            {
                revertAnalyzer(&youAnalyzer, myHand[index]);

                discard(myHand[index], &tableCard, youAnalyzer);
                dropCardAndUpdate(index, myHand, &handSize);

                toBuy = 0;
            }
        }
        if (toBuy > 0)
        {
            say("Baka Baka!! ᗜ-ᗜ");
            buy(toBuy);

            for (int i = 0; i < toBuy; i++)
            {
                scanf("%s", param);

                Card newCard = readCard(param);
                
                analyzeNew(&youAnalyzer, newCard);
                addCardAndUpdate(newCard, myHand, &handSize);
            }
        }
    }

    free(myHand);

    return 0;
}