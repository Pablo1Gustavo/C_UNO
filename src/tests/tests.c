#include <stdbool.h>

#include "testUtils.c"
#include "../definitions/Card.h"
#include "../definitions/Game.h"
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
    Card card2 = readCard("2♣");
    Card card3 = readCard("C♠");
    Card card4 = readCard("V♦");

    test("Reading a card",
        card1.suit == HEARTS && card1.value == 4 &&
        card2.suit == CLUBS && card2.value == 2 &&
        card3.suit == SPADES && card3.value == C &&
        card4.suit == DIAMONDS && card4.value == V
    );
}

void testReadHand()
{
    Hand hand = readHand("[ 4♥ 2♣ C♠ V♦ ]");

    Hand handAssert = (Card[]){
        {4,HEARTS},
        {2,CLUBS},
        {C,SPADES},
        {V,DIAMONDS}
    };

    test("Reading the hand",
        assertHandsEquals(hand, 4, handAssert, 4)
    );
}

void testReadAction()
{
    test("Reading the action",
        readAction("SAY") == SAY &&
        readAction("DISCARD") == DISCARD &&
        readAction("BUY") == BUY
    );
}

int main()
{
    printf("===[ TESTS ]===\n");
    
    testDeclareCard();
    testReadCard();
    testReadHand();
    testReadAction();
}