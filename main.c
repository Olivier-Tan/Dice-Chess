#include <stdio.h>
#include <stdlib.h>
#include "chess.h"




int main(void) {
    char chess_board[8][8];

    boardInit(chess_board);

    printConsoleBoard(chess_board);

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