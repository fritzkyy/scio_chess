#include "chess.h"

size_t nPositions;

void perft(Board* board, int depth) {
	if (depth == 0) {
		nPositions++;
		return;
	}

	nPositions = 0;
	MoveArr* moves = legalMoves(board);

	for (int m = 0; moves->moves[m].startSquare != 0; m++) {
		Move move = moves->moves[m];
		makeMove(board, move);
		size_t p = nPositions;
		perft(board, depth - 1);
		unmakeMove(board, move);

		char str[5];
		printMoveToStr(move, str);
		printf("move %s: %d\n", str, nPositions - p);
	}

	//free(moves);
	printf("positions at depth %d: %zu\n", depth, nPositions);
	return;
}

void perftest(Board* board, int depth) {
	nPositions = 0;
	MoveArr* moves = legalMoves(board);

	for (int m = 0; moves->moves[m].startSquare != 0; m++) {
		Move move = moves->moves[m];
		makeMove(board, move);
		size_t p = nPositions;
		perft(board, depth - 1);
		unmakeMove(board, move);

		char str[5];
		printMoveToStr(move, str);
		printf("move %s: %d\n", str, nPositions - p);
	}

	//free(moves);

	return;
}
