#include <iostream>
#include "Card.h"

Card::Card(Suit suit, Type type, int value, int index) 
  :  mSuit(suit),
     mType(type),
     mValue(value),
     mIndex(index) {
}

Card::~Card(void) {

}

Card::Suit Card::getSuit() {
    return mSuit;
}

Card::Type Card::getType() {
    return mType;
}

int Card::getValue() {
    return mValue;
}

int Card::getIndex() {
    return mIndex;
}

void Card::print() {
    if (mType == PIP) cout << "[" << suit_txt[mSuit] << ":" << mValue << "]\n";
    else cout << "[" << suit_txt[mSuit] << ":" << type_txt[mType] << "]\n";
}



