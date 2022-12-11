#ifndef CARD_DEF
#define CARD_DEF

typedef enum CardValue
{
    A = 0,
    // 1..10
    V = 11,
    D = 12,
    R = 13,
    C = 14
}
Value;

// ♦ ♣ ♥ ♠
typedef enum CardSuit {
    DIAMONDS, CLUBS, HEARTS, SPADES
} Suit;

typedef struct Card
{
    Value value;
    Suit suit;
}
Card;

typedef Card* Hand;

#endif