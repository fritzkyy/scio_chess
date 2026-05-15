#include "chess.h"

Board* createBoard() {
	Board* board = malloc(sizeof(Board));
	if (!board) return NULL;

	memset(board, 0, sizeof(*board));
	board->turn = 0;
	board->playerToMove = 1;

	return board;
}

void freeBoard(Board* board) {
	if (board) free(board);
}

void drawBoard(Board* board) {
	for (int i = 2; i < 10; i++) {
		for (int j = 1; j < 9; j++) {
			switch (board->squares[i * 10 + j]) {
				case 0:
					printf(".");
					break;
				case PAWN:
					printf("P");
					break;
				case -PAWN:
					printf("p");
					break;
				case KNIGHT:
					printf("N");
					break;
				case -KNIGHT:
					printf("n");
					break;
				case BISHOP:
					printf("B");
					break;
				case -BISHOP:
					printf("b");
					break;
				case ROOK:
					printf("R");
					break;
				case -ROOK:
					printf("r");
					break;
				case QUEEN:
					printf("Q");
					break;
				case -QUEEN:
					printf("q");
					break;
				case KING:
					printf("K");
					break;
				case -KING:
					printf("k");
					break;
			}
		}
		printf("\n");
	}
}

void setPosition(Board* board, char* position) {
	if (!strcmp(position, "startpos")) {
		int pos[] = {
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, -ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK, 9,
			9, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, 9,
			9, ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
		};
		memcpy(board->squares, pos, sizeof(int) * BOARD_ARRAY_SIZE);
	} else {//if (!strcmp(position, "startpos")) {
		int pos[] = {
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, ROOK, 0, 0, 0, KNIGHT, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
		};
		memcpy(board->squares, pos, sizeof(int) * BOARD_ARRAY_SIZE);
	}
}

void generateRookLegalMoves(Board* board, int squareIndex) {
	int firstEmptyIndex = 0;
	for (int i = 0; i < MAX_LEGAL_MOVES; i++) {
		if (board->legalMoves[i].startSquare == 0) {
			firstEmptyIndex = i;
			break;
		}
	}
	printf("first empty index %d\n", firstEmptyIndex);

	//left
	for (int i = 1, c = 1; board->squares[squareIndex - i] != 9 && c; i++) {
		if (board->squares[squareIndex - i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - i};
			c = 0;
		} else if (board->squares[squareIndex - i] * board->playerToMove > 0) {
			c = 0;
		}
		if (c) board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//right
	for (int i = 1, c = 1; board->squares[squareIndex + i] != 9 && c; i++) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		}
		if (c) board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
	//top
	for (int i = 10, c = 1; board->squares[squareIndex - i] != 9 && c; i += 10) {
		if (board->squares[squareIndex - i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - i};
			c = 0;
		} else if (board->squares[squareIndex - i] * board->playerToMove > 0) {
			c = 0;
		}
		if (c) board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//bottom
	for (int i = 10, c = 1; board->squares[squareIndex + i] != 9 && c; i += 10) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		}
		if (c) board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
}

void generateBishopLegalMoves(Board* board, int squareIndex) {

}

void generateQueenLegalMoves(Board* board, int squareIndex) {

}

void generateKnightLegalMoves(Board* board, int squareIndex) {

}

void generateKingLegalMoves(Board* board, int squareIndex) {

}

void generatePawnLegalMoves(Board* board, int squareIndex) {

}

void generateMoves(Board* board) {
	memset(board->legalMoves, 0, sizeof(board->legalMoves));
	for (int i = 0; i < BOARD_ARRAY_SIZE; i++) {
		int piece = board->squares[i];
		if (piece * board->playerToMove <= 0) continue;
		switch (piece * board->playerToMove) {
			case PAWN:
				generatePawnLegalMoves(board, i);
				break;
			case KNIGHT:
				generateKnightLegalMoves(board, i);
				break;
			case BISHOP:
				generateBishopLegalMoves(board, i);
				break;
			case ROOK:
				generateRookLegalMoves(board, i);
				break;
			case QUEEN:
				generateQueenLegalMoves(board, i);
				break;
			case KING:
				generateKingLegalMoves(board, i);
				break;
		}
	}
}
