#include <iostream>
#include <string>
#include <tuple>
using namespace std;
string rowPos = "";
string columnPos = "";
bool running = true;
bool turn = false;

string pos_00 = " ", pos_01 = " ", pos_02 = " ", pos_10 = " ", pos_11 = " ",
       pos_12 = " ", pos_20 = " ", pos_21 = " ", pos_22 = " ";

void drawBoard() {
  cout << "   0|1|2" << endl;
  cout << "0| " << pos_00 << "|" << pos_01 << "|" << pos_02 << endl;
  cout << "  -------" << endl;
  cout << "1| " << pos_10 << "|" << pos_11 << "|" << pos_12 << endl;
  cout << "  -------" << endl;
  cout << "2| " << pos_20 << "|" << pos_21 << "|" << pos_22 << endl;
};

void makeMove(bool turn, string row, string col) {
  int rowIndex = stoi(row); // stoi is string to int
  int colIndex = stoi(col);

  if (rowIndex >= 0 && rowIndex <= 2 && colIndex >= 0 &&
      colIndex <= 2) { // if statement checks if the row and col are valid integers
    // this blew my mind, apperently this is a "nested ternary operator" this is
    // sick. thanks to chatgpt for introducing this to me so &position is a
    // reference and in these lines we make a connection from &position to the
    // right positional variable, so i the reference changes the referenced
    // variable does to. so if position changes pos_?? the referenced variable
    // changes to.
    string &position =
        (row == "0")
            ? (col == "0"
                   ? pos_00
                   : (col == "1" ? pos_01 : pos_02)) // this asks if row is 0
                                                     // and if so it then checks
        // if col is 0 or 1 and if not both it is 2 and it binds the reference
        // with the right variable
        : (row == "1")
            ? (col == "0"
                   ? pos_10
                   : (col == "1" ? pos_11
                                 : pos_12)) // so this is for if row did not
                                            // equal 0 but instead equals 1
            : (col == "0"
                   ? pos_20
                   : (col == "1" ? pos_21 : pos_22)); // and this is for if row
                                                      // did not equal 0 or 1
    // unfortunately my autoformatting settings in neovim made this in my
    // opinion less readable, i do not want to spend to much time at tinkering
    // with that for now. the upside is is that this nested ternary operators
    // are shown as a if statement and i like that because it does exectly the
    // same and it helps visualising complex code a lot

    if (turn) {
      position = "X";
    } else {
      position = "O";
    }
  } else {
    cout << "Invalid input given" << endl;
  }
};

int main() {
  drawBoard();
  cout << "the game works as follows:" << endl
       << "the game will ask for input first the row so 1,2 or 3 and then the "
          "column so A,B or C."
       << endl;
  while (running) {
    if (turn) {
      cout << "X make your move(row):";
      cin >> rowPos;
      cout << "X make your move(column):";
      cin >> columnPos;
      makeMove(turn, rowPos, columnPos);
      drawBoard();
    } else {
      cout << "O make your move(row):";
      cin >> rowPos;
      cout << "O make your move(column):";
      cin >> columnPos;
      makeMove(turn, rowPos, columnPos);
      drawBoard();
    }
    cout << rowPos << columnPos << endl;
    turn = !turn;
  }
  return 0;
}
