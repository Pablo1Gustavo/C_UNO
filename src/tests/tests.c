#include "testUtils.c"
#include "../services/CardService.c"
#include "../services/GameService.c"
#include "../services/PredictorService.c"

void testDeclareCard()
{
    Card card;
    card.suit = DIAMONDS;
    card.value = D;

    test("Declare a card",
        card.suit == DIAMONDS && card.value == D
    );
}

void testReadCard()
{
    Card card1 = readCard("4♥");
    Card card2 = readCard("10♣");
    Card card3 = readCard("C♠");
    Card card4 = readCard("V♦");

    test("Reading a card",
        card1.suit == HEARTS && card1.value == 4 &&
        card2.suit == CLUBS && card2.value == 10 &&
        card3.suit == SPADES && card3.value == C &&
        card4.suit == DIAMONDS && card4.value == V
    );
}

void testReadHand()
{
    Hand hand = readHand("[ 4♥ 10♣ C♠ V♦ A♥ ]");

    Hand handAssert = (Card[]){
        {4,HEARTS},
        {10,CLUBS},
        {C,SPADES},
        {V,DIAMONDS},
        {A,HEARTS}
    };

    test("Read the hand",
        assertHandsEquals(hand, handAssert, 4)
    );
    
    free(hand);
}

void testReadAction()
{
    test("Read the action",
        readAction("SAY") == SAY &&
        readAction("DISCARD") == DISCARD &&
        readAction("BUY") == BUY &&
        readAction("TURN") == TURN
    );
}

void testCanPutOnTable()
{
    Card cards[] = {
        {4,HEARTS},
        {4,CLUBS},
        {A,HEARTS},
        {V,DIAMONDS}
    };

    test("Check if can put card on table",
        canPutTable(cards[0], cards[1]) &&
        canPutTable(cards[0], cards[2]) &&
        !canPutTable(cards[0], cards[3]) &&
        !canPutTable(cards[2], cards[3])
    );
}

void testGetCard()
{
    Card cards[] = {
        {4,HEARTS},
        {10,CLUBS},
        {C,SPADES},
        {V,DIAMONDS},
        {7,HEARTS}
    };
    
    test("Get a card str",
        strcmp(getCard(cards[0]), "4♥") == 0 &&
        strcmp(getCard(cards[1]), "10♣") == 0 &&
        strcmp(getCard(cards[2]), "C♠") == 0 &&
        strcmp(getCard(cards[3]), "V♦") == 0 &&
        strcmp(getCard(cards[4]), "7♥") == 0
    );
}

void testdropCardAndUpdate()
{
    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    hand[0] = (Card){4,HEARTS};
    hand[1] = (Card){10,CLUBS};
    hand[2] = (Card){C,SPADES};
    hand[3] = (Card){V,DIAMONDS};
    hand[4] = (Card){A,HEARTS};
    hand[5] = (Card){10,DIAMONDS};

    Hand handAssert = (Card[]){
        {4,HEARTS},
        {10,DIAMONDS}
    };

    int handSize = 6;

    dropCardAndUpdate(1, hand, &handSize);
    dropCardAndUpdate(1, hand, &handSize);
    dropCardAndUpdate(1, hand, &handSize);
    dropCardAndUpdate(1, hand, &handSize);

    test("Discard and update hand",
        handSize == 2 &&
        assertHandsEquals(hand, handAssert, handSize)
    );

    free(hand);
}

void testAddAndUpdate()
{
    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    hand[0] = (Card){4,HEARTS};
    hand[1] = (Card){10,CLUBS};

    Hand handAssert = (Card[]){
        {4,HEARTS},
        {10,CLUBS},
        {9,CLUBS},
        {8,DIAMONDS},
        {V,SPADES},
        {A,SPADES}
    };

    int handSize= 2;

    addCardAndUpdate(handAssert[2], hand, &handSize);
    addCardAndUpdate(handAssert[3], hand, &handSize);
    addCardAndUpdate(handAssert[4], hand, &handSize);
    addCardAndUpdate(handAssert[5], hand, &handSize);

    test("Add cards and update hand",
        handSize == 6 &&
        assertHandsEquals(hand, handAssert, handSize)
    );

    free(hand);
}

void testAndDropAndUpdate()
{
    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    hand[0] = (Card){6,HEARTS};
    hand[1] = (Card){A,DIAMONDS};

    Hand handAssert = (Card[]){
        {6,HEARTS},
        {A,DIAMONDS},
        {V,SPADES},
        {A,SPADES}
    };

    int handSize= 2;

    addCardAndUpdate((Card){9,CLUBS}, hand, &handSize);
    dropCardAndUpdate(2, hand, &handSize);

    addCardAndUpdate((Card){8,DIAMONDS}, hand, &handSize);
    dropCardAndUpdate(2, hand, &handSize);

    addCardAndUpdate(handAssert[2], hand, &handSize);
    addCardAndUpdate(handAssert[3], hand, &handSize);

    test("Add and drop cards and update hand",
        handSize == 4 &&
        assertHandsEquals(hand, handAssert, handSize)
    );

    free(hand);
}

void testInitSelfAnalyzer()
{
    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    hand[0] = (Card){4,HEARTS};
    hand[1] = (Card){10,CLUBS};
    hand[2] = (Card){C,SPADES};
    hand[3] = (Card){V,DIAMONDS};
    hand[4] = (Card){A,HEARTS};
    hand[5] = (Card){10,DIAMONDS};

    Analyzer analyzer;

    initAnalyzer(&analyzer, hand, 6);

    test("Init self analyzer",
        analyzer.values[10] == 2 &&
        analyzer.values[C] == 1 &&
        analyzer.values[R] == 0 &&
        analyzer.suits[DIAMONDS] == 2 &&
        analyzer.suits[SPADES] == 1
    );

    free(hand);
}

void testInitOpponentAnalyzer()
{
    Analyzer analyzer;

    initAnalyzer(&analyzer, NULL, 0);

    bool assertAll = true;

    for (int i = 0; i < VALUES_NUM; i++)
    {
        assertAll &= analyzer.values[i] == 0;
    }
    for (int i = 0; i < SUITS_NUM; i++)
    {
        assertAll &= analyzer.suits[i] == 0;
    }

    test("Init opponent analyzer",
        assertAll
    );
}

void test_new_and_revert_analyzer()
{
    Analyzer analyzer;

    initAnalyzer(&analyzer, NULL, 0);
    
    analyzeNew(&analyzer, (Card){A,CLUBS});
    analyzeNew(&analyzer, (Card){10,CLUBS});
    analyzeNew(&analyzer, (Card){4,HEARTS});
    analyzeNew(&analyzer, (Card){4,HEARTS});

    revertAnalyzer(&analyzer, (Card){4,HEARTS});

    test("Add new and revert analyzer",
        analyzer.values[4] == 1 &&
        analyzer.values[A] == 1 &&
        analyzer.values[10] == 1 &&
        analyzer.suits[CLUBS] == 2 &&
        analyzer.suits[HEARTS] == 1
    );
}

int main()
{
    printf("===[ TESTS ]===\n");
    
    testDeclareCard();
    testReadCard();
    testReadHand();
    testReadAction();
    testCanPutOnTable();
    testGetCard();
    testAddAndUpdate();
    testdropCardAndUpdate();
    testAndDropAndUpdate();
    testInitSelfAnalyzer();
    test_new_and_revert_analyzer();
}