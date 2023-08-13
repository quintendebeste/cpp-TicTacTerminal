#include <iostream>
#include <string>
#include <tuple>
using namespace std;
string rowPos = "";
string columnPos = "";
bool running = true;
bool turn = true;
bool validMove = false;
bool win = false;

string pos_00 = " ", pos_01 = " ", pos_02 = " ", pos_10 = " ", pos_11 = " ",
       pos_12 = " ", pos_20 = " ", pos_21 = " ", pos_22 = " ";

void drawBoard() {
  cout << "   0|1|2" << endl;
  cout << "0| " << pos_00 << "|" << pos_10 << "|" << pos_20 << endl;
  cout << "  -------" << endl;
  cout << "1| " << pos_01 << "|" << pos_11 << "|" << pos_21 << endl;
  cout << "  -------" << endl;
  cout << "2| " << pos_02 << "|" << pos_12 << "|" << pos_22 << endl;
}

bool makeMove(bool turn, string row, string col) {
  try {
    if (row.length() == 1 && col.length() == 1) {
      int rowIndex = stoi(row); // stoi is string to int
      int colIndex = stoi(col);
      if (rowIndex >= 0 && rowIndex <= 2 && colIndex >= 0 &&
          colIndex <= 2) { // if statement checks if the row and col are valid
        // this blew my mind, apperently this is a "nested ternary operator"
        // this is sick. thanks to chatgpt for introducing this to me so
        // &position is a reference and in these lines we make a connection from
        // &position to the right positional variable, so i the reference
        // changes the referenced variable does to. so if position changes
        // pos_?? the referenced variable changes to.
        string &position =
            (row == "0")
                ? (col == "0"
                       ? pos_00
                       : (col == "1" ? pos_01
                                     : pos_02)) // this asks if row is 0
                                                // and if so it then checks
            // if col is 0 or 1 and if not both it is 2 and it binds the
            // reference with the right variable
            : (row == "1")
                ? (col == "0"
                       ? pos_10
                       : (col == "1" ? pos_11
                                     : pos_12)) // so this is for if row did not
                                                // equal 0 but instead equals 1
                : (col == "0"
                       ? pos_20
                       : (col == "1" ? pos_21
                                     : pos_22)); // and this is for if row
                                                 // did not equal 0 or 1
        // unfortunately my autoformatting settings in neovim made this in my
        // opinion less readable, i do not want to spend to much time at
        // tinkering with that for now. the upside is is that this nested
        // ternary operators are shown as a if statement and i like that because
        // it does exactly the same and it helps visualising complex code a lot
        if (position == " ") {
          if (turn) {
            position = "X";
          } else {
            position = "O";
          }
        } else {
          cout << "these coordinates already contain a value" << endl;
          return false;
        }
        return true;
      } else {
        return false;
      }
    } else {
      cout << "" << endl;
      return false;
    }
  } catch (const exception &e) {
    // This executes if an exception is thrown within the previous try
    // The caught exception is stored in the variable e.

    // std::cerr is the cout for error messages
    cerr << "the flux capacitor was overloaded with flux, delorean needs "
            "fixing. "
            "details:"
         << e.what() << endl;
    // The e.what() function retrieves the error message.
    return false;
  }
}

bool winCheck() {
  win = (pos_11 == " ")                          ? false
        : (pos_11 == pos_10 && pos_11 == pos_12) ? true
        : (pos_11 == pos_20 && pos_11 == pos_02) ? true
        : (pos_11 == pos_01 && pos_11 == pos_21) ? true
                                                 : false;
  if (win) {
    return win;
  }
  win = (pos_00 == " ")                          ? false
        : (pos_00 == pos_01 && pos_00 == pos_02) ? true
        : (pos_00 == pos_10 && pos_00 == pos_20) ? true
                                                 : false;
  if (win) {
    return win;
  }
  win = (pos_22 == " ")                          ? false
        : (pos_22 == pos_21 && pos_22 == pos_20) ? true
        : (pos_22 == pos_12 && pos_22 == pos_02) ? true
                                                 : false;
  return win;
}

int main() {
  drawBoard();
  while (running) {
    winCheck();
    if (!win) {
      if (turn) {
        cout << "X make your move(row):";
        cin >> rowPos;
        cout << "X make your move(column ):";
        cin >> columnPos;
        validMove = makeMove(turn, rowPos, columnPos);
        drawBoard();
      } else {
        cout << "O make your move(row):";
        cin >> rowPos;
        cout << "O make your move(column):";
        cin >> columnPos;
        validMove = makeMove(turn, rowPos, columnPos);
        drawBoard();
      }
      if (validMove) {
        turn = !turn;
      }
      validMove = false;
    } else {
      turn == true
          ? cout << "O was the one with the bigger brain, thanks for playing!!"
                 << endl
          : cout << "X was the one with the bigger brain, thanks for playing!!"
                 << endl;
      cout << "type something then press enter to quit";
      cin >> rowPos;
      running = false;
    }
  }
  return 0;
}
