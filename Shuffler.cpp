#include <iostream>
#include <time.h>
#include "Shuffler.h"

Shuffler::Shuffler(vector<int>& deck)
  :  mDeck(deck) {
  shuffle();
}


Shuffler::~Shuffler(void) {

}

int Shuffler::draw() {
    int index = mDeck.back();
    //cout << "Draw index: " << index << "\n";
    mDeck.pop_back();
    return index;
}

bool Shuffler::isEmpty() {
    return mDeck.empty();
}

void Shuffler::refresh(vector<int>& deck) {
    mDeck.clear();
    mDeck = deck;
}

void Shuffler::shuffle() {
    // C++ rand() functions creates the same random sequence on a given list
    // every time the program runs.
    // The srand() function is used to set a different starting or seed point for the
    // rand() function. srand(time) ensures that a random sequence is generated
    // as time is different for every run.
    srand(time(0));
    for (int i = 0; i < mDeck.size(); i++) {
        int swapIndex = (int) rand() % (i+1);
        int temp = mDeck[swapIndex];
        mDeck[swapIndex] = mDeck[i];
        mDeck[i] = temp;
    }
}
