/*
 * card.h
 * COMP11 Splendor
 */

#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
using namespace std;

class Card {
  public:
    // constructor
    Card();

    void initCard();

    // print for testing
    void print();

    // getters
    int getPrice(int color);
    int getPrestige();
    string getGemColor();

    // setters
    void setPrestige(int prestige);
    void setColor(string gem_color);
    void setPrice(int index, int color);

    // read data
    bool readCard(ifstream infile);

  private:
    int price[5];
    int prestige;
    string gem_color_discount;
    int gem_index;
};

#endif
