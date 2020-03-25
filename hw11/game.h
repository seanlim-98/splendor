/*
 * game.h
 * COMP11 Splendor
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "termfuncs.h"
#include "player.h"
#include "card.h"
#include "vector.h"
using namespace std;

class Game {
  public:
    //constructor
    Game(string filename, string play_nobles);

    // main gameplay
    void playGame();

    // initialize vectors
    Vector mines;
    Vector transport;
    Vector vendors;
    Vector nobles;

    // read data
    void readData(string filename);
    string indexToColor(int index);

    // setters
    void decreaseGemBank(int color, int change);
    void increaseGemBank(int color, int change);

    //  initialize players and gem bank
    int gem_bank[6];
    Player player_1;
    Player player_2;

    //query functions
    void p3_query(Player* curr_player, string color1, string color2, string color3);
    void p2_query(Player* curr_player, string color1);
    void r_query(Player* curr_player, string row, int index);
    void b_query(Player* curr_player, string row, int index);
    void br_query(Player* curr_player, int index);
    void gem_overflow(Player* curr_player, string color);
    void ask_gem_question(Player *curr_player);
    void turn(bool check_player1, bool game_over);
    bool check_win(Player* curr_player);

  private:
    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];
};

#endif
