# Blackjack

Requirements
------------
1. Dealer must hit on soft 17
2. Single Deck. The deck is shuffled every 6 rounds
3. Player is not allowed to split cards
4. Keep track of win percentage for the player
5. Provide a readme file explaining how to compile the source and other info that might be interesting

You don't have to implement any AI other than the one mentioned above - it's just one player vs. dealer

Steps to compile and run on Mac OS X
------------------------------------
1. Install gcc or clang compiler on Mac OS X
   Followed steps from https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/
2. Copy source code to preferred location on your computer (/Documents/Program/Blackjack)
3. Launch terminal and go to the program location (/Documents/Program/Blackjack)
3. Compile using below command (with -std=c++11 option as shown)
   `g++ -std=c++11 -o blackjack Blackjack.cpp Dealer.cpp Player.cpp Shuffler.cpp Card.cpp`
4. Run the generated executable (blackjack) using below command
   `./blackjack`

Implemention summary
--------------------
The classes and data structures are designed and implemented to support multiple players - single dealer use case. But currently console support is given only for single player - single dealer use case.

1. Dealer: Maintains player queue and shuffler. Inits deck and gives it to shuffler. Talks to the console and proceeds with the game. Calls distribute, dealPlayers, dealSelf, compareForWin in sequence for each round
2. Player: Responsible for maintaining player info such as ID, hand (list of cards for a round), state (active/passive to indicate if he is playing), number of wins/losses/rounds
3. Shuffler: Responsible for shuffling and maintaining card deck from which cards are drawn. Shuffler is refreshed with a fresh deck after every 6 rounds. In event where cards are exhausted before 6 rounds (which is unlikely in a single player scenario), the discarded cards from earlier rounds are given to the shuffler
4. Card: Maintains card info such as card suit (Club, diamond, heart, spade) and type (J/Q/K/A/PIP) and value
5. Blackjack: Entry class that instantiates the Dealer and starts play

Player win conditions
---------------------
1. Get 21 points on the player's first two cards (called a "blackjack" or "natural")
2. Reach a final score higher than the dealer without exceeding 21; or
3. Let the dealer draw additional cards until their hand exceeds 21 ("busted")

Player lose conditions
----------------------
1. Reach a final score lower than dealer
2. Draws additional cards until his hand exceeds 21 ("busted")

If both player count = dealer count and less than 21, round is drawn

Reading from terminal
---------------------
1. Player is presented with play/exit option after each round
   `Starting a new round. Press Y to play, press N to exit`
2. Each card is printed as [Suit, Value]. Value can be a number/facecard/ace
3. Initial distribution: Player has two cards drawn and dealer top card is shown. Player can hit blackjack(PLAYER WINS)
3. Player turn: Player is asked if he wants to continue to draw. For every draw complete player hand is printed. Player can get 21 points(PLAYER WINS). Player can get busted(PLAYER LOSES)
   `Continue to draw.. Press H to hit, press S to stand`
4. Dealer turn: Once player is finished, dealer draws. For every draw complete dealer house is printed. Dealer can get busted(PLAYER WINS). Player count > dealer count(PLAYER WINS). Player count < dealer count (PLAYER LOSES). Player count == dealer count(ROUND DRAWN)
5. Round result and player stats are printed after the round
   `Player wins!! `
   `Player stats: rounds[2]:won[1]:lost[1]`

Example
-------
```
Example
-------
BLACKJACK
********************************************************
Starting a new round. Press Y to play, press N to exit
Y
Player hand
[heart:10]
[club:7]
Dealer top card
[club:J]
Continue to draw.. Press H to hit, press S to stand
S
Dealer house
[diamond:10]
[club:J]
Player lost!! 
Player stats: rounds[1]:won[0]:lost[1]
********************************************************
Starting a new round. Press Y to play, press N to exit
Y
Player hand
[club:8]
[diamond:Q]
Dealer top card
[club:3]
Continue to draw.. Press H to hit, press S to stand
S
Dealer house
[heart:2]
[club:3]
Dealer house
[heart:2]
[club:3]
[spade:9]
Dealer house
[heart:2]
[club:3]
[spade:9]
[heart:J]
Dealer busted!!
Player wins!! 
Player stats: rounds[2]:won[1]:lost[1]
********************************************************
Starting a new round. Press Y to play, press N to exit

```
