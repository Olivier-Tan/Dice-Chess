#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "chess.h"




int main(void) {
    char chessBoard[8][8];

    boardInit(chessBoard);

    printConsoleBoard(chessBoard);

    int player = 0;

    while (checkWin(chessBoard)) {
        char move[5];

        fgets(move, sizeof(move), stdin);

        int valid = playerMove(chessBoard, move, player);

        if (valid == MOVE_ERROR) {
            printf("That is not a valid move, please try again!\n");
            continue;
        }

        if (player == WHITE) {
            player = BLACK;
        } else {
            player = WHITE;
        }
    }

}

// board_init helper function
// determines whether black or white

char checkColour(int row) {
    if (row < 2) {
        return 'b';
    } else {
        return 'w';
    }
}

// col 0 is file a, 1 is b ... 7 is h
// We assume we play as white, so "0" is 8th rank and "7" is 1st rank
void boardInit(char board[8][8]) {
    for (int row = 0; row < BOARD_WIDTH; row++) {
        
        for (int col = 0; col < BOARD_LENGTH; col++) {

            if (1 < row && row < 6) {
                board[row][col] = EMPTY;
                continue;
            }
            int colour = checkColour(row);

            if (row == 1 || row == 6) {
                if (colour == 'w') {
                    board[row][col] = PAWN_WHITE;
                } else {
                    board[row][col] = PAWN_BLACK;
                }
                continue;
            } 

            if (col == 0 || col == 7) board[row][col] = ROOK_WHITE;
            if (col == 1 || col == 6) board[row][col] = KNIGHT_WHITE;
            if (col == 2 || col == 5) board[row][col] = BISHOP_WHITE;
            if (col == 3) board[row][col] = QUEEN_WHITE;
            if (col == 4) board[row][col] = KING_WHITE;

            if (colour == 'b') {
                board[row][col] += 6;
            }
        }
    }
}

void printConsoleBoard(char board[8][8]) {

    for (int row = 0; row < BOARD_LENGTH; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            switch (board[row][col]) {
                case 0:
                    printf(".");
                    break;
                case 1: 
                    printf("P");
                    break;
                case 2: 
                    printf("N");
                    break;
                case 3: 
                    printf("B");
                    break;
                case 4: 
                    printf("R");
                    break;
                case 5: 
                    printf("Q");
                    break;
                case 6: 
                    printf("K");
                    break;
                case 7: 
                    printf("p");
                    break;
                case 8: 
                    printf("n");
                    break;
                case 9: 
                    printf("b");
                    break;
                case 10: 
                    printf("r");
                    break;
                case 11: 
                    printf("q");
                    break;
                case 12: 
                    printf("k");
                    break;
            }

            printf(" ");
        }
        printf("\n");
    }
}

int checkWin(char board[8][8]) {
    int flag = 0;

    for (int row = 0; row < BOARD_LENGTH; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (board[row][col] == KING_WHITE || board[row][col] == KING_BLACK) {
                flag++;
            }
        }
    }

    if (flag == 2) return TRUE;

    return FALSE;
}

int playerMove(char board[8][8], char move[5], int player) {
    char Pieces[6] = {'P', 'N', 'B', 'R', 'Q', 'K'};
    char boardFiles[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    int flag = 0;
    char piece;

    // if (player == WHITE) {
    //     for (int i = 0; i < NUM_PIECES_COLOUR; i++) {
    //         if (move[0] == Pieces[i]) {
    //             flag = 1;
    //             piece = Pieces[i];
    //             break;
    //         }
    //     }
    // } else {
    //     for (int i = 0; i < NUM_PIECES_COLOUR; i++) {
    //         if (move[0] == Pieces[i]) {
    //             flag = 1;
    //             piece = Pieces[i];
    //             break;
    //         }
    //     }
    // }

    // if (!flag) return MOVE_ERROR;

    flag = 0;

    int pawnFlag = 0;

    if (strlen(move) < 4) {
        printf("bleh");
        for (int i = 0; i < BOARD_WIDTH; i++) {
            if (move[0] == boardFiles[i]) {
                pawnFlag = 1;
                return checkPawnMove(board, move, FALSE, player);
            }
        }
    }
    printf("%d\n", strlen(move));

    if (pawnFlag) {
        return checkPawnMove(board, move, TRUE, player);
    }

    // if (move[0] == 'P') {
    //     if (move[1] < '3' || move[1] > '8') {
            
    //     } else if (move[1] == 'x') {
    //         if (move[2] < '3' || move[2] > '8') {
    //             return checkPawnMove(board, move, TRUE, player);
    //         }
    //     } else {
    //         return MOVE_ERROR;
    //     }
    // }

    bool take;

    if (move[1] == 'x') {
        take = true;
    }


    int filePosition = 1;

    if (take) {
        filePosition = 2;
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (move[filePosition] == boardFiles[i]) {
            flag = 1;
            break;
        } 
    }

    int moveRank = move[filePosition + 1] - '0';

    printf("moverank error");

    if (moveRank < 1 || moveRank > 8) return MOVE_ERROR;

    printf("pawn move shouldnt get here");

    if (!flag) return MOVE_ERROR;
    
    if (piece == 'N') {
        return checkKnightMove(board, move, take, player);
    } else if (piece == 'B') {
        return checkBishopMove(board, move, take, player);
    } else if (piece == 'R') {
        return checkRookMove(board, move, take, player);
    } else if (piece =='Q') {
        return checkQueenMove(board, move, take, player);
    } else if (piece == 'K') {
        return checkKingMove(board, move, take, player);
    }

    return VALID;
}

int checkPawnMove(char board[8][8], char move[5], bool take, int player) {
    struct square coords = moveToCoords(board, move, take);

    printf("row: %d\n", coords.row);
    printf("col: %d\n", coords.col);
    
    if (take) {
        if (board[coords.row][coords.col] == EMPTY) {
                return MOVE_ERROR;
        }

        if (!player) {
            if (board[coords.row + 1][move[0] - 'a'] != PAWN_WHITE) {
                return MOVE_ERROR;
            }

            if (board[coords.row][coords.col] < 7) {
                return MOVE_ERROR;
            }

        } else {
            if (board[coords.row - 1][move[0] - 'a'] != PAWN_BLACK) {
                return MOVE_ERROR;
            }

            if (board[coords.row][coords.col] > 6) {
                return MOVE_ERROR;
            }
        }
    } else {

        if (board[coords.row][coords.col] != EMPTY) {
                return MOVE_ERROR;
        }
        if (!player) {
            if (board[coords.row + 1][move[0] - 'a'] != PAWN_WHITE && 
                board[coords.row + 2][move[0] - 'a'] != PAWN_WHITE) {
                    printf("bleh1");
                return MOVE_ERROR;
            }
        } else {
            if (board[coords.row - 1][move[0] - 'a'] != PAWN_BLACK &&
                board[coords.row - 2][move[0] - 'a'] != PAWN_BLACK) {
                    printf("bleh2");
                return MOVE_ERROR;
            }
        }
    }

    return VALID;
}

int checkKnightMove(char board[8][8], char move[5], bool take, int player) {

}
int checkBishopMove(char board[8][8], char move[5], bool take, int player) {

}

int checkRookMove(char board[8][8], char move[5], bool take, int player) {

}

int checkQueenMove(char board[8][8], char move[5], bool take, int player) {

}

int checkKingMove(char board[8][8], char move[5], bool take, int player) {

}

struct square moveToCoords(char board[8][8], char move[5], bool take) {
    struct square coords;

    int shift = 1;

    if (take) shift++;

    if(strlen(move) == 3) shift--;

    coords.row = move[shift + 1] - '0';
    coords.col = move[shift] - 'a';

    coords.row = 8 - coords.row;

    return coords;
}

void playMove(char board[8][8], char move[5]) {

}
