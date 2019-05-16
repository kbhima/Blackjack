#ifndef SHUFFLER_H
#define SHUFFLER_H

#include<vector>

using namespace std;

/**
 * Responsible for shuffling and maintaining card deck from which cards are drawn
 */

class Shuffler
{
public:
    Shuffler(vector<int>& deck);
    ~Shuffler(void);
    int draw();
    bool isEmpty();
    void refresh(vector<int>& deck);
    void shuffle();

private:
    vector<int> mDeck;
};

#endif

