#ifndef CARD_H
#define CARD_H

using namespace std;

/**
 * Maintains card info such as card suit (Club, diamond, heart, spade),
 * card type (J/Q/K/A/PIP) and card value
 */

static const char* suit_txt[] = {"club", "diamond", "heart", "spade"};
static const char* type_txt[] = {"A", "K", "Q", "J", "N"};

class Card
{
public:
    enum Suit {
        CLUB,
        DIAMOND,
        HEART,
        SPADE
    };

    enum Type {
        ACE,
        KING,
        QUEEN,
        JACK,
        PIP
    };

    Card(Suit suit, Type type, int value, int index);
    ~Card(void);
    Suit getSuit();
    Type getType();
    int getValue();
    int getIndex();
    void print();

private:
    const Suit mSuit;
    const Type mType;
    const int mValue;
    const int mIndex;
};

#endif
