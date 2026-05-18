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
			9, 0, KING, 0, 0, 0, 0, -KNIGHT, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, 0, 0, 0, 0, 0, 0, 0, 0, 9,
			9, -KING, 0, 0, 0, 0, 0, 0, 0, 9,
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
		if (squareIndex / 10 == 3 && board->squares[squareIndex + 20] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 20};
		}
		if (board->squares[squareIndex + 10] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex + 10};
		}
		if (board->squares[squareIndex + 9] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 9};
		}
		if (board->squares[squareIndex + 11] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex + 11};
		}
	} else {
		if (squareIndex / 10 == 8 && board->squares[squareIndex - 20] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 20};
		}
		if (board->squares[squareIndex - 10] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {MOVEMENT, squareIndex, squareIndex - 10};
		}
		if (board->squares[squareIndex - 9] == 0) {
			board->legalMoves[firstEmptyIndex++] = (Move) {CAPTURE, squareIndex, squareIndex - 9};
		}
		if (board->squares[squareIndex - 11] == 0) {
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

bitboard controlledSquares(int squares[], int player) {
	bitboard controlled = 0;
	for (int i = 0; i < BOARD_ARRAY_SIZE; i++) {
		if (squares[i] == 9 || squares[i] * player <= 0) continue;
		switch (squares[i] * player) {
			case PAWN:
				if (player == 1) {
					if (squares[i - 11] != 9) controlled |= 1ULL << index64(i - 11);
					if (squares[i - 9] != 9) controlled |= 1ULL << index64(i - 9);
				} else if (player == -1) {
					if (squares[i + 11] != 9) controlled |= 1ULL << index64(i + 11);
					if (squares[i + 9] != 9) controlled |= 1ULL << index64(i + 9);
				}
				break;
			case KNIGHT:
				if (squares[i - 21] != 9) controlled |= 1ULL << index64(i - 21);
				if (squares[i - 19] != 9) controlled |= 1ULL << index64(i - 19);
				if (squares[i - 12] != 9) controlled |= 1ULL << index64(i - 12);
				if (squares[i - 8] != 9) controlled |= 1ULL << index64(i - 8);
				if (squares[i + 21] != 9) controlled |= 1ULL << index64(i + 21);
				if (squares[i + 19] != 9) controlled |= 1ULL << index64(i + 19);
				if (squares[i + 12] != 9) controlled |= 1ULL << index64(i + 12);
				if (squares[i + 8] != 9) controlled |= 1ULL << index64(i + 8);
				break;
			case BISHOP: {
				int j = 11;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 11;
					}
				}
				j = 11;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 11;
					}
				}
				j = 9;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 9;
					}
				}
				j = 9;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 9;
					}
				}
			} break;
			case ROOK: {
				int j = 1;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j++;
					}
				}
				j = 1;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j++;
					}
				}
				j = 10;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 10;
					}
				}
				j = 10;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 10;
					}
				}
			} break;
			case QUEEN: {
				int j = 1;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j++;
					}
				}
				j = 1;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j++;
					}
				}
				j = 10;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 10;
					}
				}
				j = 10;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 10;
					}
				}
				j = 11;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 11;
					}
				}
				j = 11;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 11;
					}
				}
				j = 9;
				while (squares[i - j] != 9) {
					if (squares[i - j] * player > 0) break;
					if (squares[i - j] * player < 0) {
						controlled |= 1ULL << index64(i - j);
						break;
					} else {
						controlled |= 1ULL << index64(i - j);
						j += 9;
					}
				}
				j = 9;
				while (squares[i + j] != 9) {
					if (squares[i + j] * player > 0) break;
					if (squares[i + j] * player < 0) {
						controlled |= 1ULL << index64(i + j);
						break;
					} else {
						controlled |= 1ULL << index64(i + j);
						j += 9;
					}
				}
			} break;
			case KING: {
				for (int j = -1; j <= 1; j++) {
					for (int k = -1; k <= 1; k++) {
						if (squares[i + 10 * j + k] != 9) controlled |= 1ULL << index64(i + 10 * j + k);
					}
				}
			} break;
		}
	}
	return controlled;
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
