#include "chess.h"

const char FILES[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Board* createBoard() {
	Board* board = malloc(sizeof(Board));
	if (!board) return NULL;

	memset(board, 0, sizeof(*board));
	board->turn = 0;
	board->playerToMove = WHITE;

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
					putchar('.');
					break;
				case PAWN:
					putchar('P');
					break;
				case -PAWN:
					putchar('p');
					break;
				case KNIGHT:
					putchar('N');
					break;
				case -KNIGHT:
					putchar('n');
					break;
				case BISHOP:
					putchar('B');
					break;
				case -BISHOP:
					putchar('b');
					break;
				case ROOK:
					putchar('R');
					break;
				case -ROOK:
					putchar('r');
					break;
				case QUEEN:
					putchar('Q');
					break;
				case -QUEEN:
					putchar('q');
					break;
				case KING:
					putchar('K');
					break;
				case -KING:
					putchar('k');
					break;
			}
		}
		putchar('\n');
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
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, KING, 0, 0, ROOK, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
			9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
		};
		memcpy(board->squares, pos, sizeof(int) * BOARD_ARRAY_SIZE);
	}
}

void generateRookLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	for (int j = -1; j <= 1; j += 2) {
		for (int i = 1; board->squares[squareIndex + i * j] != 9; i++) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
		for (int i = 10; board->squares[squareIndex + i * j] != 9; i += 10) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
	}
}

void generateBishopLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	for (int j = -1; j <= 1; j += 2) {
		for (int i = 11; board->squares[squareIndex + i * j] != 9; i += 11) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
		for (int i = 9; board->squares[squareIndex + i * j] != 9; i += 9) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
	}
}

void generateQueenLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	for (int j = -1; j <= 1; j += 2) {
		for (int i = 1; board->squares[squareIndex + i * j] != 9; i++) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});;
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
		for (int i = 10; board->squares[squareIndex + i * j] != 9; i += 10) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
		for (int i = 11; board->squares[squareIndex + i * j] != 9; i += 11) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
		for (int i = 9; board->squares[squareIndex + i * j] != 9; i += 9) {
			if (board->squares[squareIndex + i * j] * board->playerToMove > 0) break;
			append(arr, (Move) {squareIndex, squareIndex + i * j});
			if (board->squares[squareIndex + i * j] * board->playerToMove < 0) break;
		}
	}
}

void generateKnightLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	for (int j = -1; j <= 1; j += 2) {
		if (board->squares[squareIndex + 21 * j] * board->playerToMove <= 0 && board->squares[squareIndex + 21 * j] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 21 * j});
		}
		if (board->squares[squareIndex + 19 * j] * board->playerToMove <= 0 && board->squares[squareIndex + 19 * j] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 19 * j});
		}
		if (board->squares[squareIndex + 12 * j] * board->playerToMove <= 0 && board->squares[squareIndex + 12 * j] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 12 * j});
		}
		if (board->squares[squareIndex + 8 * j] * board->playerToMove <= 0 && board->squares[squareIndex + 8 * j] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 8 * j});
		}
	}
}

void generateKingLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (board->squares[squareIndex + i * 10 + j] * board->playerToMove <= 0 && board->squares[squareIndex + i * 10 + j] != 9) {
				append(arr, (Move) {squareIndex, squareIndex + i * 10 + j});
			}
		}
	}
	if (board->castlingStatus != 0) return;
	if (board->playerToMove == WHITE) {
		if (board->squares[93] != 0 || board->squares[94] != 0 || board->squares[96] != 0 || board->squares[97] != 0) return;
		//short
		if ((board->castlingStatus & 0b00000101) == 0 && board->squares[98] == ROOK) {
			append(arr, (Move) {WKINGPOS, WSCSQ});
		}
		//long
		if ((board->castlingStatus & 0b00000011) == 0 && board->squares[91] == ROOK) {
			append(arr, (Move) {WKINGPOS, WLCSQ});
		}
	}
	if (board->playerToMove == BLACK) {
		if (board->squares[23] != 0 || board->squares[24] != 0 || board->squares[26] != 0 || board->squares[27] != 0) return;
		//short
		if ((board->castlingStatus & 0b01010000) == 0 && board->squares[28] == -ROOK) {
			append(arr, (Move) {BKINGPOS, BSCSQ});
		}
		//long
		if ((board->castlingStatus & 0b00110000) == 0 && board->squares[21] == -ROOK) {
			append(arr, (Move) {BKINGPOS, BLCSQ});
		}
	}
}

void generatePawnLegalMoves(Board* board, int squareIndex, MoveArr* arr) {
	if (board->playerToMove == BLACK) {
		if (squareIndex / 10 == 3 && board->squares[squareIndex + 20] == 0 && board->squares[squareIndex + 10] == 0) {
			append(arr, (Move) {squareIndex, squareIndex + 20});
		}
		if (board->squares[squareIndex + 10] == 0) {
			append(arr, (Move) {squareIndex, squareIndex + 10});
		}
		if (board->squares[squareIndex + 9] > 0 && board->squares[squareIndex + 9] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 9});
		}
		if (board->squares[squareIndex + 11] > 0 && board->squares[squareIndex + 11] != 9) {
			append(arr, (Move) {squareIndex, squareIndex + 11});
		}
		if (board->lastPawnMoved / 10 == squareIndex / 10 && squareIndex / 10 == 6) {
			if (board->lastPawnMoved % 10 + 1 == squareIndex % 10) {
				append(arr, (Move) {squareIndex, squareIndex + 11});
			} else if (board->lastPawnMoved % 10 - 1 == squareIndex % 10) {
				append(arr, (Move) {squareIndex, squareIndex + 9});
			}
		}
	} else {
		if (squareIndex / 10 == 8 && board->squares[squareIndex - 20] == 0 && board->squares[squareIndex - 10] == 0) {
			append(arr, (Move) {squareIndex, squareIndex - 20});
		}
		if (board->squares[squareIndex - 10] == 0) {
			append(arr, (Move) {squareIndex, squareIndex - 10});
		}
		if (board->squares[squareIndex - 9] < 0) {
			append(arr, (Move) {squareIndex, squareIndex - 9});
		}
		if (board->squares[squareIndex - 11] < 0) {
			append(arr, (Move) {squareIndex, squareIndex - 11});
		}
		if (board->lastPawnMoved / 10 == squareIndex / 10 && squareIndex / 10 == 5) {
			if (board->lastPawnMoved % 10 + 1 == squareIndex % 10) {
				append(arr, (Move) {squareIndex, squareIndex - 11});
			} else if (board->lastPawnMoved % 10 - 1 == squareIndex % 10) {
				append(arr, (Move) {squareIndex, squareIndex - 9});
			}
		}
	}
}

void generateMoves(Board* board, int player) {
	memcpy(board->legalMoves.moves, legalMoves(board), sizeof(board->legalMoves));
}

MoveArr* legalMoves(Board* board) {
	//MoveArr* arr = createMoveArr(MAX_LEGAL_MOVES);
	MoveArr* arr = malloc(sizeof(*arr) * MAX_LEGAL_MOVES);
	arr->length = MAX_LEGAL_MOVES;
	arr->firstEmptyIndex = 0;

	for (int i = 0; i < BOARD_ARRAY_SIZE; i++) {
		int piece = board->squares[i];
		if (piece * board->playerToMove <= 0) continue;
		switch (piece * board->playerToMove) {
			case PAWN:
				generatePawnLegalMoves(board, i, arr);
				break;
			case KNIGHT:
				generateKnightLegalMoves(board, i, arr);
				break;
			case BISHOP:
				generateBishopLegalMoves(board, i, arr);
				break;
			case ROOK:
				generateRookLegalMoves(board, i, arr);
				break;
			case QUEEN:
				generateQueenLegalMoves(board, i, arr);
				break;
			case KING:
				generateKingLegalMoves(board, i, arr);
				break;
		}
	}
	//filter moves
	for (int i = 0; arr->moves[i].startSquare != 0; i++) {
		if (!isMoveLegal(board->squares, arr->moves[i], board->playerToMove)) arr->moves[i] = (Move) {-1, -1};
	}

	//printf("generated %d moves for %s\n", numLegalMoves(arr), board->playerToMove == 1 ? "white" : "black");

	return arr;
}

bitboard controlledSquares(int squares[], int player) {
	bitboard controlled = 0;
	for (int i = 0; i < BOARD_ARRAY_SIZE; i++) {
		if (squares[i] == 9 || squares[i] * player <= 0) continue;
		controlled |= controlledSquaresForPiece(squares, i);
	}
	return controlled;
}

bitboard controlledSquaresForPiece(int squares[], int square) {
	bitboard controlled = 0;
	int player = (squares[square] > 0) ? WHITE : BLACK;
	switch (abs(squares[square])) {
		case PAWN:
			if (squares[square] > 0) {
				if (squares[square - 11] != 9) controlled |= 1ULL << index64(square - 11);
				if (squares[square - 9] != 9) controlled |= 1ULL << index64(square - 9);
			} else {
				if (squares[square + 11] != 9) controlled |= 1ULL << index64(square + 11);
				if (squares[square + 9] != 9) controlled |= 1ULL << index64(square + 9);
			}
			return controlled;
			break;
		case KNIGHT:
			if (squares[square - 21] != 9) controlled |= 1ULL << index64(square - 21);
			if (squares[square - 19] != 9) controlled |= 1ULL << index64(square - 19);
			if (squares[square - 12] != 9) controlled |= 1ULL << index64(square - 12);
			if (squares[square - 8] != 9) controlled |= 1ULL << index64(square - 8);
			if (squares[square + 21] != 9) controlled |= 1ULL << index64(square + 21);
			if (squares[square + 19] != 9) controlled |= 1ULL << index64(square + 19);
			if (squares[square + 12] != 9) controlled |= 1ULL << index64(square + 12);
			if (squares[square + 8] != 9) controlled |= 1ULL << index64(square + 8);
			return controlled;
			break;
		case BISHOP: {
			for (int i = -1; i <= 1; i += 2) {
				for (int j = 9; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 9) {
					controlled |= 1ULL << index64(square + i * j);
				}
				for (int j = 11; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 11) {
					controlled |= 1ULL << index64(square + i * j);
				}
			}
			return controlled;
		} break;
		case ROOK: {
			for (int i = -1; i <= 1; i += 2) {
				for (int j = 1; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j++) {
					controlled |= 1ULL << index64(square + i * j);
				}
				for (int j = 10; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 10) {
					controlled |= 1ULL << index64(square + i * j);
				}
			}
			return controlled;
		} break;
		case QUEEN: {
			for (int i = -1; i <= 1; i += 2) {
				for (int j = 1; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j++) {
					controlled |= 1ULL << index64(square + i * j);
				}
				for (int j = 10; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 10) {
					controlled |= 1ULL << index64(square + i * j);
				}
				for (int j = 9; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 9) {
					controlled |= 1ULL << index64(square + i * j);
				}
				for (int j = 11; squares[square + i * j] != 9 && (squares[square + i * j] != 0); j += 11) {
					controlled |= 1ULL << index64(square + i * j);
				}
			}
			return controlled;
		} break;
		case KING: {
			for (int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					if (squares[square + 10 * j + k] != 9) controlled |= 1ULL << index64(square + 10 * j + k);
				}
			}
			return controlled;
		} break;
	}
	return 0;
}

inline int index64(int index) {
	return index / 10 * 8 + index % 10 - 17;
}

uint64_t reverseU64(uint64_t n) {
	uint64_t result = 0;
	for (int i = 0; i < 64; i++) {
		result = (result << 1) | (n & 1);
		n >>= 1;
	}
	return result;
}

void printBitboard(uint64_t n) {
	n = reverseU64(n);
	uint64_t mask = 1ULL << 63;
	for (int i = 0; i < 64; i++, mask >>= 1) {
		putchar((n & mask) ? '1' : '0');
		if ((i + 1) % 8 == 0) putchar('\n');
	}
	putchar('\n');
}

int isMoveLegal(int squares[], Move move, int playerToMove) {
	int boardAfterMove[BOARD_ARRAY_SIZE];
	memcpy(boardAfterMove, squares, sizeof(boardAfterMove));
	boardAfterMove[move.targetSquare] = boardAfterMove[move.startSquare];
	boardAfterMove[move.startSquare] = 0;

	return (kingPosition(boardAfterMove, playerToMove) & controlledSquares(boardAfterMove, -playerToMove)) == 0;
}

bitboard kingPosition(int squares[], int player) {
	int i;
	for (i = 0; i < BOARD_ARRAY_SIZE; i++) {
		if (squares[i] * player == KING) break;
	}
	return 1ULL << index64(i);
}

int numLegalMoves(MoveArr* legalMoves) {
	int i = 0;
	while (legalMoves->moves[i].startSquare > 0) {
		i++;
	}
	return i;
}

void makeMove(Board* board, Move move) {
	/*char str[5];
	printMoveToStr(move, str);
	printf("making move %s\n", str);*/
	board->squares[move.targetSquare] = board->squares[move.startSquare];
	board->squares[move.startSquare] = 0;

	if (board->playerToMove == WHITE) board->playerToMove = BLACK;
	else board->playerToMove = WHITE;

	int pieceMoved = move.targetSquare;

	if (abs(pieceMoved) == PAWN) {
		board->lastPawnMoved = move.targetSquare;
		return;
	}
	if (pieceMoved == ROOK) {
		if (move.startSquare == S_A1) board->castlingStatus |= 0b00000010;
		else if (move.startSquare == S_A8) board->castlingStatus |= 0b00000100;
		return;
	} else if (pieceMoved == -ROOK) {
		if (move.startSquare == S_H1) board->castlingStatus |= 0b00100000;
		else if (move.startSquare == S_H8) board->castlingStatus |= 0b01000000;
		return;
	}
	if (pieceMoved == KING) {
		board->castlingStatus |= 0b00000001;
		return;
	} else if (pieceMoved == -KING) {
		board->castlingStatus |= 0b00010000;
		return;
	}
}

void unmakeMove(Board* board, Move move) {
	int pieceMoved = move.startSquare;

	if (abs(pieceMoved) == PAWN) {
		board->lastPawnMoved = 0;
	}
	if (pieceMoved == ROOK) {
		if (move.startSquare == S_A1) board->castlingStatus &= ~0b00000010;
		else if (move.startSquare == S_A8) board->castlingStatus &= ~0b00000100;
	} else if (pieceMoved == -ROOK) {
		if (move.startSquare == S_H1) board->castlingStatus &= ~0b00100000;
		else if (move.startSquare == S_H8) board->castlingStatus &= ~0b01000000;
	}
	if (pieceMoved == KING) {
		board->castlingStatus &= ~0b00000001;
	} else if (pieceMoved == -KING) {
		board->castlingStatus &= ~0b00010000;
	}

	//printf("unmaking move %d %d\n", move.startSquare, move.targetSquare);
	board->squares[move.startSquare] = board->squares[move.targetSquare];
	board->squares[move.targetSquare] = 0;

	if (board->playerToMove == WHITE) board->playerToMove = BLACK;
	else board->playerToMove = WHITE;
}

void append(MoveArr* arr, Move move) {
		arr->moves[arr->firstEmptyIndex] = move;
		char str[5];
		printMoveToStr(move, str);
		//printf("added %s at index %zu\n", str, arr->firstEmptyIndex);
		arr->firstEmptyIndex++;
		return;
}

MoveArr* createMoveArr(size_t length) {
	MoveArr* arr = malloc(sizeof(*arr) * MAX_LEGAL_MOVES);
	if (!arr) return NULL;

	arr->length = length;
	arr->firstEmptyIndex = 0;

	return arr;
}

void printMoveToStr(Move move, char* str) {
	sprintf(str, "%c%d%c%d", FILES[move.startSquare % 10 - 1], 8 - index64(move.startSquare) / 8, FILES[move.targetSquare % 10 - 1], 8 - index64(move.targetSquare) / 8);
}

Move strToMove(char* str) {
	int sfile = 0;
	for (int i = 0; i < 8; i++) {
		if (FILES[i] == str[0]) {
			sfile = i;
			break;
		}
	}
	int startSquare = 100 - (str[1] - '0') * 10 + sfile + 1;
	int tfile = 0;
	for (int i = 0; i < 8; i++) {
		if (FILES[i] == str[2]) {
			tfile = i;
			break;
		}
	}
	int targetSquare = 100 - (str[3] - '0') * 10 + tfile + 1;
	return (Move) {startSquare, targetSquare};
}
