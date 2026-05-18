#include "chess.h"

int main() {
	Board* board = createBoard();
	setPosition(board, "");
	//generateMoves(board);
	{
		int i = 0;
		while (board->legalMoves[i].startSquare != 0) {
			printf("%d %d %d\n",board->legalMoves[i].moveType,
			board->legalMoves[i].startSquare, board->legalMoves[i].targetSquare);
			i++;
		}
	}
	printBitboard(controlledSquares(board->squares, 1));
	printBitboard(controlledSquares(board->squares, -1));
	drawBoard(board);
	freeBoard(board);
	return 0;
}
