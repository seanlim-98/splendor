/*
 * game.cpp
 * COMP11 Splendor
 */

#include "game.h"

// Constructor function
Game::Game(string filename, string play_nobles){
   //include nobles or not
   if(play_nobles == "true"){
        this->play_nobles = true;
   }else{
        this->play_nobles = false;
   }

   //initialize the board
   for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }
   // USe Player() constructor functions to make new Players
   player_1 = Player();
   player_2 = Player();

   // Read data
   readData(filename);

   // Display card decks (vectors)
   for (int i = 0; i < 3; i++) {
     for (int j = 0; j < 4; j++) {
       if (i == 0) {
         grid[i][j] = vendors.back();
         vendors.pop_back();
       } else if (i == 1) {
         grid[i][j] = transport.back();
         transport.pop_back();
       } else {
         grid[i][j] = mines.back();
         mines.pop_back();
       }
     }
   }

   // Set number of gems - all 4 except for gold which has 5.
   for (int i = 0; i < 5; i++) {
     gem_bank[i] = 4;
   }
   gem_bank[5] = 5;
}

/* readData
1)	Arguments: string filename
2)	Expectations about arguments: Name of data file we are reading in
3)	Description: Read data from the data file and store it in our Cards.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::readData(string filename) {
  ifstream infile(filename.c_str());
  istringstream line_stream;
  // Check if file opened properly
  if (infile.fail()) {
    cerr << "ERROR: Error opening file, please check file name" << filename
    << endl;
    exit(EXIT_FAILURE);
  }

  string line_info;
  // ignore header of data file
  getline(infile, line_info);
  string type, gem_color_discount;
  int prestige, white, red, pink, blue, green;

  for (int i = 0; i < 100; i++) {
    getline(infile, line_info);
    line_stream.str(line_info);

    line_stream >> type;

    if (type == "m") {
      Card *c = new Card();
      line_stream >> prestige >> gem_color_discount >> white >> red
      >> pink >> blue >> green;

      // Use setters to store data in Cards
      c->setPrestige(prestige);
      c->setColor(gem_color_discount);
      c->setPrice(0, white);
      c->setPrice(1, red);
      c->setPrice(2, pink);
      c->setPrice(3, blue);
      c->setPrice(4, green);

      mines.push_back(c);

      c = nullptr;
      delete c;
      line_stream.clear();

    } else if (type == "t") {
      Card *c = new Card();
      line_stream >> prestige >> gem_color_discount >> white >> red
      >> pink >> blue >> green;

      // Use setters to store data in Cards
      c->setPrestige(prestige);
      c->setColor(gem_color_discount);
      c->setPrice(0, white);
      c->setPrice(1, red);
      c->setPrice(2, pink);
      c->setPrice(3, blue);
      c->setPrice(4, green);

      transport.push_back(c);

      c = nullptr;
      delete c;
      line_stream.clear();

    } else if (type == "v") {
      Card *c = new Card();
      line_stream >> prestige >> gem_color_discount >> white >> red
      >> pink >> blue >> green;

      // Use setters to store data in Cards
      c->setPrestige(prestige);
      c->setColor(gem_color_discount);
      c->setPrice(0, white);
      c->setPrice(1, red);
      c->setPrice(2, pink);
      c->setPrice(3, blue);
      c->setPrice(4, green);

      vendors.push_back(c);

      c = nullptr;
      delete c;
      line_stream.clear();
    } else {
      Card *c = new Card();
      line_stream >> prestige >> gem_color_discount >> white >> red
      >> pink >> blue >> green;

      // Use setters to store data in Cards
      c->setPrestige(prestige);
      c->setPrice(0, white);
      c->setPrice(1, red);
      c->setPrice(2, pink);
      c->setPrice(3, blue);
      c->setPrice(4, green);

      nobles.push_back(c);

      c = nullptr;
      delete c;
      line_stream.clear();
    }
  }
}

/* turn
1)	Arguments: bool player1_turn, bool game_over
2)	Expectations about arguments: The first argument checks whether it is
player 1 or player 2's turn. The second argument checks if the game is over.
3)	Description: Asks for a query from the player.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::turn(bool player1_turn, bool game_over){
  Player* curr_player;
  Player* other_player;
  string player;

  // Set curr_player pointer to either Player 1 or 2
  if (player1_turn) {
    curr_player = &player_1;
    other_player = &player_2;
    player = "PLAYER 1";
  } else {
    curr_player = &player_2;
    other_player = &player_1;
    player = "PLAYER 2";
  }

  // Receive input query from user
  string query;
  cin >> query;
  if (query == "q") {
    // quits program
    screen_bg("white");
    screen_fg("black");
    game_over = true;
    std::exit(0);
  } else if (query == "p3") {
    // takes three more colors as inputs
    string color1;
    string color2;
    string color3;
    cin >> color1 >> color2 >> color3;
    string colors[5] = {"white", "red", "pink", "blue", "green"};

    // Check for availability for gems for each input color
    for (int i = 0; i < 5; i++) {
      if (color1 == colors[i]) {
        // Error if there are no more gems of that color to purchase
        if (gem_bank[i] == 0) {
          cout << "Invalid move (unavailable gems) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      if (color2 == colors[i]) {
        // Error if there are no more gems of that color to purchase
        if (gem_bank[i] == 0) {
          cout << "Invalid move (unavailable gems) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      if (color3 == colors[i]) {
        // Error if there are no more gems of that color to purchase
        if (gem_bank[i] == 0) {
          cout << "Invalid move (unavailable gems) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }

    // Check for duplicate colors
    if ((color1 == color2) || (color2 == color3) || (color3 == color1)) {
      cout << "Invalid move (duplicate color) - enter a valid move: ";
      turn(player1_turn, game_over);
      return;
    } else {
      // Check that the input color is one of the colors on the board
      for (int i = 0; i < 5; i++) {
        if (color1 == colors[i]) {
          break;
        } else if ((i == 4) && color1 != colors[i]) {
          cout << "Invalid move (invalid color) - enter a valid move: ";
          turn(player1_turn, game_over);
        }
      }
      // Check that the input color is one of the colors on the board
      for (int i = 0; i < 5; i++) {
        if (color2 == colors[i]) {
          break;
        } else if ((i == 4) && color2 != colors[i]) {
          cout << "Invalid move (invalid color) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
      // Check that the input color is one of the colors on the board
      for (int i = 0; i < 5; i++) {
        if (color3 == colors[i]) {
          break;
        } else if ((i == 4) && color3 != colors[i]) {
          cout << "Invalid move (invalid color) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }
    // Purchase 3 gems from board
    p3_query(curr_player, color1, color2, color3);

    // Check if there will be too many gems after purchase
    if (curr_player->sumOfGems() > 10) {
      string color;
      // Keep prompting return of gems until total gems is less than 10
      while (curr_player->sumOfGems() > 10) {
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();

        cout << " " << player << ", you have more than 10 gems! Name one gem" <<
        " you would like to return: ";
        cin >> color;

        // Error checking
        for (int i = 0; i < 5; i++) {
          if (color == colors[i]) {
            // Error if player tries to return a gem they don't have
            if (curr_player->getGemCount(i) == 0){
              ask_gem_question(curr_player);
            } else {
              // Execute return of gem
              gem_overflow(curr_player, color);
              break;
            }
          } else if ((i == 4) && color != colors[i]) {
            // Error if player tries to return a color other than the ones
            // on the board
            ask_gem_question(curr_player);
          }
        }
      }
    }

  } else if (query == "p2") {
    // Get input color and ignore all colors other than the first one
    string color1;
    cin >> color1;
    cin.ignore(100, '\n');

    string colors[5] = {"white", "red", "pink", "blue", "green"};
    // Check for availability of gems
    for (int i = 0; i < 5; i++) {
      if (color1 == colors[i]) {
        // Error if there is less than 2 of the gem in the bank
        if (gem_bank[i] <= 1) {
          cout << "Invalid move (unavailable gems) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }
    for (int i = 0; i < 5; i++) {
      if (color1 == colors[i]) {
        // Error if there is less than 4 of the gem in the bank
        if (gem_bank[i] < 4) {
          cout << "Invalid move (unavailable gems) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
        break;
      } else if ((i == 4) && color1 != colors[i]) {
        // Error if the color is different from the ones on the board
        cout << "Invalid move (invalid color) - enter a valid move: ";
        turn(player1_turn, game_over);
        return;
      }
    }
    // purchase 2 gems of same color from the bank
    p2_query(curr_player, color1);

    // Check if there will be too many gems after purchase
    if (curr_player->sumOfGems() > 10) {
      string color;
      // Keep prompting return of gems until total gems is less than 10
      while (curr_player->sumOfGems() > 10) {
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();

        cout << " " << player << ", you have more than 10 gems! Name one gem" <<
        " you would like to return: ";
        cin >> color;

        // Error checking
        for (int i = 0; i < 5; i++) {
          if (color == colors[i]) {
            // Error if player tries to return a gem they don't have
            if (curr_player->getGemCount(i) == 0){
              ask_gem_question(curr_player);
            } else {
              // Execute return of gem
              gem_overflow(curr_player, color);
              break;
            }
          } else if ((i == 4) && color != colors[i]) {
            // Error if player tries to return a color other than the ones
            // on the board
            ask_gem_question(curr_player);
          }
        }
      }
    }
  } else if (query == "r") {
    string row;
    int index;
    cin >> row >> index;

    if (index > 4) {
      // Error if player tries to reserve from invalid column
      cout << "Invalid move (Invalid card column) - enter a valid move: ";
      turn(player1_turn, game_over);
      return;
    }

    if (curr_player->getReserve(2) != nullptr) {
      // Error if player already has 3 reserved cards
      cout << "Invalid move (reserve is already full) - enter a valid move: ";
      turn(player1_turn, game_over);
      return;
    }

    // Reserve a card
    r_query(curr_player, row, index);

    string colors[5] = {"white", "red", "pink", "blue", "green"};

    /// Check if there will be too many gems after reserve
    if (curr_player->sumOfGems() > 10) {
      string color;
      // Keep prompting return of gems until total gems is less than 10
      while (curr_player->sumOfGems() > 10) {
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();

        cout << " " << player << ", you have more than 10 gems! Name one gem" <<
        " you would like to return: ";
        cin >> color;

        // Error checking
        for (int i = 0; i < 5; i++) {
          if (color == colors[i]) {
            // Error if player tries to return a gem they don't have
            if (curr_player->getGemCount(i) == 0){
              ask_gem_question(curr_player);
            } else {
              // Execute return of gem
              gem_overflow(curr_player, color);
              break;
            }
          } else if ((i == 4) && color != colors[i]) {
            // Error if player tries to return a color other than the ones
            // on the board
            ask_gem_question(curr_player);
          }
        }
      }
    }
  } else if (query == "b") {
    string row;
    int index;
    Card* bought_card;
    cin >> row >> index;

    if (row == "v") {
      bought_card = grid[0][index-1];
      for (int i = 0; i < 5; i++) {
        // Error if player doesn't have enough gems to buy card
        if ((curr_player->getGemCount(i) < bought_card->getPrice(i)) &&
            (curr_player->getGemCount(i) + curr_player->getGemCount(5)) <
            bought_card->getPrice(i)){
          cout << "Invalid move (cannot afford card) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    } else if (row == "t") {
      bought_card = grid[1][index-1];
      for (int i = 0; i < 5; i++) {
        // Error if player doesn't have enough gems to buy card
        if ((curr_player->getGemCount(i) < (bought_card->getPrice(i) -
            curr_player->getDiscount(i))) &&
            (curr_player->getGemCount(i) + curr_player->getGemCount(5)) <
            (bought_card->getPrice(i) - curr_player->getDiscount(i))){
          cout << "Invalid move (cannot afford card) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    } else if (row == "m") {
      bought_card = grid[2][index-1];
      for (int i = 0; i < 5; i++) {
        // Error if player doesn't have enough gems to buy card
        if ((curr_player->getGemCount(i) < (bought_card->getPrice(i) -
            curr_player->getDiscount(i))) &&
            (curr_player->getGemCount(i) + curr_player->getGemCount(5)) <
            (bought_card->getPrice(i) - curr_player->getDiscount(i))){
          cout << "Invalid move (cannot afford card) - enter a valid move: ";
          turn(player1_turn, game_over);
          return;
        }
      }
    }

    // Buy card of choice from specified row
    b_query(curr_player, row, index);

    /* Check for win - condition is Player 2 has a turn and doesn't have 15, so
    Player 1 wins */
    if((!check_win(curr_player) && !player1_turn) && (other_player->
      totalPrestige() >= 15)){
      cout << " Congratulations Player 1: YOU WIN!!!!" << endl;
      screen_bg("white");
      screen_fg("black");
      game_over = true;
      std::exit(0);
    }

    // If Current player has more than 15
    if(check_win(curr_player)){
      // If Player 2 gets more than 15
      if(!player1_turn){
        // If Player 2 is more than Player 1
        if(curr_player->totalPrestige() > other_player->totalPrestige()){
          cout << " Congratulations Player 2: YOU WIN!!!!" << endl;
          screen_bg("white");
          screen_fg("black");
          game_over = true;
          std::exit(0);
        } else if (curr_player->totalPrestige() == other_player->
                  totalPrestige()) {
          // Tie condition
          if (curr_player->getPurchasedCards() > other_player->
              getPurchasedCards()) {
            // Player 1 bought fewer cards
            cout << " Congratulations Player 1: YOU WIN!!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          } else if (curr_player->getPurchasedCards() < other_player->
                    getPurchasedCards()) {
            // Player 2 bought fewer cards
            cout << " Congratulations Player 2: YOU WIN!!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          } else {
            // both players bought same number of cards
            cout << "You losers tied - BORING!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          }
        } else if (curr_player->totalPrestige() < other_player->
                  totalPrestige()) {
          // Player 1 has more prestige
          cout << " Congratulations Player 1: YOU WIN!!!!" << endl;
          screen_bg("white");
          screen_fg("black");
          game_over = true;
          std::exit(0);
        }
      } else {
        // If it is Player 1's current turn, Player 2 gets another turn
        cout << " PLAYER 2, enter your next move: ";
        turn(!player1_turn, false);
        return;
      }
    }
  } else if (query == "br") {
    int index;
    cin >> index;
    Card* selected_reserve;

    // Get the reserved card we want to buy
    selected_reserve = curr_player->getReserve(index-1);

    if (selected_reserve == nullptr || index > 3) {
      // Error if player tries to buy a card from an empty index
      cout << "Invalid move (no card at that index) - enter a valid move: ";
      turn(player1_turn, game_over);
      return;
    }

    for (int i = 0; i < 5; i++) {
      // Error if player cannot afford reserved card
      if ((curr_player->getGemCount(i) < (selected_reserve->getPrice(i) -
          curr_player->getDiscount(i))) &&
          (curr_player->getGemCount(i) + curr_player->getGemCount(5)) <
          (selected_reserve->getPrice(i) - curr_player->getDiscount(i))){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        turn(player1_turn, game_over);
        return;
      }
    }
    // Buy reserved card
    br_query(curr_player, index);

    if((!check_win(curr_player) && !player1_turn) && (other_player->
        totalPrestige() >= 15)){
      cout << " Congratulations Player 1: YOU WIN!!!!" << endl;
      screen_bg("white");
      screen_fg("black");
      game_over = true;
      std::exit(0);
    }

    /* Check for win - condition is Player 2 has a turn and doesn't have 15, so
    Player 1 wins */
    if((!check_win(curr_player) && !player1_turn) && (other_player->
      totalPrestige() >= 15)){
      cout << " Congratulations Player 1: YOU WIN!!!!" << endl;
      screen_bg("white");
      screen_fg("black");
      game_over = true;
      std::exit(0);
    }

    // If current player has more than 15
    if(check_win(curr_player)){
      // If Player 2 gets more than 15
      if(!player1_turn){
        // If Player 2 is more than Player 1
        if(curr_player->totalPrestige() > other_player->totalPrestige()){
          cout << " Congratulations Player 2: YOU WIN!!!!" << endl;
          screen_bg("white");
          screen_fg("black");
          game_over = true;
          std::exit(0);
        } else if (curr_player->totalPrestige() == other_player->
                  totalPrestige()) {
          // Tie condition
          if (curr_player->getPurchasedCards() > other_player->
              getPurchasedCards()) {
            // Player 1 bought fewer cards
            cout << " Congratulations Player 1: YOU WIN!!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          } else if (curr_player->getPurchasedCards() < other_player->
                    getPurchasedCards()) {
            // Player 2 bought fewer cards
            cout << " Congratulations Player 2: YOU WIN!!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          } else {
            // both players bought same number of cards
            cout << "You losers tied - BORING!!!!" << endl;
            screen_bg("white");
            screen_fg("black");
            game_over = true;
            std::exit(0);
          }
        } else if (curr_player->totalPrestige() < other_player->
                  totalPrestige()) {
          // Player 1 has more prestige
          cout << " Congratulations Player 1: YOU WIN!!!!" << endl;
          screen_bg("white");
          screen_fg("black");
          game_over = true;
          std::exit(0);
        }
      } else {
        // If it is Player 1's current turn, Player 2 gets another turn
        cout << " PLAYER 2, enter your next move: ";
        turn(!player1_turn, false);
        return;
      }
    }
  } else {
    // If the input query is invalid
    cout << "Invalid move - enter a valid move: ";
    turn(player1_turn, game_over);
    return;
  }
}

//main game loop
void Game::playGame(){
    string query;
    screen_bg("black");
    screen_fg("white");

    bool game_over = false;
    bool player1_turn = true;

    while(!game_over){
        //reset the screen
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();
        Player *player_1 = new Player();
        Player *player_2 = new Player();

        if (player1_turn) {
          // get query from user
          cout << " PLAYER 1, enter your next move: ";
        } else {
          // get query from user
          cout << " PLAYER 2, enter your next move: ";
        }

        /*-----------------------------------------------*/
        // Play turn of player
        turn(player1_turn, game_over);
        /*-----------------------------------------------*/

        //change turns
        player1_turn = !player1_turn;
    }

    // delete all vectors, all reserved, and the grid
    for (int i = 0; i < mines.size(); i++) {
      delete mines.at(i);
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        grid[i][j] = nullptr;
        delete grid[i][j];
      }
    }

    screen_bg("white");
    screen_fg("black");
}

//draw all of the elements onto the game board
void Game::drawBoard(){
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if(!vendors.empty()){
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if(!transport.empty()){
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if(!mines.empty()){
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for(int i = 0; i < CARD_ROWS; i++){
        for(int j = 0; j < CARD_COLS; j++){
            if(grid[i][j] != nullptr){
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            int index = (i * 2) + j;

            if(gem_bank[index] > 0){
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }

    //draw players
    drawPlayer(vpos + 1, 1, &player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), &player_2);

    //draw nobles
    if(play_nobles){
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for(int i = 0; i < NUM_NOBLES; i++){
            if(nobles.at(i) != nullptr){
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            if(board_color[i][j] != "white"){
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
   }
   cout << endl;
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c){
    string top    = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank  = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < 5; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p){
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if(hpos < 10){
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    }else{
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for(int i = 0; i < GEMS-1; i++){
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if(bonus >= 10){
            length += 1;
        }
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    for(int i = 0; i < GEMS; i++){
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for(int i = 0; i < 3; i++){
        Card *c = p->getReserve(i);
        if(c == nullptr){
            drawDeck(vpos, hpos, "");
        }else{
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for(int i = 0; i < length; i++){
        board[vpos + (CARD_HEIGHT/2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color){
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for(int i = 0; i < GEMS; i++){
        int length = gem_image[i].length();
        for(int j = 0; j < length; j++){
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];

        if(i == 8 || i == 9){
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }
}

/* indexToColor
1)	Arguments: int index
2)	Expectations about arguments: An integer indicating the index of a
corresponding color.
3)	Description: Depending on the index number, we return a string indicating
a different color.
4)	Return Value: A color in a string
5)	Expectations about return value: String
*/
string Game::indexToColor(int index) {
  if(index == 0){
    return "white";
  } else if (index == 1){
    return "red";
  } else if (index == 2){
    return "pink";
  } else if (index == 3){
    return "blue";
  } else if (index == 4){
    return "green";
  } else {
    return "yellow";
  }
}

/* decreaseGemBank
1)	Arguments: int color, int change
2)	Expectations about arguments: First argument is the color index of gem
whose quantity needs to be changed. Second argument is the quantity change
to be made.
3)	Description: Increases number of gems of a particular color in the gem bank
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::decreaseGemBank(int color, int change) {
  gem_bank[color] -= change;
}

/* increaseGemBank
1)	Arguments: int color, int change
2)	Expectations about arguments: First argument is the color index of gem
whose quantity needs to be changed. Second argument is the quantity change to
be made.
3)	Description: Increases number of gems of a particular color in the gem bank
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::increaseGemBank(int color, int change) {
  gem_bank[color] += change;
}


/* p3_query
1)	Arguments: Player* curr_player, string color_1, string color_2,
string color_3
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second to fourth arguments are strings containing all the
colors in put after the p3 query.
3)	Description: Purchases 3 gems of different colors from the gem bank.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::p3_query(Player* curr_player, string color_1, string color_2,
                    string color_3){

  string colors[5] = {"white", "red", "pink", "blue", "green"};

  /* Take out three gems of diff colors and add to the corresponding gem counts
  Also remove from the gem bank*/
  for (int i = 0; i < 5; i++) {
    if (color_1 == colors[i]) {
      curr_player->increaseGemCount(i, 1);
      decreaseGemBank(i, 1);
    }
  }

  for (int i = 0; i < 5; i++) {
    if (color_2 == colors[i]) {
      curr_player->increaseGemCount(i, 1);
      decreaseGemBank(i, 1);
    }
  }

  for (int i = 0; i < 5; i++) {
    if (color_3 == colors[i]) {
      curr_player->increaseGemCount(i, 1);
      decreaseGemBank(i, 1);
    }
  }
}

/* p2_query
1)	Arguments: Player* curr_player, string color_1,
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second argument is a string containing all the color
put after the p3 query.
3)	Description: Purchases 2 gems of the same color from the gem bank.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::p2_query(Player* curr_player, string color_1){
  string colors[5] = {"white", "red", "pink", "blue", "green"};
  /* Take out two gems of same color and add to private collection. Remove from
  gem bank. */
  for (int i = 0; i < 5; i++) {
    if (color_1 == colors[i]) {
      curr_player->increaseGemCount(i, 2);
      decreaseGemBank(i, 2);
    }
  }
}

/* r_query
1)	Arguments: Player* curr_player, string row, int index
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second argument is a string indicating the row of the
grid on which is the card we want to reserve. The third argument is the index
of the card we want to reserve on that row.
3)	Description: Reserves a particular Card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::r_query(Player* curr_player, string row, int index) {
  for (int i = 0; i < 3; i++){
    // Check for empty space
    if (curr_player->getReserve(i) == nullptr){
      if (row == "m") {
        // Reserve mines card
        curr_player->setReserve(grid[2][index-1], i);
        gem_bank[5] -= 1;
        curr_player->increaseGemCount(5, 1);
        grid[2][index-1] = mines.back();
        mines.pop_back();
        return;
      } else if (row == "t") {
        // Reserve transport card
        curr_player->setReserve(grid[1][index-1], i);
        gem_bank[5] -= 1;
        curr_player->increaseGemCount(5, 1);
        grid[1][index-1] = transport.back();
        transport.pop_back();
        return;
      } else if (row == "v") {
        // Reserve vendors card
        curr_player->setReserve(grid[0][index-1], i);
        gem_bank[5] -= 1;
        curr_player->increaseGemCount(5, 1);
        grid[0][index-1] = vendors.back();
        vendors.pop_back();
        return;
      }
    }
  }
}

/* b_query
1)	Arguments: Player* curr_player, string row, int index
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second argument is a string indicating the row of the
grid on which is the card we want to buy. The third argument is the index
of the card we want to buy on that row.
3)	Description: Buys a particular Card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::b_query(Player* curr_player, string row, int index) {
  Card* bought_card = nullptr;

  if (row == "v") {
    // Find card to be bought
    bought_card = grid[0][index-1];
    for (int i = 0; i < 5; i++) {
      // Conditions calculating change in each gem count/bank if no need gold
      if (curr_player->getGemCount(i) >= (bought_card->getPrice(i) -
          curr_player->getDiscount(i))) {
          if (bought_card->getPrice(i) != 0){
            increaseGemBank(i, (bought_card->getPrice(i) - curr_player->
                            getDiscount(i)));
            curr_player->decreaseGemCount(i, (bought_card->getPrice(i) -
                                          curr_player->getDiscount(i)));
          }
      // Conditions calculating change in each gem count/bank if gold needed
      } else if ((curr_player->getGemCount(i) + curr_player->getGemCount(5)) >=
                  (bought_card->getPrice(i) - curr_player->getDiscount(i))) {
        if (curr_player->getGemCount(i) == 0){
          increaseGemBank(i, 0);
        } else {
          increaseGemBank(i, ((bought_card->getPrice(i) - curr_player->
                          getGemCount(5)) - curr_player->getDiscount(i)));
        }
        curr_player->decreaseGemCount(5, ((bought_card->getPrice(i) -
                                      curr_player->getGemCount(i)) -
                                      curr_player->getDiscount(i)));
        increaseGemBank(5, ((bought_card->getPrice(i) - curr_player->
                            getGemCount(i)) - curr_player->getDiscount(i)));
        curr_player->decreaseGemCount(i, ((bought_card->getPrice(i) -
                                      curr_player->getDiscount(i)) -
                                      ((bought_card->getPrice(i) - curr_player
                                      ->getGemCount(i)) - curr_player->
                                      getDiscount(i))
                                     ));
      }
    }
    // Increase prestige of player
    curr_player->setPrestige(bought_card->getPrestige());
    // Update vector
    grid[0][index-1] = vendors.back();
    vendors.pop_back();
  } else if (row == "t") {
    bought_card = grid[1][index-1];
    for (int i = 0; i < 5; i++) {
      // Conditions calculating change in each gem count/bank if no need gold
      if (curr_player->getGemCount(i) >= (bought_card->getPrice(i) -
          curr_player->getDiscount(i))) {
          if (bought_card->getPrice(i) != 0){
            increaseGemBank(i, (bought_card->getPrice(i) - curr_player->
                            getDiscount(i)));
            curr_player->decreaseGemCount(i, (bought_card->getPrice(i) -
                                          curr_player->getDiscount(i)));
          }
      // Conditions calculating change in each gem count/bank if gold needed
      } else if ((curr_player->getGemCount(i) + curr_player->getGemCount(5)) >=
                  (bought_card->getPrice(i) - curr_player->getDiscount(i))) {
        if (curr_player->getGemCount(i) == 0){
          increaseGemBank(i, 0);
        } else {
          increaseGemBank(i, ((bought_card->getPrice(i) - curr_player->
                          getGemCount(5)) - curr_player->getDiscount(i)));
        }
        increaseGemBank(5, ((bought_card->getPrice(i) - curr_player->
                        getGemCount(i)) - curr_player->getDiscount(i)));
        curr_player->decreaseGemCount(5, ((bought_card->getPrice(i) -
                                      curr_player->getGemCount(i)) -
                                      curr_player->getDiscount(i)
                                      ));
        curr_player->decreaseGemCount(i, ((bought_card->getPrice(i) -
                                    curr_player->getDiscount(i)) -
                                    ((bought_card->getPrice(i) - curr_player->
                                    getGemCount(i))-curr_player->getDiscount(i))
                                    ));
      }
    }
    // Update prestige of player
    curr_player->setPrestige(bought_card->getPrestige());
    // Update vector
    grid[1][index-1] = transport.back();
    transport.pop_back();
  } else if (row == "m") {
    bought_card = grid[2][index-1];
    for (int i = 0; i < 5; i++) {
      // Conditions calculating change in each gem count/bank if no need gold
      if (curr_player->getGemCount(i) >= (bought_card->getPrice(i) -
          curr_player->getDiscount(i))) {
          if (bought_card->getPrice(i) != 0){
            increaseGemBank(i, (bought_card->getPrice(i) - curr_player->
                            getDiscount(i)));
            curr_player->decreaseGemCount(i, (bought_card->getPrice(i) -
                                          curr_player->getDiscount(i)));
          }
      // Conditions calculating change in each gem count/bank if gold needed
      } else if ((curr_player->getGemCount(i) + curr_player->getGemCount(5)) >=
                  (bought_card->getPrice(i) - curr_player->getDiscount(i))) {
        if (curr_player->getGemCount(i) == 0){
          increaseGemBank(i, 0);
        } else {
          increaseGemBank(i, ((bought_card->getPrice(i) - curr_player->
                          getGemCount(5)) - curr_player->getDiscount(i)));
        }
        increaseGemBank(5, ((bought_card->getPrice(i) - curr_player->
                        getGemCount(i)) - curr_player->getDiscount(i)));
        curr_player->decreaseGemCount(5, ((bought_card->getPrice(i) -
                                      curr_player->getGemCount(i)) -
                                      curr_player->getDiscount(i)));
        curr_player->decreaseGemCount(i, ((bought_card->getPrice(i) -
                                    curr_player->getDiscount(i)) -
                                    ((bought_card->getPrice(i) - curr_player->
                                    getGemCount(i)) - curr_player->
                                    getDiscount(i))));
      }
    }
    // Update prestige of player
    curr_player->setPrestige(bought_card->getPrestige());
    // Update vector
    grid[2][index-1] = mines.back();
    mines.pop_back();
  }

  // add discount to Player
  string discount_color = bought_card->getGemColor();
  string colors[5] = {"white", "red", "pink", "blue", "green"};
  // Take out two gems of same color and add to private collection.
  for (int i = 0; i < 5; i++) {
    if (discount_color == colors[i]) {
      curr_player->setDiscount(i);
    }
  }

  // Update number of purchased card
  curr_player->updatePurchasedCards();
  delete bought_card;
}

/* br_query
1)	Arguments: Player* curr_player, int index
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second argument is an integer indicating the index on our
row of reserved cards, of the card we want to buy.
3)	Description: Buys a particular reserved Card.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::br_query(Player* curr_player, int index) {
  Card* bought_card;
  bought_card = curr_player->getReserve(index-1);

  for (int i = 0; i < 5; i++) {
    // Conditions calculating change in each gem count/bank if no need gold
    if (curr_player->getGemCount(i) >= (bought_card->getPrice(i) -
        curr_player->getDiscount(i))) {
        if (bought_card->getPrice(i) != 0){
          increaseGemBank(i, (bought_card->getPrice(i) - curr_player->
          getDiscount(i)));
          curr_player->decreaseGemCount(i, (bought_card->getPrice(i) -
                                        curr_player->getDiscount(i)));
        }
    // Conditions calculating change in each gem count/bank if gold needed
    } else if ((curr_player->getGemCount(i) + curr_player->getGemCount(5)) >=
                (bought_card->getPrice(i) - curr_player->getDiscount(i))) {
      if (curr_player->getGemCount(i) == 0){
        increaseGemBank(i, 0);
      } else {
        increaseGemBank(i, ((bought_card->getPrice(i) - curr_player->
                        getGemCount(5)) - curr_player->getDiscount(i)));
      }
      increaseGemBank(5, ((bought_card->getPrice(i) - curr_player->
                      getGemCount(i)) - curr_player->getDiscount(i)));
      curr_player->decreaseGemCount(5, ((bought_card->getPrice(i) -
                                    curr_player->getGemCount(i)) - curr_player->
                                    getDiscount(i)));
      curr_player->decreaseGemCount(i, ((bought_card->getPrice(i)-curr_player->
                                    getDiscount(i)) - ((bought_card->
                                    getPrice(i) - curr_player->getGemCount(i))
                                    - curr_player->getDiscount(i))));
    }
  }
  // Update prestige of Player
  curr_player->setPrestige(bought_card->getPrestige());
  string discount_color = bought_card->getGemColor();
  string colors[5] = {"white", "red", "pink", "blue", "green"};
  // Update discounts of player
  for (int i = 0; i < 5; i++) {
    if (discount_color == colors[i]) {
      curr_player->setDiscount(i);
    }
  }

  // Update the reserve array
  if (index == 1) {
    curr_player->setReserve(curr_player->getReserve(index), index-1);
    curr_player->setReserve(curr_player->getReserve(index+1), index);
    curr_player->setReserve(nullptr, index+1);
  } else if (index == 2) {
    curr_player->setReserve(curr_player->getReserve(index), index-1);
    curr_player->setReserve(nullptr, index);
  } else {
    curr_player->setReserve(nullptr, index);
  }

  // Update number of purchased cards of player
  curr_player->updatePurchasedCards();
  delete bought_card;
}

/* gem_overflow
1)	Arguments: Player* curr_player, string color
2)	Expectations about arguments: The first argument is a pointer to the
current Player. The second argument is a string indicating the color of the
gem we want to return.
3)	Description: Returns gem to the bank if we have more than 10 gems in total.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::gem_overflow(Player* curr_player, string color){
  string colors[5] = {"white", "red", "pink", "blue", "green"};

  // Remove gems from gem count
  for (int i = 0; i < 5; i++) {
    if (color == colors[i]) {
      gem_bank[i] += 1;
      curr_player->decreaseGemCount(i, 1);
    }
  }
}

/* ask_gem_question
1)	Arguments: Player* curr_player
2)	Expectations about arguments: The argument is a pointer to the
current Player.
3)	Description: Prompts user again if the input for gem to return to bank is
invalid.
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
void Game::ask_gem_question(Player* curr_player){
  string color;
  cout << "Invalid color. Name one gem you would like to return: ";
  cin >> color;

  string colors[5] = {"white", "red", "pink", "blue", "green"};

  // Check if color is one of the 5 above
  if (color == colors[0] || color == colors[1] || color == colors[2] || color
  == colors[3] || color == colors[4]) {
    for (int i = 0; i < 5; i++) {
      if (color == colors[i]) {
        if (curr_player->getGemCount(i) == 0) {
          // Error if player doesn't have that gem to return
          ask_gem_question(curr_player);
        } else {
          // Remove gem from count if all tests pass
          gem_overflow(curr_player, color);
        }
      }
    }
  } else {
    // Error if color is not one of the 5
    ask_gem_question(curr_player);
  }
}

/* check_win
1)	Arguments: Player* curr_player
2)	Expectations about arguments: The argument is a pointer to the
current Player.
3)	Description: Checks if a player has more than 15 prestige points
4)	Return Value: N/A
5)	Expectations about return value: N/A
*/
bool Game::check_win(Player* curr_player){
  // Return true if Player has winning condition - i.e. they reach 15 points
  if (curr_player->totalPrestige() >= 15)  {
    clearBoard();
    screen_clear();
    screen_home();
    drawBoard();
    return true;
  } else {
    return false;
  }
}

//clear the board display
void Game::clearBoard(){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }
}
