#include "ticTacToe.h"

// ============================================================
// Helper: allocate a clean N x N board filled with spaces
// ============================================================
static void allocBoard(char**& board, int N) {
    board = new char*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new char[N];
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';
    }
}

// ============================================================
// Helper: free all memory used by the board
// ============================================================
static void freeBoard(char**& board, int N) {
    for (int i = 0; i < N; i++)
        delete[] board[i];
    delete[] board;
    board = NULL;
}

// ============================================================
// 1. Default Constructor -> creates a 3 x 3 empty board
// ============================================================
ticTacToe::ticTacToe() : N(3), moves(0) {
    allocBoard(board, N);
}

// ============================================================
// 2. Parameterized Constructor -> creates N x N empty board
// ============================================================
ticTacToe::ticTacToe(int size) : N(size < 3 ? 3 : size), moves(0) {
    allocBoard(board, N);
}

// ============================================================
// 3. Copy Constructor -> creates an independent deep copy
// ============================================================
ticTacToe::ticTacToe(const ticTacToe& other) : N(other.N), moves(other.moves) {
    board = new char*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new char[N];
        for (int j = 0; j < N; j++)
            board[i][j] = other.board[i][j];
    }
}

// ============================================================
// 4. Destructor -> releases all dynamically allocated memory
// ============================================================
ticTacToe::~ticTacToe() {
    freeBoard(board, N);
}

// ============================================================
// 5. Stream output operator (cout << game)
//    Prints the board with row/col numbers and dividers
// ============================================================
ostream& operator<<(ostream& out, const ticTacToe& game) {
    // Column header
    out << "\n     ";
    for (int j = 0; j < game.N; j++)
        out << "  " << (j + 1) << " ";
    out << "\n";

    for (int i = 0; i < game.N; i++) {
        out << "  " << (i + 1) << "  ";
        for (int j = 0; j < game.N; j++) {
            out << " " << game.board[i][j] << " ";
            if (j < game.N - 1) out << "|";
        }
        out << "\n";

        if (i < game.N - 1) {
            out << "     ";
            for (int j = 0; j < game.N; j++) {
                out << "---";
                if (j < game.N - 1) out << "+";
            }
            out << "\n";
        }
    }
    out << "\n";
    return out;
}

// ============================================================
// 6. Get a move from the player
//    Prompts for row and col, validates, places symbol
// ============================================================
void ticTacToe::getMove(char player) {
    int row, col;
    cout << "  Player " << player << " -> row col (1 to " << N << "): ";
    cin >> row >> col;
    row--; col--;  // convert 1-based input to 0-based index

    while (!isValidMove(row, col)) {
        if (row < 0 || row >= N || col < 0 || col >= N)
            cout << "  Out of range! row col (1 to " << N << "): ";
        else
            cout << "  Cell is taken! Try another row col: ";
        cin >> row >> col;
        row--; col--;
    }

    board[row][col] = player;
    moves++;
}

// ============================================================
// 7. Check if a move is valid (in bounds + cell is empty)
// ============================================================
bool ticTacToe::isValidMove(int row, int col) const {
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    return board[row][col] == ' ';
}

// ============================================================
// 8. Check for a winner (rows, columns, both diagonals)
//    Returns 'X' or 'O' if someone won, ' ' otherwise
// ============================================================
char ticTacToe::checkWinner() const {
    // Check every row
    for (int i = 0; i < N; i++) {
        char f = board[i][0];
        if (f == ' ') continue;
        bool win = true;
        for (int j = 1; j < N; j++)
            if (board[i][j] != f) { win = false; break; }
        if (win) return f;
    }

    // Check every column
    for (int j = 0; j < N; j++) {
        char f = board[0][j];
        if (f == ' ') continue;
        bool win = true;
        for (int i = 1; i < N; i++)
            if (board[i][j] != f) { win = false; break; }
        if (win) return f;
    }

    // Check main diagonal (top-left -> bottom-right)
    {
        char f = board[0][0];
        if (f != ' ') {
            bool win = true;
            for (int i = 1; i < N; i++)
                if (board[i][i] != f) { win = false; break; }
            if (win) return f;
        }
    }

    // Check anti-diagonal (top-right -> bottom-left)
    {
        char f = board[0][N - 1];
        if (f != ' ') {
            bool win = true;
            for (int i = 1; i < N; i++)
                if (board[i][N - 1 - i] != f) { win = false; break; }
            if (win) return f;
        }
    }

    return ' '; // no winner yet
}

// ============================================================
// Check if board is full (all N*N cells have been played)
// ============================================================
bool ticTacToe::isFull() const {
    return moves == N * N;
}

// ============================================================
// 9a. Save game to file  (ofstream << game)
//     Writes: size, moves, then each row of the board
// ============================================================
ofstream& operator<<(ofstream& out, const ticTacToe& game) {
    ostream& base = static_cast<ostream&>(out);
    base << game.N     << "\n";
    base << game.moves << "\n";
    for (int i = 0; i < game.N; i++) {
        for (int j = 0; j < game.N; j++)
            base << game.board[i][j];
        base << "\n";
    }
    return out;
}

// ============================================================
// 9b. Load game from file  (ifstream >> game)
//     Reads size, moves, then reconstructs board row by row
// ============================================================
ifstream& operator>>(ifstream& in, ticTacToe& game) {
    for (int i = 0; i < game.N; i++)
        delete[] game.board[i];
    delete[] game.board;

    in >> game.N >> game.moves;
    in.ignore();

    game.board = new char*[game.N];
    for (int i = 0; i < game.N; i++) {
        game.board[i] = new char[game.N];
        string row;
        getline(in, row);
        for (int j = 0; j < game.N; j++)
            game.board[i][j] = (j < (int)row.size()) ? row[j] : ' ';
    }
    return in;
}
