#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

void printBoard(vector<vector<char>>& board) {
    for (vector<char>& row : board) {
        for (char& ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

bool isBoardFull(vector<vector<char>>& board) {
    for (vector<char>& row : board) {
        for (char& ch : row) {
            if (ch == '_')
                return false;
        }
    }
    return true;
}

bool checkWin(vector<vector<char>>& board, const char& player) {
    // horizontal and vertical wins
    for (int i = 0; i < 3; i++) {
        if (((board[i][0] == player) && (board[i][1] == player) && (board[i][2] == player)) ||
            ((board[0][i] == player) && (board[1][i] == player) && (board[2][i] == player))) {
            return true;
        }
    }

    // diagonal wins
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

void playerMove(vector<vector<char>>& board) {
    int x = 0, y = 0;
    while (true) {
        cout << "Enter the position (row and column) you want to play (0-2): ";
        cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == '_') {
            board[x][y] = 'X';
            break;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

void computerMove(vector<vector<char>>& board) {
    // Check winning move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = 'O';
                if (checkWin(board, 'O')) {
                    return;
                }
                board[i][j] = '_';
            }
        }
    }

    // Play random move
    int x, y;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != '_');
    board[x][y] = 'O';
}

void playGame(vector<vector<char>>& board) {
    char player = 'X';

    while (true) {
        if (player == 'X') {
            cout << "User plays" << endl;
            playerMove(board);
        } else {
            cout << "Computer plays" << endl;
            computerMove(board);
        }
        printBoard(board);

        if (checkWin(board, player)) {
            cout << player << " wins." << endl;
            return;
        } else if (isBoardFull(board)) {
            cout << "It's a draw." << endl;
            return;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, '_'));
    playGame(board);
    return 0;
}
