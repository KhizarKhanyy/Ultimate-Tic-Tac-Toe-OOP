#include "ticTacToe.h"

// ============================================================
// Main game loop: alternate turns, check winner, allow save
// ============================================================
void playGame(ticTacToe& game, int startTurn = 0) {
    char players[2] = { 'X', 'O' };
    int turn = startTurn;

    while (true) {
        // Print current board
        cout << game;

        // Current player's turn
        char currentPlayer = players[turn % 2];
        game.getMove(currentPlayer);

        // Check for winner
        char winner = game.checkWinner();
        if (winner != ' ') {
            cout << game;
            cout << "  *** Congratulations! Player " << winner << " WINS! ***\n\n";
            return;
        }

        // Check for draw
        if (game.isFull()) {
            cout << game;
            cout << "  *** It's a DRAW! Well played both! ***\n\n";
            return;
        }

        // Offer save option after each move
        cout << "  Save and exit? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            ofstream file("BasicGame.txt");
            if (file) {
                file << game;
                file << (turn + 1) << "\n"; // save whose turn is next
                file.close();
                cout << "  Game saved to BasicGame.txt\n\n";
            } else {
                cout << "  ERROR: Could not save file!\n";
            }
            return;
        }

        turn++;
    }
}

// ============================================================
// MAIN: show menu -> new game or load saved game
// ============================================================
int main() {
    cout << "\n";
    cout << "  ==============================\n";
    cout << "     TIC TAC TOE  (N x N)\n";
    cout << "  ==============================\n\n";

    cout << "  1. New Game\n";
    cout << "  2. Load Saved Game\n";
    cout << "  Choice: ";

    int choice;
    cin >> choice;
    cout << "\n";

    // ---- LOAD SAVED GAME ----
    if (choice == 2) {
        ifstream file("BasicGame.txt");
        if (!file) {
            cout << "  No saved game found! Starting a new game.\n\n";
            choice = 1; // fall through to new game
        } else {
            ticTacToe game; // default 3x3, will be resized on load
            file >> game;
            int savedTurn = 0;
            file >> savedTurn;
            file.close();
            cout << "  Game loaded from BasicGame.txt!\n";
            cout << "  Resuming from turn " << savedTurn + 1 << "...\n\n";
            playGame(game, savedTurn);
            return 0;
        }
    }

    // ---- NEW GAME ----
    if (choice == 1) {
        int N;
        cout << "  Enter board size N (N >= 3): ";
        cin >> N;
        if (N < 3) {
            cout << "  N must be >= 3. Using 3.\n";
            N = 3;
        }
        cout << "\n  Starting " << N << " x " << N << " game!\n";
        cout << "  Player X goes first.\n\n";

        ticTacToe game(N);
        playGame(game);
    }

    return 0;
}
