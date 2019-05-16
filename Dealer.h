#ifndef DEALER_H
#define DEALER_H

/**
 * Maintains player queue and shuffler. Talks to the console and proceeds with the game.
 * Calls distribute, dealPlayers, dealSelf, compareForWin in sequence for each round
 * 
 * Maintains a deck mapping between <Index, Card object>. Shuffler is given the
 * list of indeces (integers) to shuffle and keep. When a card needs to be drawn
 * from shuffler its index is drawn and dealer maps the index to card object. The card
 * object is then given to player or self
 */
#include <memory>
#include <vector>
#include <unordered_map>
#include "Shuffler.h"
#include "Player.h"
#include "Card.h"

using namespace std;

class Dealer {
public:
    Dealer(int numMaxPlayers, int numDecks, int shuffleInterval);
    ~Dealer(void);
    /**
     * Starts play
     */
    void play();
private:
    void initDeck();    
    /**
     * Sequence of actions for each round
     */
    void distribute();
    void dealPlayers();
    void dealSelf();
    void compareForWin();
    void offer(shared_ptr<Card> card);
    /*
     * Computes total for a hand
     */
    int getValue(vector<shared_ptr<Card>> hand);
    /*
     * Soft17 condition check
     */
    bool isSoft17();
    void resetPlayer(const shared_ptr<Player> player, Player::Result result);
    void resetHouse();
    int getNumActivePlayers();
    void printHouse();

    unique_ptr<Shuffler> mShuffler;
    vector<shared_ptr<Player>> mPlayerQueue;
    vector<shared_ptr<Card>> mHouse;
    // deck info
    vector<int> mDeck;
    unordered_map<int, shared_ptr<Card>> mDeckIndexMap;
    vector<int> mDiscards;
    // Info about num player, rounds, shuffle interval
    int mNumMaxPlayers;
    int mNumDecks;
    int mShuffleInterval;
    int mNumRounds;
};

#endif
