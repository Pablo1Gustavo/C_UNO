#ifndef CARD_DEF
#define CARD_DEF

#define VALUES_NUM 15
#define SUITS_NUM 4

typedef enum {
    A = 0,
    // 1..10
    V = 11,
    D = 12,
    R = 13,
    C = 14
}
Value;

// ♦ ♣ ♥ ♠
typedef enum {
    DIAMONDS,
    CLUBS,
    HEARTS,
    SPADES
} Suit;

typedef struct
{
    Value value;
    Suit suit;
}
Card;

typedef Card* Hand;

#endif