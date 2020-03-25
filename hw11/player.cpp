/*
 * player.cpp
 * COMP11 Splendor
 */

#include "player.h"

// Constructor function
Player::Player() {
  prestige = 0;
  for (int i = 0; i < 5; i++) {
    discount[i] = 0;
  }
  for (int i = 0; i < 5; i++) {
    gem_count[i] = 0;
  }
  for (int i = 0; i < 3; i++) {
    reserve[i] = nullptr;
  }
  purchasedCards = 0;
}

/* print
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Accesses different properties of the Players and prints.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::print() {
  for (int i = 0; i < 5; i++) {
    cout << "Discount is: " << discount[i] << endl;
  }
  for (int i = 0; i < 5; i++) {
    cout << "Gem count is: " << gem_count[i] << endl;
  }
  cout << "Prestige is: " << prestige << endl;
}

/* totalPrestige
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Return the prestige of a player
4)	Return Value: The prestige of a player
5)	Expectations about return value: Integer
*/
int Player::totalPrestige() {
  return this->prestige;
};

/* getGemCount
1)	Arguments: int color
2)	Expectations about arguments: The index number of a color
3)	Description: Return the number of gems of that color owned by a
Player.
4)	Return Value: The number of a particular gem owned
5)	Expectations about return value: Integer
*/
int Player::getGemCount(int color) {
  return this->gem_count[color];
};

/* getDiscount
1)	Arguments: int color
2)	Expectations about arguments: The index number of a color
3)	Description: Return the amount of discounts per color of gem owned by
a Player.
4)	Return Value: The number of discounts of a particular colored gem.
5)	Expectations about return value: Integer
*/
int Player::getDiscount(int color){
  return this->discount[color];
};

/* getReserve
1)	Arguments: int color
2)	Expectations about arguments: Index of reserved card possessed by Player
3)	Description: Returns reserved card owned by player
4)	Return Value: Pointer to a Card reserved by player
5)	Expectations about return value: Pointer to a Card object
*/
Card *Player::getReserve(int color){
  return this->reserve[color];
};

/* increaseGemCount
1)	Arguments: int color, int change
2)	Expectations about arguments: Color index of gem whose quantity needs to
be changed. The quantity change to be made.
3)	Description: Increases number of gems of a particular colors
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::increaseGemCount(int color, int change){
  this->gem_count[color] += change;
}

/* decreaseGemCount
1)	Arguments: int color, int change
2)	Expectations about arguments: Color index of gem whose quantity needs to
be changed. The quantity change to be made.
3)	Description: Decreases number of gems of a particular colors
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::decreaseGemCount(int color, int change){
  this->gem_count[color] -= change;
}

/* setReserve
1)	Arguments: Card *p, int index
2)	Expectations about arguments: First argument is a pointer to the Card
that we want to reserve. Second argument is the index of that card in the
Reserve array.
3)	Description: Sets a spot in the reserve array to be for a particular card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::setReserve(Card *p, int index) {
  this->reserve[index] = p;
}

/* setDiscount
1)	Arguments: int color
2)	Expectations about arguments: Index of color which we just got a discount
for.
3)	Description: Gives player discount for gems of a particular color.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::setDiscount(int color) {
  this->discount[color] += 1;
}

/* setPrestige
1)	Arguments: int amount
2)	Expectations about arguments: Amount of prestige points to be added
to the player.
3)	Description: Adds prestige points for a player.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::setPrestige(int amount) {
  this->prestige += amount;
}

/* sumOfGems
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Sums up the total number of gems owned by a player.
4)	Return Value: The total number of gems owned.
5)	Expectations about return value: An integer
*/
int Player::sumOfGems() {
  int sum = 0;
  for (int i = 0; i < 6; i++) {
    sum += getGemCount(i);
  }
  return sum;
}

/* sumOfGems
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Sums up the total number of cards purchased.
4)	Return Value: The total number of cards purchased.
5)	Expectations about return value: An integer
*/
int Player::getPurchasedCards() {
  return this->purchasedCards;
}

/* updatePurchasedCards
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Adds 1 to the total number of purchased cards.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Player::updatePurchasedCards() {
  this->purchasedCards += 1;
}
