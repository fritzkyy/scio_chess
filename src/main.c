#include "chess.h"
#include "scio.h"
#include "interface.h"

int main() {
	/*intro();

	char buffer[256];

	do {

	} while ();*/

	Board* board = createBoard();
	setPosition(board, "startpos");
	//makeMove(board, strToMove("e2e3"));
	//unmakeMove(board, (Move){81, 61});
	/*generateMoves(board, board->playerToMove);
	{
		for (int i = 0; board->legalMoves.moves[i].startSquare != 0; i++) {
			if (board->legalMoves.moves[i].startSquare == -1) continue;
			printf("%d %d\n", board->legalMoves.moves[i].startSquare, board->legalMoves.moves[i].targetSquare);
		}
	}*/
	drawBoard(board);
	/*printBitboard(controlledSquares(board->squares, WHITE));
	printBitboard(controlledSquares(board->squares, BLACK));*/
	int depth = 3;
	perftest(board, depth);
	//printf("%d legal moves depth %d\n", perft(board, depth), depth);
	freeBoard(board);
	return 0;
}
