#include "testUtils.c"
#include "../services/CardService.c"
#include "../services/GameService.c"

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
        {V,DIAMONDS}
    };
    
    test("Get a card str",
        strcmp(getCard(cards[0]), "4♥") == 0 &&
        strcmp(getCard(cards[1]), "10♣") == 0 &&
        strcmp(getCard(cards[2]), "C♠") == 0 &&
        strcmp(getCard(cards[3]), "V♦") == 0
    );
}

void testDiscardAndUpdate()
{
    Hand hand = malloc(6 * sizeof(Card));
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

    discardAndUpdate(hand, 1, &handSize);
    discardAndUpdate(hand, 1, &handSize);
    discardAndUpdate(hand, 1, &handSize);
    discardAndUpdate(hand, 1, &handSize);

    test("Discard and update hand",
        handSize == 2 &&
        assertHandsEquals(hand, handAssert, 2)
    );
}

void testAddAndUpdate()
{
    Hand hand = malloc(2 * sizeof(Card));
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
        assertHandsEquals(hand, handAssert, 6)
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
    testDiscardAndUpdate();
}