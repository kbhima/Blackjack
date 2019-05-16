#include <iostream>
#include "Dealer.h"


Dealer::Dealer(int numMaxPlayers, int numDecks, int shuffleInterval)
  : mNumMaxPlayers(numMaxPlayers),
    mNumDecks(numDecks),
    mShuffleInterval(shuffleInterval),
    mNumRounds(0) {

    initDeck();
    mShuffler = unique_ptr<Shuffler>(new Shuffler(mDeck));
    mPlayerQueue.push_back(make_shared<Player>(1));
}


Dealer::~Dealer(void) {

}

void Dealer::play() {
    // Loop for each round
    while (true) {
        cout <<"********************************************************\n";
        cout << "Starting a new round. Press Y to play, press N to exit\n";
        while (true) {
            char c = ' ';
            cin >> c;
            if (c == 'N' || c == 'n') return;
            if (c == 'Y' || c == 'y') break;
            cout << "Invalid key entry. Press Y to play, press N to exit\n";
        }
        
        if (mNumRounds == mShuffleInterval) {
            mShuffler->refresh(mDeck);
            mNumRounds = 0;
        }
        mNumRounds++;
        distribute();
        if (getNumActivePlayers() > 0) dealPlayers();
        if (getNumActivePlayers() > 0) dealSelf();
        if (getNumActivePlayers() > 0) compareForWin();
        resetHouse();
    }
}

void Dealer::initDeck() {
    /*
     * Maintains a deck mapping between <Index, Card object>. Shuffler is given the
     * list of indeces (integers) to shuffle and keep. When a card needs to be drawn
     * from shuffler its index is drawn and dealer maps the index to card object. The card
     * object is then given to player or self
     */
    int index = 0;
    Card::Suit suits[] = { Card::Suit::CLUB, Card::Suit::DIAMOND, Card::Suit::HEART, Card::Suit::SPADE };
    Card::Type faces[] = { Card::Type::JACK, Card::Type::QUEEN, Card::Type::KING };

    for (int i = 0; i < mNumDecks; i++) {
        for (auto suit : suits) {
            for (int val = 2; val <= 10; val++) {
                shared_ptr<Card> card = make_shared<Card>(suit, Card::Type::PIP, val, index);
                mDeck.push_back(index);
                mDeckIndexMap[index] = card;
                index++;
            }

            for (auto face : faces) {
                shared_ptr<Card> card = make_shared<Card>(suit, face, 10, index);
                mDeck.push_back(index);
                mDeckIndexMap[index] = card;
                index++;
            }

            shared_ptr<Card> card = make_shared<Card>(suit, Card::Type::ACE, 1, index);
            mDeck.push_back(index);
            mDeckIndexMap[index] = card;
            index++;
        }
    }
}

void Dealer::distribute() {
    // Set all players to state ACTIVE for the round
    for (auto& player : mPlayerQueue) player->setState(Player::State::ACTIVE);

    // Initial set of draws for each player and the dealer
    for (int i = 0; i < 2; i++) {
        for (auto& player : mPlayerQueue) {
            /*
             * NOTE: You will notice mShuffler->isEmpty() check is done before
             * every draw in other places too.
             * Shuffler is refreshed with a fresh deck after every 6 rounds.
             * In event where cards are exhausted before 6 rounds (which is unlikely
             * in a single player scenario), the discarded cards from earlier
             * rounds are given to the shuffler. 
             */
            if (mShuffler->isEmpty()) mShuffler->refresh(mDiscards);
            int index = mShuffler->draw();
            auto card = mDeckIndexMap[index];
            player->offer(card);
        }

        if (mShuffler->isEmpty()) mShuffler->refresh(mDiscards);
        int index = mShuffler->draw();
        auto card = mDeckIndexMap[index];
        offer(card);
    }

    // Check for player Blackjack
    for (auto& player : mPlayerQueue) {
        player->printHand();
        if (getValue(player->getHand()) == 21) {
            cout << "Player blackjack!!\n";
            resetPlayer(player, Player::Result::WIN);
        }
    }

    // Present dealer's top card
    cout << "Dealer top card\n";
    mHouse[mHouse.size()-1]->print();
}

void Dealer::dealPlayers() {
    // Deal players one by one. Player is asked for hit or stand before each draw
    // Proceed to next player if either player stands or he is busted
    for (auto& player : mPlayerQueue) {
        if (player->getState() == Player::State::ACTIVE) {
            while (true) {
                if (getValue(player->getHand()) > 21) break;
                cout << "Continue to draw.. Press H to hit, press S to stand\n";
                char c = ' ';
                while (true) {
                    cin >> c;
                    if (c == 'H' || c == 'h' || c == 'S' || c == 's') break;
                    cout << "Invalid key entry. Press H to hit, press S to break\n";
                }
                if (c == 'S' || c == 's') break;
                if (mShuffler->isEmpty()) mShuffler->refresh(mDiscards);
                int index = mShuffler->draw();
                auto card = mDeckIndexMap[index];
                player->offer(card);
                player->printHand();
            }

            // Check for player busted
            if (getValue(player->getHand()) > 21) {
                cout << "Player busted!!\n";
                resetPlayer(player, Player::Result::LOSE);
            }

            // Check for player blackjack
            if (getValue(player->getHand()) == 21) {
                cout << "Player blackjack!!\n";
                resetPlayer(player, Player::Result::WIN);
            }
        }
    }
}

void Dealer::dealSelf() {
    // Deal house. Breaks if either value is > 17 or is hard17
    while (true) {
        printHouse();
        if (getValue(mHouse) >= 17 && !isSoft17()) break;
        if (mShuffler->isEmpty()) mShuffler->refresh(mDiscards);
        int index = mShuffler->draw();
        auto card = mDeckIndexMap[index];
        offer(card);
    }

    // Check for dealer busted
    if (getValue(mHouse) > 21) {
        cout << "Dealer busted!!\n";
        for (auto& player : mPlayerQueue) {
            if (player->getState() == Player::State::ACTIVE)
                resetPlayer(player, Player::Result::WIN);
        }
    }
}

void Dealer::compareForWin() {
    // Compare player and dealer hands
    for (auto& player : mPlayerQueue) {
        if (player->getState() == Player::State::ACTIVE) {
            resetPlayer(player, getValue(player->getHand()) > getValue(mHouse) ? Player::Result::WIN :
                getValue(player->getHand()) < getValue(mHouse) ? Player::Result::LOSE : Player::Result::DRAW);
        }
    }
}

void Dealer::offer(shared_ptr<Card> card) {
    mHouse.push_back(card);
}

int Dealer::getValue(vector<shared_ptr<Card>> hand) {
    /**
     * Compute the hand total. To get the best possible total when 
     * one or more ace is present, the foll. is done 
     * - Exclude one ace card and compute remaining total.
     * - If the remainining total is <= 10, then best total can be
     *   got by treating the excluded ace as 11.
     * - If remaining total is > 10, treating this ace (or any other
     *   ace in the hand) as 11 can bust it. So treat the ace as 1
     */
    bool isAcePresent = false;
    int total = 0;
    for (auto& card : hand) {
        if (!isAcePresent && (card->getType() == Card::Type::ACE)) {
            isAcePresent = true;
            continue;
        }
        total += card->getValue();
    }

    if (isAcePresent) {
        if (total <= 10) total += 11;
        else total += 1;
    }

    return total;
}

bool Dealer::isSoft17() {
    /*
     * Any blackjack hand that contains an ace counted as 11 is a soft hand.
     * Soft17 is when we hit 17, by counting an ace as 11.
     * - To check for soft17, check if atleast one ace is present.
     * - Treating this ace as 11, remaining total should be 6 for the
     *   net total to be 17
     */
    bool isAcePresent = false;
    int total = 0;
    for (int i = 0; i < mHouse.size(); i++) {
        if (!isAcePresent && mHouse[i]->getType() == Card::Type::ACE) {
            isAcePresent = true;
            continue;
        }
        total += mHouse[i]->getValue();
    }

    if (isAcePresent && total == 6) return true;
    return false;
}

void Dealer::resetPlayer(const shared_ptr<Player> player, Player::Result result) {
    for (auto& card : player->getHand()) mDiscards.push_back(card->getIndex());
    player->resetHand(result);
}

void Dealer::resetHouse() {
    for (auto& card : mHouse) mDiscards.push_back(card->getIndex());
    mHouse.clear();
}

int Dealer::getNumActivePlayers() {
    int count = 0;
    for (auto& player : mPlayerQueue) if (player->getState() == Player::State::ACTIVE) count++;
    return count;
}

void Dealer::printHouse() {
    cout << "Dealer house\n";
    for (auto& card : mHouse) card->print();
}
