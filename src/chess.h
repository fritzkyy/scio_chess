#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEGAL_MOVES 256
#define BOARD_ARRAY_SIZE 120
#define WHITE 1
#define BLACK -1
#define WKINGPOS 95
#define WSCSQ 97
#define WLCSQ 93
#define BKINGPOS 25
#define BSCSQ 27
#define BLCSQ 23
#define S_A1 91
#define S_A8 98
#define S_H1 21
#define S_H8 28

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

typedef struct {
	int startSquare, targetSquare;
} Move;

typedef struct {
	size_t length;
	size_t firstEmptyIndex;
	Move moves[];
} MoveArr;

typedef struct {
	int squares[BOARD_ARRAY_SIZE];
	int turn;
	int lastPawnMoved;
	int playerToMove; //1 white, -1 black
	bitboard wKing, bKing;
	MoveArr legalMoves, movesPlayed;
	uint8_t castlingStatus;
	/*
	Bits:
	7: 0
	6: h8 rook moved
	5: h1 rook moved
	4: black king moved
	3: 0
	2: a8 rook moved
	1: a1 rook moved
	0: white king moved
	*/
} Board;

Board* createBoard();
void freeBoard(Board* board);
void drawBoard(Board* board);
void setPosition(Board* board, char* position);
void generateRookLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generateBishopLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generateQueenLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generateKnightLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generateKingLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generatePawnLegalMoves(Board* board, int squareIndex, MoveArr* arr);
void generateMoves(Board* board, int player);
MoveArr* legalMoves(Board* board);
bitboard controlledSquares(int squares[], int player);
bitboard controlledSquaresForPiece(int squares[], int square);
int index64(int index);
uint64_t reverseU64(uint64_t n);
void printBitboard(uint64_t n);
int isMoveLegal(int squares[], Move move, int playerToMove);
bitboard kingPosition(int square[], int player);
int numLegalMoves(MoveArr* legalMoves);
void perft(Board* board, int depth);void perftest(Board* board, int depth);
void makeMove(Board* board, Move move);
void unmakeMove(Board* board, Move move);
void append(MoveArr* arr, Move move);
MoveArr* createMoveArr(size_t length);
void printMoveToStr(Move move, char* str);
Move strToMove(char* str);
