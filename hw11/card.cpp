/*
 * card.cpp
 * COMP11 Splendor
 */

#include "card.h"

using namespace std;
// Card constructor
Card::Card() {
  // getDiscount
  for (int i = 0; i < 5; i++) {
    price[i] = 0;
  }
  prestige = 0;
  gem_color_discount = "";
  gem_index = 0;
}

/* print
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Accesses different properties of the Cards and prints.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Card::print() {
  for (int i = 0; i < 5; i++) {
    cout << "Price is: " << price[i] << endl;
  }
  cout << "Prestige is: " << prestige << endl;
  cout << "Discount color is: " << gem_color_discount << endl;
  cout << "Gem index is: " << gem_index << endl;
}

/* getPrice
1)	Arguments: int color
2)	Expectations about arguments: Index corresponding to a particular color
3)	Description: Accesses the value of the price array at that index.
4)	Return Value: A particular price of a certain colored gem.
5)	Expectations about return value: An integer
*/
int Card::getPrice(int color) {
  return price[color];
}

/* getPrestige
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Accesses prestige of a Card.
4)	Return Value: The prestige value of a Card
5)	Expectations about return value: An integer
*/
int Card::getPrestige() {
  return prestige;
};

/* getGemColor
1)	Arguments: N/A
2)	Expectations about arguments: N/A
3)	Description: Accesses the gem color that is discounted from a Card.
4)	Return Value: The color of the discounted gem on a Card
5)	Expectations about return value: A string
*/
string Card::getGemColor() {
  return gem_color_discount;
};

/* setPrestige
1)	Arguments: int prestige
2)	Expectations about arguments: The amount of prestige to be set on a Card.
3)	Description: Sets value of prestige property of a Card
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Card::setPrestige(int prestige){
  this->prestige = prestige;
};

/* setColor
1)	Arguments: string gem_color_discount
2)	Expectations about arguments: The color of the discounted gem
to be set on a Card.
3)	Description: Sets color of discounted gem on a Card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Card::setColor(string gem_color_discount){
  this->gem_color_discount = gem_color_discount;
}

/* setPrice
1)	Arguments: int gem_index, int color
2)	Expectations about arguments: First is the index of a particular color.
Second is the price of that particular colored gem on a Card.
3)	Description: Sets the price of different colored gems on a Card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Card::setPrice(int gem_index, int color){
  this->price[gem_index] = color;
}

// int main(int argc, char *argv[]){
//   if(argc < 2){
//       cerr << "ERROR: Expecting an input file!" << endl;
//       exit(EXIT_FAILURE);
//   }
//
//   cout << "LOL" << endl;
// }
