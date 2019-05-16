# Blackjack

Requirements
------------
•   Dealer must hit on soft 17
•   Single Deck. The deck is shuffled every 6 rounds.
•   Player is not allowed to split cards.
•   Keep track of win percentage for the player.
•   Provide a readme file explaining how to compile the source and other info that might be interesting.

You don't have to implement any AI other than the one mentioned above - it's just one player vs. dealer.

Steps to compile and run on Mac OS X
------------------------------------
1. Install gcc compiler on Mac OS X
   Followed steps from https://www.mkyong.com/mac/how-to-install-gcc-compiler-on-mac-os-x/
2. Copy source code to a preferred location on your computer (/Documents/Program/Blackjack)
3. Launch terminal and go to the program location (/Documents/Program/Blackjack)
3. Compile using below command with -std=c++11 option
   g++ -std=c++11 -o blackjack Blackjack.cpp Dealer.cpp Player.cpp Shuffler.cpp Card.cpp
4. Run using below command
   ./blackjack

Player win conditions
---------------------
1. Get 21 points on the player's first two cards (called a "blackjack" or "natural"), without a dealer blackjack;
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
   "Starting a new round. Press Y to play, press N to exit"
2. Each card is printed as [Suit, Value]. Value can be a number/facecard/ace
3. Initial distribution: Player has two cards drawn and dealer top card is shown.
   a. Player can hit blackjack - Player wins!!
3. Player turn: Player is asked if he wants to continue to draw. For every draw complete player hand is printed
   a. Player can get 21 points - Player wins!!
   b. Player can get get busted - Player loses!!
4. Dealer turn: Once player is finished, dealer draws. For every draw complete dealer house is printed
   a. Dealer can get busted - Player wins!!
   b. Player count > dealer count - Player wins!!
   c. Player count < dealer count - Player loses!!
   d. Player count == dealer count - Round drawn!!
5. Round result and player stats are printed after the round

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

Implementation summary
----------------------

