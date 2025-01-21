#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#define BOARD_WIDTH 8
#define BOARD_LENGTH 8
#define MAX_MOVES 100
#define FALSE 0
#define TRUE 1
#define WHITE 0
#define BLACK 1
#define NUM_PIECES_COLOUR 6
#define MOVE_ERROR -1
#define VALID 1

#include <stdbool.h>


// Enum to represent chess pieces
typedef enum {
    EMPTY,       
    PAWN_WHITE,  
    KNIGHT_WHITE, 
    BISHOP_WHITE, 
    ROOK_WHITE,  
    QUEEN_WHITE, 
    KING_WHITE,  
    PAWN_BLACK,  
    KNIGHT_BLACK, 
    BISHOP_BLACK, 
    ROOK_BLACK,  
    QUEEN_BLACK, 
    KING_BLACK   
} ChessPiece;

struct square {
    int row;
    int col;
    char piece;
};

char checkColour(int row);
void boardInit(char board[8][8]);
int playerMove(char board[8][8], char move[5], int player);
void printConsoleBoard(char board[8][8]);
void callSquare(int row, int col);
int checkWin(char board[8][8]);

int checkPawnMove(char board[8][8], char move[5], bool take, int player);
int checkKnightMove(char board[8][8], char move[5], bool take, int player);
int checkBishopMove(char board[8][8], char move[5], bool take, int player);
int checkRookMove(char board[8][8], char move[5], bool take, int player);
int checkQueenMove(char board[8][8], char move[5], bool take, int player);
int checkKingMove(char board[8][8], char move[5], bool take, int player);

void playMove(char board[8][8], char move[5]);

struct square moveToCoords(char board[8][8], char move[5], bool take);

#endif
