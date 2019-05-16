#include <iostream>
#include "Dealer.h"

#define NUM_MAX_PLAYERS 1
#define NUM_DECKS 1
#define SHUFFLE_INTERVAL 6

/**
 * Entry class that instantiates the Dealer and starts play
 */
int main()
{
  cout<<"BLACKJACK\n";
  unique_ptr<Dealer> dealer = unique_ptr<Dealer>(new Dealer(NUM_MAX_PLAYERS, NUM_DECKS, SHUFFLE_INTERVAL));
  dealer->play();
  cout<<"Exiting..\n";
  return 0;
}