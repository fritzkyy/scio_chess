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
			9, -PAWN, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, -BISHOP, 0, 0, 0, 0, 0, 0, 9,
			9, 0, KING, 0, 0, 0, 0, -KNIGHT, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, PAWN, 0, 0, 0, 0, 0, 0, 9,
			9, PAWN, 0, 0, 0, 0, 0, 0, 0, 9,
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
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//right
	for (int i = 1, c = 1; board->squares[squareIndex + i] != 9 && c; i++) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
	//top
	for (int i = 10, c = 1; board->squares[squareIndex - i] != 9 && c; i += 10) {
		if (board->squares[squareIndex - i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - i};
			c = 0;
		} else if (board->squares[squareIndex - i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//bottom
	for (int i = 10, c = 1; board->squares[squareIndex + i] != 9 && c; i += 10) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
}

void generateBishopLegalMoves(Board* board, int squareIndex) {
	int firstEmptyIndex = 0;
	for (int i = 0; i < MAX_LEGAL_MOVES; i++) {
		if (board->legalMoves[i].startSquare == 0) {
			firstEmptyIndex = i;
			break;
		}
	}
	printf("first empty index %d\n", firstEmptyIndex);

	//top-left
	for (int i = 1, c = 1; board->squares[squareIndex - 11 * i] != 9 && c; i++) {
		if (board->squares[squareIndex - 11 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 11 * i};
			c = 0;
		} else if (board->squares[squareIndex - 11 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 11 * i};
	}
	//top-right
	for (int i = 1, c = 1; board->squares[squareIndex - 9 * i] != 9 && c; i++) {
		if (board->squares[squareIndex - 9 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 9 * i};
			c = 0;
		} else if (board->squares[squareIndex - 9 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 9 * i};
	}
	//bottom-left
	for (int i = 1, c = 1; board->squares[squareIndex + 9 * i] != 9 && c; i++) {
		if (board->squares[squareIndex + 9 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 9 * i};
			c = 0;
		} else if (board->squares[squareIndex + 9 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 9 * i};
	}
	//bottom-right
	for (int i = 1, c = 1; board->squares[squareIndex + 11 * i] != 9 && c; i++) {
		if (board->squares[squareIndex + 11 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 11 * i};
			c = 0;
		} else if (board->squares[squareIndex + 11 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 11 * i};
	}
}

void generateQueenLegalMoves(Board* board, int squareIndex) {
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
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//right
	for (int i = 1, c = 1; board->squares[squareIndex + i] != 9 && c; i++) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
	//top
	for (int i = 10, c = 1; board->squares[squareIndex - i] != 9 && c; i += 10) {
		if (board->squares[squareIndex - i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - i};
			c = 0;
		} else if (board->squares[squareIndex - i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - i};
	}
	//bottom
	for (int i = 10, c = 1; board->squares[squareIndex + i] != 9 && c; i += 10) {
		if (board->squares[squareIndex + i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i};
			c = 0;
		} else if (board->squares[squareIndex + i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i};
	}
	//top-left
	for (int i = 1, c = 1; board->squares[squareIndex - 11 * i] != 9 && c; i++) {
		if (board->squares[squareIndex - 11 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 11 * i};
			c = 0;
		} else if (board->squares[squareIndex - 11 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 11 * i};
	}
	//top-right
	for (int i = 1, c = 1; board->squares[squareIndex - 9 * i] != 9 && c; i++) {
		if (board->squares[squareIndex - 9 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 9 * i};
			c = 0;
		} else if (board->squares[squareIndex - 9 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 9 * i};
	}
	//bottom-left
	for (int i = 1, c = 1; board->squares[squareIndex + 9 * i] != 9 && c; i++) {
		if (board->squares[squareIndex + 9 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 9 * i};
			c = 0;
		} else if (board->squares[squareIndex + 9 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 9 * i};
	}
	//bottom-right
	for (int i = 1, c = 1; board->squares[squareIndex + 11 * i] != 9 && c; i++) {
		if (board->squares[squareIndex + 11 * i] * board->playerToMove < 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 11 * i};
			c = 0;
		} else if (board->squares[squareIndex + 11 * i] * board->playerToMove > 0) {
			c = 0;
		} else board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 11 * i};
	}
}

void generateKnightLegalMoves(Board* board, int squareIndex) {
	int firstEmptyIndex = 0;
	for (int i = 0; i < MAX_LEGAL_MOVES; i++) {
		if (board->legalMoves[i].startSquare == 0) {
			firstEmptyIndex = i;
			break;
		}
	}
	printf("first empty index %d\n", firstEmptyIndex);

	//top
	if (board->squares[squareIndex - 21] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 21};
	} else if (board->squares[squareIndex - 21] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 21};
	}
	if (board->squares[squareIndex - 19] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 19};
	} else if (board->squares[squareIndex - 19] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 19};
	}
	//bottom
	if (board->squares[squareIndex + 21] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 21};
	} else if (board->squares[squareIndex + 21] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 21};
	}
	if (board->squares[squareIndex + 19] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 19};
	} else if (board->squares[squareIndex + 19] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 19};
	}
	//left
	if (board->squares[squareIndex - 12] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 12};
	} else if (board->squares[squareIndex - 12] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 12};
	}
	if (board->squares[squareIndex + 8] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 8};
	} else if (board->squares[squareIndex + 8] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 8};
	}
	//right
	if (board->squares[squareIndex + 12] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 12};
	} else if (board->squares[squareIndex + 12] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 12};
	}
	if (board->squares[squareIndex - 8] * board->playerToMove < 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 8};
	} else if (board->squares[squareIndex - 8] == 0) {
		board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 8};
	}
}

void generateKingLegalMoves(Board* board, int squareIndex) {
	int firstEmptyIndex = 0;
	for (int i = 0; i < MAX_LEGAL_MOVES; i++) {
		if (board->legalMoves[i].startSquare == 0) {
			firstEmptyIndex = i;
			break;
		}
	}
	printf("first empty index %d\n", firstEmptyIndex);

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (board->squares[squareIndex + i * 10 + j] * board->playerToMove < 0) {
				board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + i * 10 + j};
			} else if (board->squares[squareIndex + i * 10 + j] == 0) {
				board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + i * 10 + j};
			}
		}
	}
}

void generatePawnLegalMoves(Board* board, int squareIndex) {
	int firstEmptyIndex = 0;
	for (int i = 0; i < MAX_LEGAL_MOVES; i++) {
		if (board->legalMoves[i].startSquare == 0) {
			firstEmptyIndex = i;
			break;
		}
	}
	printf("first empty index %d\n", firstEmptyIndex);

	if (board->playerToMove == -1) {
		if (squareIndex / 10 == 3 && board->[squareIndex + 20] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 20};
		}
		if (board->[squareIndex + 10] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 10};
		}
		if (board->[squareIndex + 9] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 9};
		}
		if (board->[squareIndex + 11] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 11};
		}
	} else {
		if (squareIndex / 10 == 8 && board->[squareIndex - 20] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 20};
		}
		if (board->[squareIndex - 10] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 10};
		}
		if (board->[squareIndex - 9] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 9};
		}
		if (board->[squareIndex - 11] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 11};
		}
	}
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
