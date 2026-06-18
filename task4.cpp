#include <iostream>
using namespace std;

char board[3][3];

// Initialize Board
void initializeBoard() {
    char value = '1';

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = value++;
        }
    }
}

// Display Board
void displayBoard() {
    cout << "\n";

    for(int i = 0; i < 3; i++) {
        cout << " ";

        for(int j = 0; j < 3; j++) {
            cout << board[i][j];

            if(j < 2)
                cout << " | ";
        }

        cout << endl;

        if(i < 2)
            cout << "---|---|---" << endl;
    }

    cout << "\n";
}

// Check Winner
bool checkWinner(char player) {

    for(int i = 0; i < 3; i++) {

        if(board[i][0] == player &&
           board[i][1] == player &&
           board[i][2] == player)
            return true;

        if(board[0][i] == player &&
           board[1][i] == player &&
           board[2][i] == player)
            return true;
    }

    if(board[0][0] == player &&
       board[1][1] == player &&
       board[2][2] == player)
        return true;

    if(board[0][2] == player &&
       board[1][1] == player &&
       board[2][0] == player)
        return true;

    return false;
}

// Check Draw
bool checkDraw() {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {

            if(board[i][j] != 'X' &&
               board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

// Make Move
bool makeMove(int choice, char player) {

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if(choice < 1 || choice > 9)
        return false;

    if(board[row][col] == 'X' ||
       board[row][col] == 'O')
        return false;

    board[row][col] = player;

    return true;
}

int main() {

    char replay;

    do {

        initializeBoard();

        char currentPlayer = 'X';
        int move;

        while(true) {

            displayBoard();

            cout << "Player "
                 << currentPlayer
                 << ", enter position (1-9): ";

            cin >> move;

            if(!makeMove(move, currentPlayer)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            if(checkWinner(currentPlayer)) {

                displayBoard();

                cout << "Player "
                     << currentPlayer
                     << " Wins!\n";

                break;
            }

            if(checkDraw()) {

                displayBoard();

                cout << "Game Draw!\n";

                break;
            }

            currentPlayer =
                (currentPlayer == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay Again? (Y/N): ";
        cin >> replay;

    } while(replay == 'Y' || replay == 'y');

    cout << "\nThanks for playing!\n";

    return 0;
}
