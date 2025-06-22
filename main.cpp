#include <iostream>
#include <vector>
#include "Move.h"

using namespace std;

Board main_board;

int main(){
    initiate_game(main_board);
    backup_boards.push_back(main_board);
    int now_color = 1;
    while (can_move(main_board, now_color) && is_peaces_exc_kings(main_board))
    {
        if (make_move(main_board)) now_color = now_color % 2 + 1;
    }
    if (is_peaces_exc_kings(main_board) == false)
    {
        cout << "Draw!" << endl;
        exit(0);
    }
    if (check_king(main_board, now_color))
    {
        cout << "Stalemate!" << endl;
        exit(0);
    }
    else
    {
        cout << (now_color == 1 ? "Black" : "White") << " wins!" << endl;
        exit(0);
    }
    return 0;
}