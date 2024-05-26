#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

// Length of the board
#define SIDE 3

// Name of the players
string PLAYER1, PLAYER2;

// Function to show the current
// board status
void showBoard(char board[][SIDE]){

    cout << "\n\n";
    cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    cout << "\t\t\t------------\n";
    cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    cout << "\t\t\t------------\n";
    cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n\n";
}

// Function to show the instructions
void showInstructions()
{
    cout << "\t\t\t Tic-Tac-Toe\n\n";
    cout << "Choose a cell numbered from 1 to 9 as below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t------------\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t------------\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";
    cout << "-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n";
}

// Function to initialize the game
void initialise(char board[][SIDE], int moves[])
{
    // Initialize the board with empty spaces
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = ' ';
        }
    }

    // Fill the moves with numbers 0 to 8
    for (int i = 0; i < SIDE * SIDE; i++) {
        moves[i] = i;
    }

    // Shuffle the moves
    random_shuffle(moves, moves + SIDE * SIDE);
}

// Function to declare winner of the game
void declareWinner(string whoseTurn)
{
    cout << whoseTurn << " has won\n";
}

// Function that returns true if
// any of the row is crossed with
// the same player's move
bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return true;
        }
    }
    return false;
}

// Function that returns true if any
// of the column is crossed with the
// same player's move
bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return true;
        }
    }
    return false;
}

// Function that returns true if any
// of the diagonal is crossed with
// the same player's move
bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return true;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return true;
    }

    return false;
}

// Function that returns true if the
// game is over else it returns a false
bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

// Function to play Tic-Tac-Toe
void playTicTacToe(string whoseTurn)
{
    // A 3*3 Tic-Tac-Toe board for playing
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];

    // Initialise the game
    initialise(board, moves);

    // Show instructions before playing
    showInstructions();

    int moveIndex = 0, r, c;

    // Keep playing till the game is
    // over or it is a draw
    while (gameOver(board) == false && moveIndex != SIDE * SIDE) {
        if (whoseTurn == PLAYER1) {
            // Input the desired row and
            // column by player 1 to
            // insert X
            cout << PLAYER1 << ", enter the respective row and column to insert X: ";
            cin >> r >> c;

            if (r >= 1 && r <= 3 && c >= 1 && c <= 3) {
                // To check desired row and
                // column should be empty
                if (board[r - 1][c - 1] == ' ') {
                    board[r - 1][c - 1] = 'X';
                }
                // If input is on already
                // filled position
                else {
                    cout << "You cannot overlap on already filled position:\n";
                    continue;
                }
            }
            // Input is not valid
            else {
                cout << "Input is not valid, please enter the right one\n";
                continue;
            }

            showBoard(board);
            moveIndex++;
            whoseTurn = PLAYER2;
        }
        else if (whoseTurn == PLAYER2) {
            // Input the desired row and
            // column by player 2 to
            // insert O
            cout << PLAYER2 << ", enter the respective row and column to insert O: ";
            cin >> r >> c;

            if (r >= 1 && r <= 3 && c >= 1 && c <= 3) {
                // To check desired row and
                // column should be empty
                if (board[r - 1][c - 1] == ' ') {
                    board[r - 1][c - 1] = 'O';
                }
                // If input is on already
                // filled position
                else {
                    cout << "You cannot overlap on already filled position:\n";
                    continue;
                }
            }
            // Input is not valid
            else {
                cout << "Input is not valid, please enter the right one\n";
                continue;
            }

            showBoard(board);
            moveIndex++;
            whoseTurn = PLAYER1;
        }
    }

    // If the game has drawn
    if (gameOver(board) == false && moveIndex == SIDE * SIDE) {
        cout << "It's a draw\n";
    }
    else {
        // Toggling the user to declare
        // the actual winner
        if (whoseTurn == PLAYER1) {
            whoseTurn = PLAYER2;
        }
        else if (whoseTurn == PLAYER2) {
            whoseTurn = PLAYER1;
        }

        // Declare the winner
        declareWinner(whoseTurn);
    }
}

// Driver Code
int main()
{
    // Take the name of players
    cout << "Enter name of first Player: ";
    cin >> PLAYER1;

    cout << "Enter name of second Player: ";
    cin >> PLAYER2;

    cout << "\nplayer 1 will have 'X'\n player 2 will have 'O'\n\n";
    // Use current time as seed for
    // random generator
    char ch;
    
    do{
    srand(time(0));

    // Let's do toss
    int toss = rand() % 2;

    // Let us play the game
    if (toss == 1) {
        cout << "Player " << PLAYER1 << " wins the toss\n";
        playTicTacToe(PLAYER1);
    }
    else {
        cout << "Player " << PLAYER2 << " wins the toss\n";
        playTicTacToe(PLAYER2);
    }

    cout << "Do you want to play another game (Y/N)" << endl; 
    cin >> ch ;
    
    }while(ch != 'N');
    return 0;
}
