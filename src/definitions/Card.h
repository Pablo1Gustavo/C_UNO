#ifndef CARD_MODEL
#define CARD_MODEL

typedef enum CardValue
{
    A = 0,
    // 1..9
    V = 11,
    D = 12,
    R = 13,
    C = 14
}
Value;

typedef enum CardSuit {
    DIAMONDS, CLUBS, HEARTS, SPADES
} Suit;

typedef struct Card
{
    Value value;
    Suit suit;
}
Card;

#endif