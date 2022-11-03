#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


char lastTurn = 'o';
char board[9];

int checkValid(string line, char &move, int &row, int &column) {
        int charCount = 0;
        char chars;
        stringstream lineStream(line);
        while (lineStream >> chars) {
                if (charCount==0) {
                        move = chars;
                        if (chars != 'x' && chars != 'o') {
                                return 1;
                        }
                        if (move==lastTurn) return 2;
                        if (move=='x') {
                                lastTurn = 'x';
                        } else {
                                lastTurn = 'o';
                        }
                } else if (charCount==1) {
                        if (chars!='0' && chars!='1' && chars!='2') {
                                return 3;
                        }
                        row = chars - '0';
                } else if (charCount==2) {
                        if (chars!='0' && chars!='1' && chars!='2') {
                                return 4;
                        }
                        column = chars - '0';
                } if (charCount > 2) {
                        return 5;
                }
                ++charCount;
        }
        if (charCount < 3) return 6;
        if (board[row * 3 + column] != ' ') {
                return 7;
        }
        return 0;
}

int outcome() {
        for (int i = 0; i < 3; i++) {
                if (board[i * 3] != ' ' && board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
                        return board[i * 3]=='x' ? 1 : 2;
                }
        }
        for (int i = 0; i < 3; i++) {
                if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
                        return board[i]=='x' ? 1 : 2;
                }
        }
        if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) {
                return board[4]=='x' ? 1 : 2;
        }
        if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]) {
                return board[4]=='x' ? 1 : 2;
        }
        for (int i = 0; i < 9; i++) {
                if (board[i]==' ') return 0;
        }
        return 3;
}

void printBoard() {
        cout << "|" << board[0] << "|" << board[1] << "|" << board[2] << "|" << endl;
        cout << "|" << board[3] << "|" << board[4] << "|" << board[5] << "|" << endl;
        cout << "|" << board[6] << "|" << board[7] << "|" << board[8] << "|" << endl;
}

int main( int argc, char * argv[] ) {
        if (argc==1) {
                int xWins = 0;
                int oWins = 0;
                int ties = 0;
                int aborted = 0;
                int invalid = 0;
                for (int i = 0; i < 9; i++) {
                        board[i] = ' ';
                }
                while (!cin.eof()) {
                        char move;
                        int row;
                        int column;
                        string stdLines;
                        getline(cin, stdLines);
                        if (cin.fail()) break;
                        int check = checkValid(stdLines, move, row, column);
                        if (check != 0) {
                                invalid = 1;
                                aborted++;
                                cout << "Invalid move: " << stdLines << endl;
                                break;
                        } else {
                                board[row * 3 + column] = move;
                                check = outcome();
                                printBoard();
                                if (check==1) {
                                        xWins++;
                                        cout << "x won!" << endl;
                                        break;
                                }
                                if (check==2) {
                                        oWins++;
                                        cout << "o won!" << endl;
                                        break;
                                }
                                if (check==3) {
                                        ties++;
                                        cout << "Tie" << endl;
                                        break;
                                }
                                if (check != 0) {
                                        break;
                                }
                        }

                }
                int check = outcome();
                if (check==0 && invalid==0) {
                        cout << "Unfinished game" << endl;
                        aborted++;
                }
                cout << "x Wins:         " << xWins << endl;
                cout << "o Wins:         " << oWins << endl;
                cout << "Ties:           " << ties << endl;
                cout << "Aborted Games:  " << aborted << endl;
        } else {
                int xWins = 0;
                int oWins = 0;
                int ties = 0;
                int aborted = 0;
                int invalid = 0;
                for(int i = 1; i < argc; i++) {
                        for (int i = 0; i < 9; i++) {
                                board[i] = ' ';
                        }
                        ifstream inputFile;
                        inputFile.open(argv[i]);
                        if (!inputFile) {
                                cout << "Bad file: " << argv[i] << endl;
                        } else {
                                string lines;
                                while (getline(inputFile, lines)) {
                                        char move;
                                        int row;
                                        int column;
                                        int check = checkValid(lines, move, row, column);
                                        if (check != 0) {
                                                invalid = 1;
                                                aborted++;
                                                cout << "Invalid move: " << lines << endl;
                                                break;
                                        } else {
                                                board[row * 3 + column] = move;
                                                check = outcome();
                                                printBoard();
                                                if (check==1) {
                                                        xWins++;
                                                        cout << "x won!" << endl;
                                                }
                                                if (check==2) {
                                                        oWins++;
                                                        cout << "o won!" << endl;
                                                }
                                                if (check==3) {
                                                        ties++;
                                                        cout << "Tie" << endl;
                                                }
                                                if (check != 0) {
                                                        break;
                                                }
                                        }
                                }
                                int check = outcome();
                                if (check==0 && invalid==0) {
                                        cout << "Unfinished game" << endl;
                                        aborted++;
                                }
                        }
                        lastTurn = 'o';
                }
                cout << "x Wins:         " << xWins << endl;
                cout << "o Wins:         " << oWins << endl;
                cout << "Ties:           " << ties << endl;
                cout << "Aborted Games:  " << aborted << endl;
        }
        return 0;
}
