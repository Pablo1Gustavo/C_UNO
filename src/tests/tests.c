#include "testUtils.c"
#include "../controllers/GameController.c"
#include "../controllers/CardController.c"

void testDeclareCard()
{
    Card card;
    card.suit = DIAMONDS;
    card.value = D;

    test("Declaring a card",
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

    test("Reading the hand",
        assertHandsEquals(hand, handAssert, 4)
    );
}

void testReadAction()
{
    test("Reading the action",
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

    test("Checking if can put card on table",
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
    
    test("Getting a card str",
        strcmp(getCard(cards[0]), "4♥") == 0 &&
        strcmp(getCard(cards[1]), "10♣") == 0 &&
        strcmp(getCard(cards[2]), "C♠") == 0 &&
        strcmp(getCard(cards[3]), "V♦") == 0
    );
}

void testDiscardAndUpdate()
{
    Hand hand = (Card[]){
        {4,HEARTS},
        {10,CLUBS},
        {C,SPADES},
        {V,DIAMONDS},
        {A,HEARTS}
    };
    Hand handAssert = (Card[]){
        {4,HEARTS},
        {10,CLUBS},
        {V,DIAMONDS},
        {A,HEARTS}
    };

    hand = discardAndUpdate(hand, 2, 5);

    test("Reading the hand",
        assertHandsEquals(hand, handAssert, 4)
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
    testDiscardAndUpdate();
}