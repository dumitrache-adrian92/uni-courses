 #ifndef BOT_H
#define BOT_H
#include <bits/stdc++.h>

#include "Move.h"
#include "PlaySide.h"
#include "Piece.h"

#define TABLE_SIZE 8

class Bot {
 private:
  static const std::string BOT_NAME;
  std::pair<Piece, PlaySide> board[9][9];
  bool promoted[9][9];
  std::vector<int> captured_by_ally = {0, 0, 0, 0, 0};
  std::vector<int> captured_by_enemy = {0, 0, 0, 0, 0};
  PlaySide engineColor;
  std::pair<int, int> lastMoveSrc;
  std::pair<int, int> lastMoveDest;

  /* A smart bot knows how to move pieces, right? */

  // Directions for a bishop
  std::vector<int> bishop_direction_x = {1, 1, -1, -1};  // x-axis
  std::vector<int> bishop_direction_y = {1, -1, 1, -1};  // y-axis

  // Directions for a rook
  std::vector<int> rook_direction_x = {1, -1, 0, 0};  // x-axis
  std::vector<int> rook_direction_y = {0, 0, 1, -1};  // y-axis

  // Directions for a queen
  std::vector<int> queen_direction_x = {1, 1, -1, -1, 1, -1, 0, 0};  // x-axis
  std::vector<int> queen_direction_y = {1, -1, 1, -1, 0, 0, 1, -1};  // y-axis

  // Directions for a knight
  std::vector<int> knight_direction_x = {2, 2, -2, -2, 1, 1, -1, -1};  // x-axis
  std::vector<int> knight_direction_y = {1, -1, 1, -1, 2, -2, 2, -2};  // y-axis

  // Directions for a king
  std::vector<int> king_direction_x = {1, 1, 1, -1, -1, -1, 0, 0};  // x-axis
  std::vector<int> king_direction_y = {1, -1, 0, 1, -1, 0, 1, -1};  // y-axis

  // Directions for a black pawn
  std::vector<int> black_pawn_direction_y = {0};             // x-axis (no movement)
  std::vector<int> black_pawn_direction_x = {-1};     // y-axis (up)

  std::vector<int> black_pawn_capture_y = {-1, 1};
  std::vector<int> black_pawn_capture_x = {-1, -1};

  // Directions for a white pawn
  std::vector<int> white_pawn_direction_y = {0};             // x-axis (no movement)
  std::vector<int> white_pawn_direction_x = {1};     // y-axis (down)

  std::vector<int> white_pawn_capture_y = {1, -1};
  std::vector<int> white_pawn_capture_x = {1, 1};

  // we need to remember these so we can confirm if castling is possible or not
  bool allyKingMoved, allyLeftRookMoved, allyRightRookMoved;
  bool enemyKingMoved, enemyLeftRookMoved, enemyRightRookMoved;
 public:
  Bot();

  /* Gets all possible moves from current state; computes them
   * only for sideToMove */
  void getAllMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove);
  void getPawnMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  void getBishopMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  void getKingMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  void getQueenMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  void getRookMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  void getKnightMoves(std::pair<Piece, PlaySide> chess_board[9][9], std::queue<Move *> &q, PlaySide sideToMove, int x, int y);
  bool kingsidePathAttacked(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side);
  bool queensidePathAttacked(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side);

  /* checks if side is in check */
  int is_in_check(std::pair<Piece, PlaySide> chess_board[9][9], PlaySide side);
  bool check_if_check(std::pair<Piece, PlaySide> chess_board[9][9], Move *move, PlaySide side);
  int check_empty_tile_and_existence(std::pair<Piece, PlaySide> chess_board[9][9], int x, int y, PlaySide sideToMove);

  /* changes a board, it's used for check */
  void change_board(std::pair<Piece, PlaySide> *chess_board[9], Move *move);

  /**
   * Record move (either by enemy in normal mode, or by either side
   * in force mode) in custom structures
   * @param move received move
   * @param sideToMode side to move
   */
  void recordMove(Move* move, PlaySide sideToMove, PlaySide engineSide);

  /**
   * Calculates next move, in response to enemyMove
   * @param enemyMove the enemy's last move
   *                  null if this is the opening move, or previous
   *                  move has been recorded in force mode
   * @return your move
   */
  Move* calculateNextMove(PlaySide engineSide);

  static std::string getBotName();

  void printChessBoard(Move *move, std::pair<Piece, PlaySide> board[9][9]);
};
#endif
