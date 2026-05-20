#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEGAL_MOVES 256
#define BOARD_ARRAY_SIZE 120

typedef uint64_t bitboard;

typedef enum {
	EMPTY,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
} PieceType;

typedef enum {
	MOVEMENT,
	CAPTURE,
	ENPASSANT,
	SHORTCASTLE,
	LONGCASTLE
} MoveType;

typedef struct {
	int moveType;
	int startSquare, targetSquare;
} Move;

typedef struct {
	int squares[BOARD_ARRAY_SIZE];
	int turn;
	int lastPawnMoved;
	int playerToMove; //1 white, -1 black
	bitboard wKing, bKing;
	Move legalMoves[MAX_LEGAL_MOVES], movesPlayed[1024];
} Board;

Board* createBoard();
void freeBoard(Board* board);
void drawBoard(Board* board);
void setPosition(Board* board, char* position);
void generateRookLegalMoves(Board* board, int squareIndex);
void generateBishopLegalMoves(Board* board, int squareIndex);
void generateQueenLegalMoves(Board* board, int squareIndex);
void generateKnightLegalMoves(Board* board, int squareIndex);
void generateKingLegalMoves(Board* board, int squareIndex);
void generatePawnLegalMoves(Board* board, int squareIndex);
void generateMoves(Board* board, int player);
bitboard controlledSquares(int squares[], int player);
bitboard controlledSquaresForPiece(int squares[], int square);
int index64(int index);
uint64_t reverseU64(uint64_t n);
void printBitboard(uint64_t n);
int isMoveLegal(int squares[], Move move, int playerToMove);
bitboard kingPosition(int square[], int player);
int numLegalMoves(Move legalMoves[]);
