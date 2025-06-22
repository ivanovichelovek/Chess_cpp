#include <iostream>

using namespace std;

class Board
{
public:
    Peace board[8][8];
};
/*
    0   1   2   3   4   5   6   7

0   R   KN  B   Q   KI  B   KN  R

1   WP  WP  WP  WP  WP  WP  WP  WP   

2   E   E   E   E   E   E   E   E

3   E   E   E   E   E   E   E   E

4   E   E   E   E   E   E   E   E

5   E   E   E   E   E   E   E   E

6   BP  BP  BP  BP  BP  BP  BP  BP   

7   R   KN  B   Q   KI  B   KN  R
*/

void initiate_game(Board &main_board){
    Peace white_rook;
    Peace white_knight;
    Peace white_bishop;
    Peace white_king;
    Peace white_queen;
    Peace white_pawn;

    white_rook.color = 1;
    white_knight.color = 1;
    white_bishop.color = 1;
    white_king.color = 1;
    white_queen.color = 1;
    white_pawn.color = 1;
    white_rook.is_empty = false;
    white_knight.is_empty = false;
    white_bishop.is_empty = false;
    white_king.is_empty = false;
    white_queen.is_empty = false;
    white_pawn.is_empty = false;
    white_rook.is_rook = true;
    white_knight.is_knight = true;
    white_bishop.is_bishop = true;
    white_king.is_king = true;
    white_queen.is_queen = true;
    white_pawn.is_pawn = true;
    

    Peace black_rook;
    Peace black_knight;
    Peace black_bishop;
    Peace black_king;
    Peace black_queen;
    Peace black_pawn;

    black_rook.color = 2;
    black_knight.color = 2;
    black_bishop.color = 2;
    black_king.color = 2;
    black_queen.color = 2;
    black_pawn.color = 2;
    black_rook.is_empty = false;
    black_knight.is_empty = false;
    black_bishop.is_empty = false;
    black_king.is_empty = false;
    black_queen.is_empty = false;
    black_pawn.is_empty = false;
    black_rook.is_rook = true;
    black_knight.is_knight = true;
    black_bishop.is_bishop = true;
    black_king.is_king = true;
    black_queen.is_queen = true;
    black_pawn.is_pawn = true;

    main_board.board[0][0] = white_rook;
    main_board.board[1][0] = white_knight;
    main_board.board[2][0] = white_bishop;
    main_board.board[3][0] = white_queen;
    main_board.board[4][0] = white_king;
    main_board.board[5][0] = white_bishop;
    main_board.board[6][0] = white_knight;
    main_board.board[7][0] = white_rook;
    main_board.board[0][1] = white_pawn;
    main_board.board[1][1] = white_pawn;
    main_board.board[2][1] = white_pawn;
    main_board.board[3][1] = white_pawn;
    main_board.board[4][1] = white_pawn;
    main_board.board[5][1] = white_pawn;
    main_board.board[6][1] = white_pawn;
    main_board.board[7][1] = white_pawn;
    main_board.board[0][7] = black_rook;
    main_board.board[1][7] = black_knight;
    main_board.board[2][7] = black_bishop;
    main_board.board[3][7] = black_queen;
    main_board.board[4][7] = black_king;
    main_board.board[5][7] = black_bishop;
    main_board.board[6][7] = black_knight;
    main_board.board[7][7] = black_rook;
    main_board.board[0][6] = black_pawn;
    main_board.board[1][6] = black_pawn;
    main_board.board[2][6] = black_pawn;
    main_board.board[3][6] = black_pawn;
    main_board.board[4][6] = black_pawn;
    main_board.board[5][6] = black_pawn;
    main_board.board[6][6] = black_pawn;
    main_board.board[7][6] = black_pawn;
}
