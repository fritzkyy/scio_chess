#include "chess.h"

int main() {
	Board* board = createBoard();
	setPosition(board, "startpos");
	generateMoves(board, board->playerToMove);
	{
		int i = 0;
		while (board->legalMoves[i].startSquare != 0) {
			if (board->legalMoves[i].startSquare == -1) {
				i++;
				continue;
			}
			printf("%d %d\n", board->legalMoves[i].startSquare, board->legalMoves[i].targetSquare);
			i++;
		}
	}
	printBitboard(controlledSquares(board->squares, 1));
	printBitboard(controlledSquares(board->squares, -1));
	drawBoard(board);
	printf("%d legal moves\n", numLegalMoves(board->legalMoves));
	freeBoard(board);
	return 0;
}
