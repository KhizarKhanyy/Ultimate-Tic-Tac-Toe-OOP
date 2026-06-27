/*
=============================================================
  ULTIMATE TIC-TAC-TOE  —  Complete OOP Implementation
  File: UltimateTicTacToe.cpp   (Single file, no headers)
  
  Rules:
  - 9 small 3x3 boards arranged in a 3x3 grid
  - Win a small board by getting 3 in a row on it
  - Win the game by winning 3 small boards in a row
  - KEY RULE: Your move's cell position decides which
    small board your opponent MUST play in next
=============================================================
*/
 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
 
// =============================================================
//  CLASS: ticTacToe  —  Represents ONE small 3x3 board
// =============================================================
class ticTacToe {
private:
    char board[3][3];   // 3x3 grid of cells
    int  moves;         // number of moves made on this board
 
public:
 
    // ---------------------------------------------------------
    // 1. CONSTRUCTOR — fills board with spaces (empty)
    // ---------------------------------------------------------
    ticTacToe() {
        moves = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }
 
    // ---------------------------------------------------------
    // 2. COPY CONSTRUCTOR — copies another board exactly
    // ---------------------------------------------------------
    ticTacToe(const ticTacToe& other) {
        moves = other.moves;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = other.board[i][j];
    }
 
    // ---------------------------------------------------------
    // 3. DESTRUCTOR — nothing dynamic here, but required
    // ---------------------------------------------------------
    ~ticTacToe() {}
 
    // ---------------------------------------------------------
    // 4. STREAM OUTPUT OPERATOR — prints one small board
    //    row by row (called by UltimateTicTacToe's operator<<)
    // ---------------------------------------------------------
    // Returns one row of the board as a string for display
    string getRow(int row) const {
        string s = "";
        for (int j = 0; j < 3; j++) {
            s += ' ';
            s += board[row][j];
            s += ' ';
            if (j < 2) s += '|';
        }
        return s;
    }
 
    // Print this small board standalone
    friend ostream& operator<<(ostream& out, const ticTacToe& t) {
        for (int i = 0; i < 3; i++) {
            out << t.getRow(i) << "\n";
            if (i < 2) out << "-----------\n";
        }
        return out;
    }
 
    // ---------------------------------------------------------
    // 5. GET MOVE — asks player for row and column
    //    Returns true if move is valid and placed it
    // ---------------------------------------------------------
    bool getMove(char symbol) {
        int row, col;
        cout << "  Enter row (1-3) and col (1-3): ";
        cin >> row >> col;
        row--; col--;  // convert to 0-based
 
        if (!isValidMove(row, col))
            return false;
 
        board[row][col] = symbol;
        moves++;
        return true;
    }
 
    // Place a move directly (used by Ultimate game)
    bool placeMove(int row, int col, char symbol) {
        if (!isValidMove(row, col)) return false;
        board[row][col] = symbol;
        moves++;
        return true;
    }
 
    // ---------------------------------------------------------
    // 6. IS VALID MOVE — checks bounds and if cell is empty
    // ---------------------------------------------------------
    bool isValidMove(int row, int col) const {
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "  Out of bounds! Try again.\n";
            return false;
        }
        if (board[row][col] != ' ') {
            cout << "  Cell already taken! Try again.\n";
            return false;
        }
        return true;
    }
 
    // ---------------------------------------------------------
    // 7. CHECK WINNER — checks rows, cols, diagonals
    //    Returns 'X', 'O', or ' ' (no winner)
    // ---------------------------------------------------------
    char checkWinner() const {
        // Check rows
        for (int i = 0; i < 3; i++)
            if (board[i][0] != ' ' &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2])
                return board[i][0];
 
        // Check columns
        for (int j = 0; j < 3; j++)
            if (board[0][j] != ' ' &&
                board[0][j] == board[1][j] &&
                board[1][j] == board[2][j])
                return board[0][j];
 
        // Check main diagonal
        if (board[0][0] != ' ' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2])
            return board[0][0];
 
        // Check anti-diagonal
        if (board[0][2] != ' ' &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0])
            return board[0][2];
 
        return ' '; // no winner yet
    }
 
    // Is this small board completely full?
    bool isFull() const { return moves >= 9; }
 
    // Is this small board done? (won or full)
    bool isDone() const { return checkWinner() != ' ' || isFull(); }
 
    // Getters/Setters for save-load
    char getCell(int r, int c) const { return board[r][c]; }
    void setCell(int r, int c, char ch) { board[r][c] = ch; }
    void setMoves(int m) { moves = m; }
    int  getMoves() const { return moves; }
};
 
 
// =============================================================
//  CLASS: UltimateTicTacToe
//  Holds a 3x3 array of ticTacToe objects (9 small boards)
// =============================================================
class UltimateTicTacToe {
private:
    ticTacToe boards[3][3];  // the 9 small boards
    char bigBoard[3][3];     // winner symbol of each small board
    int  nextBR, nextBC;     // which small board must be played (-1 = free choice)
    char currentPlayer;      // whose turn: 'X' or 'O'
 
public:
 
    // ---------------------------------------------------------
    // 1. CONSTRUCTOR
    // ---------------------------------------------------------
    UltimateTicTacToe() {
        currentPlayer = 'X';
        nextBR = -1; nextBC = -1;  // first move: player picks any board
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                bigBoard[i][j] = ' ';
    }
 
    // ---------------------------------------------------------
    // 2. COPY CONSTRUCTOR
    // ---------------------------------------------------------
    UltimateTicTacToe(const UltimateTicTacToe& other) {
        currentPlayer = other.currentPlayer;
        nextBR = other.nextBR;
        nextBC = other.nextBC;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                boards[i][j] = other.boards[i][j];
                bigBoard[i][j] = other.bigBoard[i][j];
            }
    }
 
    // ---------------------------------------------------------
    // 3. DESTRUCTOR
    // ---------------------------------------------------------
    ~UltimateTicTacToe() {}
 
    // ---------------------------------------------------------
    // 4. STREAM OUTPUT OPERATOR — prints all 9 boards
    //    in a 3x3 layout with dividers between them
    // ---------------------------------------------------------
    friend ostream& operator<<(ostream& out, const UltimateTicTacToe& u) {
        out << "\n";
        out << "    Board(1,1)     Board(1,2)     Board(1,3)\n";
        out << "  =============  =============  =============\n";
 
        for (int bigRow = 0; bigRow < 3; bigRow++) {
            // Each big-row has 3 small rows inside it
            for (int smallRow = 0; smallRow < 3; smallRow++) {
                out << "  ";
                for (int bigCol = 0; bigCol < 3; bigCol++) {
                    char w = u.bigBoard[bigRow][bigCol];
                    if (w != ' ') {
                        // Board already won — show big symbol
                        if (smallRow == 1)
                            out << "   [  " << w << "  ]   ";
                        else
                            out << "   [     ]   ";
                    } else {
                        out << u.boards[bigRow][bigCol].getRow(smallRow);
                    }
                    if (bigCol < 2) out << " | ";
                }
                out << "\n";
            }
            // Divider between big rows
            if (bigRow < 2)
                out << "  ===============================================\n";
        }
        out << "\n";
        return out;
    }
 
    // ---------------------------------------------------------
    // 5. GET MOVE — handles the ultimate game move logic
    //    Considers the last opponent's move to decide
    //    which small board must be played
    // ---------------------------------------------------------
    void getMove() {
        int br, bc, sr, sc;
 
        while (true) {
            // Determine which small board to play in
            if (nextBR == -1 || boards[nextBR][nextBC].isDone()) {
                // Free choice — any available board
                cout << "  Pick small board — row (1-3): "; cin >> br;
                cout << "  Pick small board — col (1-3): "; cin >> bc;
                br--; bc--;
                if (br < 0 || br > 2 || bc < 0 || bc > 2) {
                    cout << "  Invalid board! Try again.\n"; continue;
                }
                if (boards[br][bc].isDone()) {
                    cout << "  That board is already done! Pick another.\n"; continue;
                }
            } else {
                // Forced board from opponent's last move
                br = nextBR; bc = nextBC;
                cout << "  You MUST play in small board (" << br+1 << "," << bc+1 << ")\n";
            }
 
            // Get cell within that small board
            cout << "  Pick cell — row (1-3): "; cin >> sr;
            cout << "  Pick cell — col (1-3): "; cin >> sc;
            sr--; sc--;
 
            if (boards[br][bc].placeMove(sr, sc, currentPlayer)) {
                // Update big board if this small board is now won
                char w = boards[br][bc].checkWinner();
                if (w != ' ') bigBoard[br][bc] = w;
 
                // Send opponent to the board matching cell just played
                nextBR = sr; nextBC = sc;
 
                // Switch player
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                break;
            }
            // if invalid move, loop again
        }
    }
 
    // ---------------------------------------------------------
    // 6. IS VALID MOVE — handled inside getMove() above
    // ---------------------------------------------------------
 
    // ---------------------------------------------------------
    // 7. CHECK WINNER — checks the big board for 3 in a row
    // ---------------------------------------------------------
    char checkBigWinner() const {
        // Rows
        for (int i = 0; i < 3; i++)
            if (bigBoard[i][0] != ' ' &&
                bigBoard[i][0] == bigBoard[i][1] &&
                bigBoard[i][1] == bigBoard[i][2])
                return bigBoard[i][0];
        // Columns
        for (int j = 0; j < 3; j++)
            if (bigBoard[0][j] != ' ' &&
                bigBoard[0][j] == bigBoard[1][j] &&
                bigBoard[1][j] == bigBoard[2][j])
                return bigBoard[0][j];
        // Main diagonal
        if (bigBoard[0][0] != ' ' &&
            bigBoard[0][0] == bigBoard[1][1] &&
            bigBoard[1][1] == bigBoard[2][2])
            return bigBoard[0][0];
        // Anti diagonal
        if (bigBoard[0][2] != ' ' &&
            bigBoard[0][2] == bigBoard[1][1] &&
            bigBoard[1][1] == bigBoard[2][0])
            return bigBoard[0][2];
        return ' ';
    }
 
    // Are all 9 small boards done with no overall winner?
    bool isOver() const {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!boards[i][j].isDone())
                    return false;
        return true;
    }
 
    // ---------------------------------------------------------
    // 8a. SAVE GAME — writes full state to UltimateGame.txt
    // ---------------------------------------------------------
    void saveGame() const {
        ofstream file("UltimateGame.txt");
        if (!file) { cout << "  Error saving game!\n"; return; }
 
        file << currentPlayer << "\n";
        file << nextBR << " " << nextBC << "\n";
 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                file << bigBoard[i][j] << "\n";
                file << boards[i][j].getMoves() << "\n";
                for (int r = 0; r < 3; r++) {
                    for (int c = 0; c < 3; c++)
                        file << boards[i][j].getCell(r, c);
                    file << "\n";
                }
            }
        }
        cout << "  Game saved to UltimateGame.txt\n";
    }
 
    // ---------------------------------------------------------
    // 8b. LOAD GAME — reads state from UltimateGame.txt
    // ---------------------------------------------------------
    bool loadGame() {
        ifstream file("UltimateGame.txt");
        if (!file) return false;
 
        file >> currentPlayer;
        file >> nextBR >> nextBC;
 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                file >> bigBoard[i][j];
                int m; file >> m;
                string line; getline(file, line); // consume newline
                for (int r = 0; r < 3; r++) {
                    getline(file, line);
                    for (int c = 0; c < 3 && c < (int)line.size(); c++)
                        boards[i][j].setCell(r, c, line[c]);
                }
                boards[i][j].setMoves(m);
            }
        }
        cout << "  Game loaded successfully!\n";
        return true;
    }
 
    // Print the status of which small boards are won
    void printStatus() const {
        cout << "  Big Board Status:\n";
        for (int i = 0; i < 3; i++) {
            cout << "  ";
            for (int j = 0; j < 3; j++) {
                char w = bigBoard[i][j];
                cout << "[" << (w == ' ' ? '.' : w) << "]";
            }
            cout << "\n";
        }
        cout << "\n";
    }
 
    char getCurrentPlayer() const { return currentPlayer; }
};
 
 
// =============================================================
//  MAIN — Menu + Game Loop
// =============================================================
int main() {
    cout << "\n";
    cout << "  ================================================\n";
    cout << "         ULTIMATE TIC-TAC-TOE\n";
    cout << "  ================================================\n";
    cout << "  1. New Game\n";
    cout << "  2. Load Saved Game (UltimateGame.txt)\n";
    cout << "  3. Exit\n";
    cout << "  Choose: ";
 
    int choice; cin >> choice;
 
    if (choice == 3) { cout << "  Goodbye!\n"; return 0; }
 
    UltimateTicTacToe game;
 
    if (choice == 2) {
        if (!game.loadGame()) {
            cout << "  No saved game found. Starting new game.\n";
        }
    }
 
    // ---- GAME LOOP ----
    while (true) {
        cout << game;                   // print all 9 boards
        game.printStatus();             // print big board summary
 
        // Check if game is already won or over
        char winner = game.checkBigWinner();
        if (winner != ' ') {
            cout << "  *** Player " << winner << " WINS THE ULTIMATE GAME! ***\n\n";
            break;
        }
        if (game.isOver()) {
            cout << "  *** All boards are done — it's a DRAW! ***\n\n";
            break;
        }
 
        cout << "  Player " << game.getCurrentPlayer() << "'s Turn\n";
        cout << "  [1] Make Move   [2] Save & Exit\n";
        cout << "  Choice: ";
        int c; cin >> c;
 
        if (c == 2) {
            game.saveGame();
            cout << "  Goodbye!\n";
            return 0;
        }
 
        game.getMove();
    }
 
    return 0;
}
