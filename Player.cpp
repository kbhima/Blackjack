#include <iostream>
#include "Player.h"

Player::Player(int id)
  : mID(id),
    mState(PASSIVE),
    mNumWins(0),
    mNumLosses(0),
    mNumRounds(0) {

}


Player::~Player(void) {

}

void Player::offer(shared_ptr<Card> card) {
    mHand.push_back(card);
}

vector<shared_ptr<Card>> Player::getHand() {
    return mHand;
}

void Player::printHand() {
    cout << "Player hand\n";
    for (auto& card : mHand) card->print();
}

void Player::resetHand(Result result) {
    if (result == WIN) {
        mNumWins++;
        cout << "Player wins!! \n";
    } else if (result == LOSE) {
        mNumLosses++;
        cout << "Player lost!! \n";
    } else {
        cout << "Round drawn!! \n";
    }
    mNumRounds++;
    mState = PASSIVE;
    mHand.clear();
    cout << "Player stats: rounds[" << mNumRounds << "]:won["<< mNumWins << "]:lost[" << mNumLosses << "]\n";
}

Player::State Player::getState() {
    return mState;
}

void Player::setState(Player::State state) {
    mState = state;
}

int Player::getID() {
    return mID;
}
