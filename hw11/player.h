/*
 * card.h
 * COMP11 Splendor
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "card.h"
using namespace std;

class Player {
  public:
    // constructor
    Player();

    // destructor

    void initPlayer();

    // print for testing
    void print();

    // getters and setters
    int totalPrestige();
    int getGemCount(int color);
    int getDiscount(int color);
    Card *getReserve(int color);
    void increaseGemCount(int color, int change);
    void setReserve(Card* p, int index);
    void decreaseGemCount(int color, int change);
    void setDiscount(int color);
    void setPrestige(int change);
    int sumOfGems();
    int getPurchasedCards();
    void updatePurchasedCards();

  private:
    int gem_count[6];
    int prestige;
    int discount[5];
    Card *reserve[3];
    int purchasedCards;
};

#endif
