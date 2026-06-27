#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ticTacToe {
private:
    char** board;  // dynamic 2D array for the game board
    int N;         // board size (N x N)
    int moves;     // total moves made (used to detect draw)

public:
    // 1. Default Constructor -> creates 3x3 board
    ticTacToe();

    // 2. Parameterized Constructor -> creates N x N board
    ticTacToe(int size);

    // 3. Copy Constructor -> deep copy
    ticTacToe(const ticTacToe& other);

    // 4. Destructor -> free memory
    ~ticTacToe();

    // 5. Stream output operator -> cout << game
    friend ostream& operator<<(ostream& out, const ticTacToe& game);

    // 6. Get move from player
    void getMove(char player);

    // 7. Check if a move is valid
    bool isValidMove(int row, int col) const;

    // 8. Check winner after each move
    char checkWinner() const;

    // 9. Save game to file
    friend ofstream& operator<<(ofstream& out, const ticTacToe& game);

    // 9. Load game from file
    friend ifstream& operator>>(ifstream& in, ticTacToe& game);

    // Helper: is board completely full?
    bool isFull() const;

    // Helper: get size (used by ultimate game)
    int getSize() const { return N; }

    // Helper: get moves count
    int getMoves() const { return moves; }
};

#endif
