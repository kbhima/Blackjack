#ifndef PLAYER_H
#define PLAYER_H

#include<vector>
#include"Card.h"

using namespace std;

/**
 * Responsible for maintaining player info such as ID, hand (list of cards
 * for a round), state (active/passive to indicate if he is playing),
 * number of wins/losses/rounds
 */

class Player {
public:
    enum State {
        PASSIVE,
        ACTIVE
    };

    enum Result {
        WIN,
        LOSE,
        DRAW
    };

    Player(int id);
    ~Player(void);
    /*
     * Offer card to player on hit
     */
    void offer(shared_ptr<Card> card);
    /*
     * Get player hand
     */
    vector<shared_ptr<Card>> getHand();
    void printHand();
    /*
     * Reset hand after each round
     */
    void resetHand(Result result);
    State getState();
    void setState(State state);
    int getID();

private:
    const int mID;
    State mState;
    vector<shared_ptr<Card>> mHand;
    int mNumWins;
    int mNumLosses;
    int mNumRounds;
};

#endif
