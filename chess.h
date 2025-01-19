#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#define BOARD_WIDTH 8
#define BOARD_LENGTH 8
#define MAX_MOVES 100

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

char checkColour(int row);
void boardInit(char board[8][8]);
void printConsoleBoard(char board[8][8]);
void callSquare(int row, int col);
void checkWin(char board[8][8]);

#endif