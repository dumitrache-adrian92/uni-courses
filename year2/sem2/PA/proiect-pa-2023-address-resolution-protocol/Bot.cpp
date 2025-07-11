 #include "Bot.h"

#include <bits/stdc++.h>

const std::string Bot::BOT_NAME = "shtou"; /* Edit this, escaped characters are forbidden */

void clearDebugFile() {
	// Open the file in truncate mode to clear the file
	std::ofstream debugFile("bot.dbg", std::ios::trunc);
	if (!debugFile.is_open()) {
		std::cerr << "Failed to open debugging file!" << std::endl;
		return;
	}

	// Close the debugging file
	debugFile.close();
}

Bot::Bot() {
	clearDebugFile();

	allyKingMoved = false;
	allyLeftRookMoved = false;
	allyRightRookMoved = false;
	enemyKingMoved = false;
	enemyLeftRookMoved = false;
	enemyRightRookMoved = false;

	for (int i = 0; i < 5; i++) {
		captured_by_ally[i] = 0;
		captured_by_enemy[i] = 0;
	}

	// Initialize the array with default values
	for (int i = 1; i <= TABLE_SIZE; i++)
		for (int j = 1; j <= TABLE_SIZE; j++) {
			board[i][j] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
			promoted[i][j] = false;
		}

	for (int i = 1; i <= TABLE_SIZE; i++) {
		board[7][i] = std::make_pair(Piece::PAWN, PlaySide::BLACK);
		board[2][i] = std::make_pair(Piece::PAWN, PlaySide::WHITE);
	}
	board[1][1] = std::make_pair(Piece::ROOK, PlaySide::WHITE);
	board[1][8] = std::make_pair(Piece::ROOK, PlaySide::WHITE);
	board[8][1] = std::make_pair(Piece::ROOK, PlaySide::BLACK);
	board[8][8] = std::make_pair(Piece::ROOK, PlaySide::BLACK);

	board[1][2] = std::make_pair(Piece::KNIGHT, PlaySide::WHITE);
	board[1][7] = std::make_pair(Piece::KNIGHT, PlaySide::WHITE);
	board[8][2] = std::make_pair(Piece::KNIGHT, PlaySide::BLACK);
	board[8][7] = std::make_pair(Piece::KNIGHT, PlaySide::BLACK);

	board[1][3] = std::make_pair(Piece::BISHOP, PlaySide::WHITE);
	board[1][6] = std::make_pair(Piece::BISHOP, PlaySide::WHITE);
	board[8][3] = std::make_pair(Piece::BISHOP, PlaySide::BLACK);
	board[8][6] = std::make_pair(Piece::BISHOP, PlaySide::BLACK);

	board[1][4] = std::make_pair(Piece::QUEEN, PlaySide::WHITE);
	board[8][4] = std::make_pair(Piece::QUEEN, PlaySide::BLACK);

	board[1][5] = std::make_pair(Piece::KING, PlaySide::WHITE);
	board[8][5] = std::make_pair(Piece::KING, PlaySide::BLACK);

}

/* from string to coordinates, example:
 * "g4" ---> (4, 7) corresponding to matrix in memory
 */
std::pair<int, int> getCoordsfromString(std::string place) {
	int sy = place.at(0) - 'a' + 1;
	int sx = place.at(1) - '0';

	return std::make_pair(sx, sy);
}

/* from coordinates to string, example:
 * "(4, 7)" ---> "g4" corresponding to matrix in memory
 */
std::string getStringfromCoords(std::pair<int, int> coords) {
	std::string result = "a1";

	result[0] = result[0] + coords.second - 1;
	result[1] = result[1] + coords.first - 1;

	return result;
}

/* gets piece type from encoding */
std::string getPieceType(Piece p)
{
	std::string pieceType = "";
	switch (p) {
		case Piece::ROOK:
			pieceType = "R";
			break;
		case Piece::KNIGHT:
			pieceType = "N";
			break;
		case Piece::BISHOP:
			pieceType = "B";
			break;
		case Piece::QUEEN:
			pieceType = "Q";
			break;
		case Piece::KING:
			pieceType = "K";
			break;
		case Piece::PAWN:
			pieceType = "P";
			break;
		default:
			pieceType = "U";
			break;
	}

	return pieceType;
}

/* returns vector with values from a to b in a random order */
std::vector<int> generateRandomPermutation(int a, int b) {
	int n = b - a + 1; // Calculate the size of the permutation
	std::vector<int> nums(n);
	for (int i = 0; i < n; ++i) {
		nums[i] = a + i; // Generate numbers from a to b
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(nums.begin(), nums.end(), g);
	return nums;
}

/* Just pawn implementation stuff, take it as it is */
int Bot::check_empty_tile_and_existence(std::pair<Piece, PlaySide> chess_board[9][9], int x, int y, PlaySide sideToMove) {
	if(x < 1 || x > 8 || y < 1 || y > 8)
		return -1;
	if(chess_board[x][y].second == PlaySide::NONE)
		return true;
	if(sideToMove == chess_board[x][y].second)
		return -1;
	return 0;
}

// checks if i and j are in the bounds of a chess table
bool inBounds(int i, int j) {
	if (i >= 1 && i <= 8 && j >= 1 && j <= 8)
		return true;

	return false;
}

// puts all possible moves of the knight at (x, y) in the given queue
void Bot::getKnightMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	std::pair<int, int> current_pair = std::make_pair(x, y);

	std::vector<int> perms = generateRandomPermutation(0, 7);

	for(int i = 0; i < 8; i++) {
		/* pick a direction, then go all the way(nu e cazul celor de la CTI) */
		int current_x = knight_direction_x[perms[i]];
		int current_y = knight_direction_y[perms[i]];

		if (inBounds(x + current_x, y + current_y))
			if (chess_board[x + current_x][y + current_y].second != sideToMove)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + current_x, y + current_y))));
	}
}

// puts all possible moves of the rook at (x, y) in the given queue
void Bot::getRookMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	std::pair<int, int> current_pair = std::make_pair(x, y);

	std::vector<int> perms = generateRandomPermutation(0, 3);

	for(int i = 0; i < 4; i++) {
		/* pick a direction, then go all the way(nu e cazul celor de la CTI) */
		int current_x = rook_direction_x[perms[i]];
		int current_y = rook_direction_y[perms[i]];
		int j = 1;
		while(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true) {
			j++;
		}
		while(j > 0) {
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == 0)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			j--;
		}
	}
}

// puts all possible moves of the queen at (x, y) in the given queue
void Bot::getQueenMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	std::pair<int, int> current_pair = std::make_pair(x, y);

	std::vector<int> perms = generateRandomPermutation(0, 7);

	/* All directions */
	for(int i = 0; i < 8; i++) {
		/* pick a direction, then go all the way(nu e cazul celor de la CTI) */
		int current_x = queen_direction_x[perms[i]];
		int current_y = queen_direction_y[perms[i]];
		int j = 1;
		while(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true) {
			j++;
		}
		while(j > 0) {
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == 0)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			j--;
		}
	}
}

// puts all possible moves of the bishop at (x, y) in the given queue
void Bot::getBishopMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	std::pair<int, int> current_pair = std::make_pair(x, y);

	std::vector<int> perms = generateRandomPermutation(0, 3);

	/* All directions */
	for(int i = 0; i < 4; i++) {
		/* pick a direction, then go all the way(nu e cazul celor de la CTI) */
		int current_x = bishop_direction_x[perms[i]];
		int current_y = bishop_direction_y[perms[i]];
		int j = 1;
		while(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true) {
			j++;
		}
		while(j > 0) {
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == true)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			if(Bot::check_empty_tile_and_existence(chess_board, x + j * current_x, y + j * current_y, sideToMove) == 0)
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + j * current_x, y + j * current_y))));
			j--;
		}
	}
}

// puts all possible moves of the king at (x, y) in the given queue
void Bot::getKingMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	std::pair<int, int> current_pair = std::make_pair(x, y);

	std::vector<int> perms = generateRandomPermutation(0, 7);

	/* All directions */
	for(int i = 0; i < 8; i++) {
		/* pick a direction, then go all the way(nu e cazul celor de la CTI) */
		int current_x = king_direction_x[perms[i]];
		int current_y = king_direction_y[perms[i]];

		if(Bot::check_empty_tile_and_existence(chess_board, x + current_x, y + current_y, sideToMove) == true ||
			Bot::check_empty_tile_and_existence(chess_board, x + current_x, y + current_y, sideToMove) == 0)
			q.push(Move::moveTo(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + current_x, y + current_y))));
	}
}

// puts all possible moves of the pawn at (x, y) in the given queue
void Bot::getPawnMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y) {
	int critical_x = 7;
	if(sideToMove == PlaySide::WHITE) {
		critical_x = 2;
	}

	int en_passant_line = 4;
	if (sideToMove == PlaySide::WHITE) {
		en_passant_line = 5;
	}

	// start checking for en passant
	if (x == en_passant_line) {
		// if we have a pawn to our right
		if (chess_board[x][y + 1].first == Piece::PAWN && chess_board[x][y + 1].second != sideToMove) {
			// if that pawn just moved two squares forward
			if (lastMoveDest.first == x && lastMoveDest.second == y + 1 &&
				abs(lastMoveSrc.first - lastMoveDest.first) == 2 && lastMoveSrc.second == y + 1) {
					std::string src = getStringfromCoords(std::make_pair(x, y));
					std::string dst;

					if (sideToMove == PlaySide::BLACK)
						dst = getStringfromCoords(std::make_pair(x - 1, y + 1));
					else
						dst = getStringfromCoords(std::make_pair(x + 1, y + 1));

					q.push(Move::moveTo(src, dst));
				}
		}

		if (chess_board[x][y - 1].first == Piece::PAWN && chess_board[x][y - 1].second != sideToMove) {
			if (lastMoveDest.first == x && lastMoveDest.second == y - 1 &&
				abs(lastMoveSrc.first - lastMoveDest.first) == 2 && lastMoveSrc.second == y - 1) {
					std::string src = getStringfromCoords(std::make_pair(x, y));
					std::string dst;

					if (sideToMove == PlaySide::BLACK)
						dst = getStringfromCoords(std::make_pair(x - 1, y - 1));
					else
						dst = getStringfromCoords(std::make_pair(x + 1, y - 1));

					q.push(Move::moveTo(src, dst));
				}
		}
	}

	std::pair<int, int> current_pair = std::make_pair(x, y);

	/* Trying to capture */
	int dir1_x, dir1_y, dir2_x, dir2_y;
	if (sideToMove == WHITE) {
		dir1_x = white_pawn_capture_x[0];
		dir1_y = white_pawn_capture_y[0];
		dir2_x = white_pawn_capture_x[1];
		dir2_y = white_pawn_capture_y[1];
	} else {
		dir1_x = black_pawn_capture_x[0];
		dir1_y = black_pawn_capture_y[0];
		dir2_x = black_pawn_capture_x[1];
		dir2_y = black_pawn_capture_y[1];
	}

	if (Bot::check_empty_tile_and_existence(chess_board, x + dir1_x, y + dir1_y, sideToMove) == 0) {
		if(x + dir1_x == 8 || x + dir1_x == 1) {
			std::cout << "am promovat piesa" << std::endl;
			std::vector<Piece> pieces;
			pieces.push_back(ROOK);
			pieces.push_back(KNIGHT);
			pieces.push_back(QUEEN);
			pieces.push_back(BISHOP);
			auto rd = std::random_device {};
			auto rng = std::default_random_engine { rd() };
			std::shuffle(std::begin(pieces), std::end(pieces), rng);
			q.push(Move::promote(getStringfromCoords(current_pair),
			 	getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[0]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[1]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[2]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[3]));
		}
		else
			q.push(Move::moveTo(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y))));
	}

	if (Bot::check_empty_tile_and_existence(chess_board, x + dir2_x, y + dir2_y, sideToMove) == 0) {
		if(x + dir2_x == 8 || x + dir2_x == 1) {
			std::cout << "am promovat piesa" << std::endl;
			std::cout << "am promovat piesa" << std::endl;
			std::vector<Piece> pieces;
			pieces.push_back(ROOK);
			pieces.push_back(KNIGHT);
			pieces.push_back(QUEEN);
			pieces.push_back(BISHOP);
			auto rd = std::random_device {};
			auto rng = std::default_random_engine { rd() };
			std::shuffle(std::begin(pieces), std::end(pieces), rng);
			q.push(Move::promote(getStringfromCoords(current_pair),
			 	getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y)), pieces[0]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y)), pieces[1]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y)), pieces[2]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y)), pieces[3]));
		}
		else
			q.push(Move::moveTo(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y))));
	}

	/* Moving without capture */
	if (critical_x == x) {

	if (sideToMove == WHITE) {
		dir1_x = white_pawn_direction_x[0];
		dir1_y = white_pawn_direction_y[0];
		dir2_x = 2 * white_pawn_direction_x[0];
		dir2_y = 2 * white_pawn_direction_y[0];
	} else {
		dir1_x = black_pawn_direction_x[0];
		dir1_y = black_pawn_direction_y[0];
		dir2_x = 2 * black_pawn_direction_x[0];
		dir2_y = 2 * black_pawn_direction_y[0];
	}

	if (Bot::check_empty_tile_and_existence(chess_board, x + dir1_x, y + dir1_y, sideToMove) == true) {
		if(x + dir1_x == 8 || x + dir1_x == 1) {
			std::cout << "am promovat piesa" << std::endl;
			std::cout << "am promovat piesa" << std::endl;
			std::vector<Piece> pieces;
			pieces.push_back(ROOK);
			pieces.push_back(KNIGHT);
			pieces.push_back(QUEEN);
			pieces.push_back(BISHOP);
			auto rd = std::random_device {};
			auto rng = std::default_random_engine { rd() };
			std::shuffle(std::begin(pieces), std::end(pieces), rng);
			q.push(Move::promote(getStringfromCoords(current_pair),
			 	getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[0]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[1]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[2]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[3]));
		}

		else
			q.push(Move::moveTo(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y))));
	}

	if (Bot::check_empty_tile_and_existence(chess_board, x + dir2_x, y + dir2_y, sideToMove) == true &&
	Bot::check_empty_tile_and_existence(chess_board, x + dir2_x - dir1_x, y + dir2_y - dir1_y, sideToMove) == true) {
		if(x + dir2_x == 8 || x + dir2_x == 1) {
			std::cout << "am promovat piesa" << std::endl;
			std::cout << "am promovat piesa" << std::endl;
			std::vector<Piece> pieces;
			pieces.push_back(ROOK);
			pieces.push_back(KNIGHT);
			pieces.push_back(QUEEN);
			pieces.push_back(BISHOP);
			auto rd = std::random_device {};
			auto rng = std::default_random_engine { rd() };
			std::shuffle(std::begin(pieces), std::end(pieces), rng);
			q.push(Move::promote(getStringfromCoords(current_pair),
			 	getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[0]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[1]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[2]));
			q.push(Move::promote(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), pieces[3]));
		}
		else
			q.push(Move::moveTo(getStringfromCoords(current_pair),
				getStringfromCoords(std::make_pair(x + dir2_x, y + dir2_y))));
	}
	} else {
		int dir1_x, dir1_y;

		if (sideToMove == WHITE) {
			dir1_x = white_pawn_direction_x[0];
			dir1_y = white_pawn_direction_y[0];
		} else {
			dir1_x = black_pawn_direction_x[0];
			dir1_y = black_pawn_direction_y[0];
		}

		if (Bot::check_empty_tile_and_existence(chess_board, x + dir1_x, y + dir1_y, sideToMove) == true) {
			if(x + dir1_x == 8 || x + dir1_x == 1)
				q.push(Move::promote(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y)), Piece::KNIGHT));
			else
				q.push(Move::moveTo(getStringfromCoords(current_pair),
					getStringfromCoords(std::make_pair(x + dir1_x, y + dir1_y))));
		}

		}

}

// puts all possible moves in a queue given a side and a board
void Bot::getAllMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove) {
	/*
	 * generate a random order in which we're going to traverse the lines and
	 * columns of the board so we can randomly decide the order in which we'll
	 * generate the moves for each piece, this guarantees a somewhat random game
	 */
	std::vector<int> xx = generateRandomPermutation(1, 8);
	std::vector<int> yy = generateRandomPermutation(1, 8);

	/* Queue current pieces */
	std::queue<std::pair<int, int>> pieces;
	for(int i = 7; i >= 0; i--)
		for(int j = 7; j >= 0; j--) {
			if(chess_board[xx[i]][yy[j]].second == sideToMove)
				pieces.push(std::make_pair(xx[i], yy[j]));
		}

	if (engineColor == sideToMove)
		for (int i = 0; i < 5; i++) {
			if (captured_by_ally[i] != 0) {
				for (int x = 1; x <= 8; x++)
					for (int y = 1; y <= 8; y++) {
						if ((Piece) i == Piece::PAWN && (x == 1 || x == 8))
							continue;

						if (board[x][y].first == Piece::EMPTY)
							q.push(Move::dropIn(getStringfromCoords(std::make_pair(x, y)), (Piece) i));
					}
			}
		}
	else
		for (int i = 0; i < 5; i++) {
			if (captured_by_enemy[i] != 0) {
				for (int x = 1; x <= 8; x++)
					for (int y = 1; y <= 8; y++) {
						if ((Piece) i == Piece::PAWN && (x == 1 || x == 8))
							continue;
						if (board[x][y].first == Piece::EMPTY)
							q.push(Move::dropIn(getStringfromCoords(std::make_pair(x, y)), (Piece) i));
					}
			}
		}

	/* While queue is not empty, generate the moves for the piece
	 * in front of the queue and add the to the move queue
	 */
	while(!pieces.empty()) {
		int x = pieces.front().first;
		int y = pieces.front().second;
		pieces.pop();
		if(chess_board[x][y].first == Piece::QUEEN) {
			Bot::getQueenMoves(chess_board, q, sideToMove, x, y);
		}
		if(chess_board[x][y].first == Piece::BISHOP) {
			Bot::getBishopMoves(chess_board, q, sideToMove, x, y);
		}
		if(chess_board[x][y].first == Piece::PAWN) {
			Bot::getPawnMoves(chess_board, q, sideToMove, x, y);
		}
		if(chess_board[x][y].first == Piece::KNIGHT) {
			Bot::getKnightMoves(chess_board, q, sideToMove, x, y);
		}
		if(chess_board[x][y].first == Piece::ROOK) {
			Bot::getRookMoves(chess_board, q, sideToMove, x, y);
		}
		if(chess_board[x][y].first == Piece::KING) {
			Bot::getKingMoves(chess_board, q, sideToMove, x, y);
		}
	}
}

/* DEBUG TOOL */
void Bot::printChessBoard( Move *last_move, std::pair<Piece, PlaySide> board[9][9]) {
	// Open the debugging file
	std::ofstream debugFile("bot.dbg", std::ios::app);
	if (!debugFile.is_open()) {
		std::cerr << "Failed to open debugging file!" << std::endl;
		return;
	}

	// Loop through each row and column of the board
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			// Check if the spot is empty (i.e., both pieces are -1)
			if (board[i][j].first == -1 && board[i][j].second == -1) {
				debugFile << "none ";
			} else {
				// Print the piece type and color abbreviation
				std::string pieceType = "";
				std::string color = "";
				switch (board[i][j].first) {
					case Piece::ROOK:
						pieceType = "R";
						break;
					case Piece::KNIGHT:
						pieceType = "N";
						break;
					case Piece::BISHOP:
						pieceType = "B";
						break;
					case Piece::QUEEN:
						pieceType = "Q";
						break;
					case Piece::KING:
						pieceType = "K";
						break;
					case Piece::PAWN:
						pieceType = "P";
						break;
					default:
						pieceType = "U";
						break;
				}
				switch (board[i][j].second) {
					case PlaySide::WHITE:
						color = "W";
						break;
					case PlaySide::BLACK:
						color = "B";
						break;
					default:
						color = "U";
						break;
				}
				debugFile << pieceType << color << " ";
			}
		}
		debugFile << std::endl; // Move to the next row
	}

	debugFile << "ally king moved: " << allyKingMoved<<std::endl;
	debugFile << "enemy king moved: " << enemyKingMoved<<std::endl;
	debugFile << "ally left rook moved: " << allyLeftRookMoved<<std::endl;
	debugFile << "ally right rook moved: " << allyRightRookMoved<<std::endl;
	debugFile << "enemy left rook moved: " << enemyLeftRookMoved<<std::endl;
	debugFile << "enemy right rook moved: " << enemyRightRookMoved<<std::endl;

	//Print last move
	std::string source = last_move->getSource().value_or("BAD");
	std::string dest = last_move->getDestination().value_or("BAD");
	std::pair<int, int> d = getCoordsfromString(dest);
	debugFile << std::endl << "piece "<< board[d.first][d.second].first << " moved from " << source << " to " << dest << std::endl;

	/* Print captures */
	for (int i = 0; i < 5; i++) {
		debugFile << "captured by ally " << captured_by_ally[i] << std::endl;
		debugFile << "captured by enemy " << captured_by_enemy[i] << std::endl;
	}

	debugFile << "\n";
	// Close the debugging file
	debugFile.close();
}

int Bot::is_in_check(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side) {
	/* Search for the side's King */
	int x, y;

	for(int i = 8; i > 0; i--)
		for(int j = 8; j > 0; j--)
			if(chess_board[i][j].second == side && chess_board[i][j].first == KING) {
				x = i;
				y = j;
			}

	/* Get opposite side */
	PlaySide opposite_side = BLACK;
	if(side == opposite_side)
		opposite_side = WHITE;

	/* Get all enemy moves, check if one can take my king */
	std::queue<Move *> q;
	Bot::getAllMoves(chess_board, q, opposite_side);

	/* now i have to see if there is a move that leads to the king being captured */

	while(!q.empty()) {
		std::pair trial = getCoordsfromString(q.front()->destination.value_or("baad"));
		q.pop();

		if(trial.first == x && trial.second == y)
			return true;
	}

	return false;
}

/* Finds out if the given move would put side in check*/
bool Bot::check_if_check(std::pair<Piece, PlaySide> chess_board[9][9], Move *move, PlaySide side) {
	std::pair<Piece, PlaySide> board_copy[9][9];
	int i, j;

	PlaySide opposingSide;

	if (side == PlaySide::BLACK)
		opposingSide = PlaySide::WHITE;
	else
		opposingSide = PlaySide::BLACK;

	// copy the board
	for (i = 1; i <= TABLE_SIZE; i++)
		for (j = 1; j <= TABLE_SIZE; j++) {
			board_copy[i][j].first = board[i][j].first;
			board_copy[i][j].second = board[i][j].second;
		}

	// coords of source and destination of the move as they are written in memory
	std::string source = move->getSource().value_or("BAD");
	std::pair<int, int> s = getCoordsfromString(source);

	std::string dest = move->getDestination().value_or("BAD");
	std::pair<int, int> d = getCoordsfromString(dest);

	// make the move on the copied board
	if (move->isNormal()) {
		// move the piece to its new position
		board_copy[d.first][d.second] = board_copy[s.first][s.second];
		// empty its original position
		board_copy[s.first][s.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
	} else if (move->isPromotion()) {
		// move the piece to its new position and change its value
		board_copy[d.first][d.second] = std::make_pair(move->getReplacement().value(), side);
		// empty its original position
		board_copy[s.first][s.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
	} else if (move->isDropIn()) {
		// move the piece to its position
		board_copy[d.first][d.second] = std::make_pair(move->getReplacement().value(), side);
	}

	/* check if the king is in danger following the move by generating all
	 * the moves on the previous side and seeing if any of the lead to the
	 * king being captured
	 */
	std::queue<Move *> unfiltered_moves;
	getAllMoves(board_copy, unfiltered_moves, opposingSide);

	// find the king
	int x, y;
	for (i = 1; i <= TABLE_SIZE; i++)
		for (j = 1; j <= TABLE_SIZE; j++)
			if (board_copy[i][j].first == Piece::KING && board_copy[i][j].second == side) {
				x = i;
				y = j;
				i = 100;
				j = 100;
			}

	// check if any moves capture the king
	while (!unfiltered_moves.empty()) {
		Move *m = unfiltered_moves.front();
		std::pair<int, int> dest = getCoordsfromString(m->destination.value_or("baad"));

		if (!m->isDropIn() && dest.first == x && dest.second == y)
			return true;

		unfiltered_moves.pop();
	}

	return false;
}

void Bot::change_board(std::pair<Piece, PlaySide> *chess_board[9], Move *move) {
	/* Coords of source and destination as they are written in memory */
	std::string source = move->getSource().value_or("BAD");
	std::pair<int, int> s = getCoordsfromString(source);

	std::string dest = move->getDestination().value_or("BAD");
	std::pair<int, int> d = getCoordsfromString(dest);

	// move the piece to its new position
	chess_board[d.first][d.second] = chess_board[s.first][s.second];

	// empty its original position
	chess_board[s.first][s.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
}

/* checks if any of the squares traversed during a kingside castle are attacked,
 * meaning it check the king's square and all the squares to the right of the
 * king minus the rook's square */
bool Bot::kingsidePathAttacked(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side) {
	PlaySide opposingSide;

	if (side == PlaySide::BLACK)
		opposingSide = PlaySide::WHITE;
	else
		opposingSide = PlaySide::BLACK;

	// find the king
	int x, y;
	for (int i = 1; i <= TABLE_SIZE; i++)
		for (int j = 1; j <= TABLE_SIZE; j++)
			if (chess_board[i][j].first == Piece::KING && chess_board[i][j].second == side) {
				x = i;
				y = j;
				i = 100;
				j = 100;
			}

	// check if the rook is still there
	if (chess_board[x][8].first != Piece::ROOK)
		return true;

	// check if the spaces between the king and the rook are empty
	for (int i = y + 1; i < 8; i++)
		if (chess_board[x][i].first != Piece::EMPTY)
			return true;

	// generate all moves of the opponent
	std::queue<Move *> unfiltered_moves;
	getAllMoves(chess_board, unfiltered_moves, opposingSide);

	// check if any moves capture the king
	while (!unfiltered_moves.empty()) {
		Move *m = unfiltered_moves.front();
		std::pair<int, int> dest = getCoordsfromString(m->destination.value_or("baad"));

		for (int i = y; i < 8; i++)
			if (!m->isDropIn() && dest.first == x && dest.second == i)
				return true;

		unfiltered_moves.pop();
	}

	return false;
}

bool Bot::queensidePathAttacked(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side) {
	PlaySide opposingSide;

	if (side == PlaySide::BLACK)
		opposingSide = PlaySide::WHITE;
	else
		opposingSide = PlaySide::BLACK;

	// find the king
	int x, y;
	for (int i = 1; i <= TABLE_SIZE; i++)
		for (int j = 1; j <= TABLE_SIZE; j++)
			if (chess_board[i][j].first == Piece::KING && chess_board[i][j].second == side) {
				x = i;
				y = j;
				i = 100;
				j = 100;
			}

	// check if the rook is still there
	if (chess_board[x][1].first == Piece::ROOK)
		return true;

	// check if the spaces between the king and the rook are empty
	for (int i = y - 1; i >= 2; i--)
			if (chess_board[x][i].first != Piece::EMPTY)
				return true;


	// generate all moves of the opponent
	std::queue<Move *> unfiltered_moves;
	getAllMoves(chess_board, unfiltered_moves, opposingSide);

	// check if any moves attack the king or the squares to the left of the king
	while (!unfiltered_moves.empty()) {
		Move *m = unfiltered_moves.front();
		std::pair<int, int> dest = getCoordsfromString(m->destination.value_or("baad"));

		for (int i = y; i > 2; i--)
			if (!m->isDropIn() && dest.first == x && dest.second == i)
				return true;

		unfiltered_moves.pop();
	}


	return false;
}

void Bot::recordMove(Move* move, PlaySide sideToMove, PlaySide engineSide) {
	if(move == NULL)
		return;

	/* Coords of source and destination as they are written in memory */
	std::string source = move->getSource().value_or("BAD");
	std::pair<int, int> s = getCoordsfromString(source);

	std::string dest = move->getDestination().value_or("BAD");
	std::pair<int, int> d = getCoordsfromString(dest);

	lastMoveSrc.first = s.first;
	lastMoveSrc.second = s.second;

	lastMoveDest.first = d.first;
	lastMoveDest.second = d.second;

	/* If not promotion or drop-in */
	if (move->isNormal()) {
		// check if it's a capture
		if(board[d.first][d.second].second != NONE) {
			if (sideToMove == engineSide) {
				if (!promoted[d.first][d.second])
					captured_by_ally[board[d.first][d.second].first]++;
				else
					captured_by_ally[Piece::PAWN]++;
			}
			else
				if (!promoted[d.first][d.second])
					captured_by_enemy[board[d.first][d.second].first]++;
				else
					captured_by_enemy[Piece::PAWN]++;
		}

		//check for en passant
		if(board[s.first][s.second].first == PAWN)
			if(board[d.first][d.second].first == EMPTY)
				if(s.second != d.second) {
					if(board[s.first][s.second].second == WHITE) {
						board[d.first-1][d.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
						promoted[d.first-1][d.second] = false;
					}
					else {
						board[d.first+1][d.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
						promoted[d.first+1][d.second] = false;
					}

					if (sideToMove == engineSide)
						captured_by_ally[Piece::PAWN]++;
					else
						captured_by_enemy[Piece::PAWN]++;
				}

		// move the piece to its new position
		board[d.first][d.second] = board[s.first][s.second];
		promoted[d.first][d.second] = promoted[s.first][s.second];

		// empty its original position
		board[s.first][s.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
		promoted[s.first][s.second] = false;

		// check if this move was a castle
		if (board[d.first][d.second].first == Piece::KING) {
			// if we moved 2 positions to the right, we castled kingside
			// if we moved 2 positions to the left, we castled queenside
			if (d.second - 2 == s.second) {
				// move rook
				board[d.first][6] = board[d.first][8];
				// empty its original position
				board[d.first][8] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
			} else if (d.second + 2 == s.second) {
				// move rook
				board[d.first][4] = board[d.first][1];
				// empty its original position
				board[d.first][1] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
			}
		}

		// memorize if we moved a king or a rook so we can invalidate castling
		if (board[d.first][d.second].first == Piece::KING) {
			if (board[d.first][d.second].second == engineSide)
				allyKingMoved = true;
			else
				enemyKingMoved = true;
		} else if (board[d.first][d.second].first == Piece::ROOK) {
			if (s.first == 1 && s.second == 1) {
				if (board[d.first][d.second].second == engineSide)
					allyLeftRookMoved = true;
				else
					enemyLeftRookMoved = true;
			} else if (s.first == 1 && s.second == 8) {
				if (board[d.first][d.second].second == engineSide)
					allyRightRookMoved = true;
				else
					enemyRightRookMoved = true;
			} else if (s.first == 8 && s.second == 1) {
				if (board[d.first][d.second].second == engineSide)
					allyLeftRookMoved = true;
				else
					enemyLeftRookMoved = true;
			} else if (s.first == 8 && s.second == 8) {
				if (board[d.first][d.second].second == engineSide)
					allyRightRookMoved = true;
				else
					enemyRightRookMoved = true;
			}
		}
	} else if (move->isPromotion()) {
		// check if it's a capture
		if(board[d.first][d.second].second != NONE) {
			if (sideToMove == engineSide) {
				if (!promoted[d.first][d.second])
					captured_by_ally[board[d.first][d.second].first]++;
				else
					captured_by_ally[Piece::PAWN]++;
			}
			else
				if (!promoted[d.first][d.second])
					captured_by_enemy[board[d.first][d.second].first]++;
				else
					captured_by_enemy[Piece::PAWN]++;
		}

		// move the piece to its new position and change its value
		board[d.first][d.second] = std::make_pair(move->getReplacement().value(), sideToMove);
		promoted[d.first][d.second] = promoted[s.first][s.second];
		// empty its original position
		board[s.first][s.second] = std::make_pair(Piece::EMPTY, PlaySide::NONE);
		promoted[s.first][s.second] = false;

		promoted[d.first][d.second] = true;
	} else if (move->isDropIn()) {
		// move the piece to its position
		board[d.first][d.second] = std::make_pair(move->getReplacement().value(), sideToMove);

		if (engineSide == sideToMove)
			captured_by_ally[board[d.first][d.second].first]--;
		else
			captured_by_enemy[board[d.first][d.second].first]--;
	}

	printChessBoard(move, Bot::board);
}

Move* Bot::calculateNextMove(PlaySide engineSide) {
	engineColor = engineSide;
  /* Play move for the side the engine is playing (Hint: Main.getEngineSide())
   * Make sure to record your move in custom structures before returning.
   *
   * Return move that you are willing to submit
   * Move is to be constructed via one of the factory methods declared in Move.h */

	std::queue<Move *> unfiltered_moves;
	std::queue<Move *> filtered_moves;

	// generate all possible moves without checking if they lead to a check
	getAllMoves(board, unfiltered_moves, engineSide);

	/* filter out the moves that lead to a check and also determine if the
	 * squares to the left or to the right (with the exception of the rook
	 * squares) of the king are attacked so we can check castling */
	while (!unfiltered_moves.empty()) {
		Move *m = unfiltered_moves.front();

		if (!check_if_check(board, m, engineSide))
			filtered_moves.push(m);

		unfiltered_moves.pop();
	}

	// verify if we can castle kingside and do it if we can
	if (!allyKingMoved && !allyRightRookMoved && !kingsidePathAttacked(board, engineSide)) {
		int destX, srcX;
		int destY = 7, srcY = 5;

		if (engineSide == PlaySide::BLACK) {
			destX = 8;
			srcX = 8;
		}
		else {
			destX = 1;
			srcX = 1;
		}
		std::string source = getStringfromCoords(std::make_pair(srcX, srcY));
		std::string destination = getStringfromCoords(std::make_pair(destX, destY));

		Move *m = Move::moveTo(source, destination);

		filtered_moves.push(m);
	}

	// verify if we can castle queenside and do it if we can
	if (!allyKingMoved && !allyLeftRookMoved && !queensidePathAttacked(board, engineSide)) {
		int destX, srcX;
		int destY = 3, srcY = 5;

		if (engineSide == PlaySide::BLACK) {
			destX = 8;
			srcX = 8;
		}
		else {
			destX = 1;
			srcX = 1;
		}
		std::string source = getStringfromCoords(std::make_pair(srcX, srcY));
		std::string destination = getStringfromCoords(std::make_pair(destX, destY));

		Move *m = Move::moveTo(source, destination);

		filtered_moves.push(m);
	}

	/* make a move, chosen randomly since we randomized the order
	 * in which we generate moves
	 */
	Bot::recordMove(filtered_moves.front(), engineSide, engineSide);

	return filtered_moves.front();
}

std::string Bot::getBotName() { return Bot::BOT_NAME; }
