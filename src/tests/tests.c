#include "testUtils.c"
#include "../services/CardService.c"
#include "../services/GameService.c"
#include "../services/PredictorService.c"

void test_declare_card()
{
    Card card;
    card.suit = DIAMONDS;
    card.value = D;

    test("Declare a card",
        card.suit == DIAMONDS && card.value == D
    );
}

void test_read_card()
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

void test_read_hand()
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

void test_read_action()
{
    test("Read the action",
        readAction("SAY") == SAY &&
        readAction("DISCARD") == DISCARD &&
        readAction("BUY") == BUY &&
        readAction("TURN") == TURN
    );
}

void test_can_put_on_table()
{
    Card cards[] = {
        {4,HEARTS},
        {4,CLUBS},
        {A,HEARTS},
        {V,DIAMONDS}
    };

    test("Check if can put card on table",
        canPutTable(cards[0], cards[1]) &&
        canPutTable(cards[2], cards[3]) &&
        !canPutTable(cards[0], cards[3]) &&
        !canPutTable(cards[1], cards[3])
    );
}

void test_get_card()
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

void test_drop_card_and_update()
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

void test_add_and_update()
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

void test_add_drop_and_update()
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

void test_init_self_analyzer()
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

void test_init_opponent_analyzer()
{
    Analyzer analyzer;

    initAnalyzer(&analyzer, NULL, 0);

    bool assertAll = true;

    for (Value v = 0; v < VALUES_NUM; v++)
    {
        assertAll &= analyzer.values[v] == 0;
    }
    for (Suit s = 0; s < SUITS_NUM; s++)
    {
        assertAll &= analyzer.suits[s] == 0;
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

void test_get_max_suit_frequency()
{
    Hand hand = malloc(MAX_HAND_SIZE * sizeof(Card));
    hand[0] = (Card){4,DIAMONDS};
    hand[1] = (Card){10,CLUBS};
    hand[2] = (Card){C,SPADES};
    hand[3] = (Card){V,DIAMONDS};
    hand[4] = (Card){A,HEARTS};
    hand[5] = (Card){10,DIAMONDS};

    Analyzer analyzer;

    initAnalyzer(&analyzer, hand, 6);

    test("Get max suit frequency",
        getMaxSuitFrequency(analyzer, 6) == 50
    );
}

int main()
{
    printf("===[ TESTS ]===\n");
    
    test_declare_card();
    test_read_card();
    test_read_hand();
    test_read_action();
    test_can_put_on_table();
    test_get_card();
    test_add_and_update();
    test_drop_card_and_update();
    test_add_drop_and_update();
    test_init_self_analyzer();
    test_init_opponent_analyzer();
    test_new_and_revert_analyzer();
    test_get_max_suit_frequency();
}