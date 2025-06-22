#include <iostream>
#include <functional>
#include <vector>
#include "Peace.h"
#include "Board.h"

using namespace std;

struct Move
{
    Peace peace;
    pair < int , int > now_position;
    pair < int , int > next_position;
};

vector<Board> backup_boards;
vector<Move> move_backups;

bool check_move_for_pawn(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    int add = (now_board.board[now_position.first][now_position.second].color - 1 ? -1 : 1); // color 0 - white, 1 - black
    if ((abs(next_position.first - now_position.first) > 1) or (abs(next_position.second - now_position.second) > 2)) 
        return false;
    if (next_position.first == now_position.first)
    {
        if (now_board.board[next_position.first][next_position.second].is_empty) 
        {
            if (next_position.second - now_position.second == 1 * add)
                return true;
            if (next_position.second - now_position.second == 2 * add)
            {
                if (now_board.board[now_position.first][now_position.second].were_moved == false && now_board.board[next_position.first][next_position.second - 1 * add].is_empty)
                    return true;
                return false;
            }
            return false;
        }
        return false;
    }
    if (abs(now_position.first - next_position.first) == 1)
    {
        if (next_position.second - now_position.second == 2 * add)
            return false;
        if (now_board.board[next_position.first][next_position.second].color != now_board.board[now_position.first][now_position.second].color)
            return true;
        if (now_board.board[next_position.first][next_position.second].is_empty){
            Peace pe = now_board.board[next_position.first][next_position.second - 1 * add];
            if (pe.is_pawn && pe.color != now_board.board[now_position.first][now_position.second].color && (&move_backups.back().peace == &pe))
            {
                if (move_backups.back().now_position.first == move_backups.back().next_position.first &&
                    move_backups.back().now_position.second == move_backups.back().next_position.second + 2 * add)
                    return true;
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool check_move_for_rook(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    if (now_position.first != next_position.first &&
        now_position.second != next_position.second)
        return false;
    if (now_position.first > next_position.first)
    {
        for (int i = now_position.first + 1; i < next_position.first; ++i)
        {
            if (now_board.board[i][now_position.first].is_empty == false)
            {
                return false;
            }
        }
        return true;
    }
    if (now_position.first < next_position.first)
    {
        for (int i = next_position.first + 1; i < now_position.first; ++i)
        {
            if (now_board.board[i][now_position.first].is_empty == false)
            {
                return false;
            }
        }
        return true;
    }
    if (now_position.second > next_position.second)
    {
        for (int i = now_position.second + 1; i < next_position.second; ++i)
        {
            if (now_board.board[now_position.second][i].is_empty == false)
            {
                return false;
            }
        }
        return true;
    }
    if (now_position.second > next_position.second)
    {
        for (int i = next_position.second + 1; i < now_position.second; ++i)
        {
            if (now_board.board[now_position.second][i].is_empty == false)
            {
                return false;
            }
        }
        return true;
    }
    return true;
}

bool check_move_for_knight(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    int difference_betw_first_coords = abs(now_position.first - next_position.first);
    int difference_betw_second_coords = abs(now_position.second - next_position.second);
    if ((difference_betw_first_coords == 1 and difference_betw_second_coords == 2) or
        (difference_betw_first_coords == 2 and difference_betw_second_coords == 1)){
            return true;
        }
    return false;
}

bool check_move_for_bishop(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    if (abs(now_position.first - next_position.first) != abs(now_position.second - next_position.second)) 
        return false;
    int delta_x = (next_position.first > now_position.first ? 1 : -1);
    int delta_y = (next_position.second > now_position.second ? 1 : -1);
    for (int _=1; _<abs(next_position.first - now_position.first); ++_)
        if (now_board.board[now_position.first + delta_x * _][now_position.second + delta_y * _].is_empty == false)
            return false;
    return true;
}

bool check_move_for_queen(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    if (now_position.first == next_position.first || now_position.second == next_position.second) 
        return check_move_for_rook(now_board, now_position, next_position);
    return check_move_for_bishop(now_board, now_position, next_position);
}

bool check_move_for_king(const Board &now_board, const pair < int , int > &now_position, const pair < int , int > &next_position)
{
    if (now_board.board[now_position.first][now_position.second].color == 
        now_board.board[next_position.first][next_position.second].color)
        return false;
    if (abs(now_position.first - next_position.first) > 1 || 
        abs(now_position.second - next_position.second) > 1)
        return false;
    return true;
}

bool check_king(Board now_board, int color) { // false - under attack, true - safe
    pair<int , int> king_position;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (now_board.board[i][j].is_king && now_board.board[i][j].color == color)
                king_position = {i, j};

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++ j)
        {
            if (i != king_position.first && j != king_position.second)
            {
                if (now_board.board[i][j].is_empty || now_board.board[i][j].color == color) continue;
                if (now_board.board[i][j].is_pawn && check_move_for_pawn(now_board, {i, j}, king_position)) return false;
                if (now_board.board[i][j].is_king && check_move_for_king(now_board, {i, j}, king_position)) return false;
                if (now_board.board[i][j].is_queen && check_move_for_queen(now_board, {i, j}, king_position)) return false;
                if (now_board.board[i][j].is_bishop && check_move_for_bishop(now_board, {i, j}, king_position)) return false;
                if (now_board.board[i][j].is_rook && check_move_for_rook(now_board, {i, j}, king_position)) return false;
                if (now_board.board[i][j].is_knight && check_move_for_knight(now_board, {i, j}, king_position)) return false;
            }
        }
    }
    return true;
};

bool check_if_move_is_right(const Board &board, const pair<int , int> &now_pos, const pair<int , int> &next_pos)
{
    if (now_pos == next_pos)
        return false;
    if ((board.board[now_pos.first][now_pos.second].is_empty == true) ||
        (board.board[next_pos.first][next_pos.second].is_empty == false)) 
        return false;
    auto chm = [&](const function<bool(Board, pair<int,int>, pair<int,int>)>& check){
        if (check(board, now_pos, next_pos) == false) return false;
        Board board_copy = board;
        Peace pe = board_copy.board[now_pos.first][now_pos.second];
        board_copy.board[now_pos.first][now_pos.second] = Peace{};
        pe.were_moved = true;
        board_copy.board[next_pos.first][next_pos.second] = pe;
        if (check_king(board, pe.color) == false) return false;
        return true;
    };
    if (board.board[now_pos.first][now_pos.second].is_pawn) return chm(check_move_for_pawn);
    else if (board.board[now_pos.first][now_pos.second].is_rook) return chm(check_move_for_rook);
    else if (board.board[now_pos.first][now_pos.second].is_king) return chm(check_move_for_king);
    else if (board.board[now_pos.first][now_pos.second].is_queen) return chm(check_move_for_queen);
    else if (board.board[now_pos.first][now_pos.second].is_knight) return chm(check_move_for_knight);
    else return chm(check_move_for_bishop);
}

bool make_move(Board &main_board){
    cout << "Make a move: ";
    string get_move;
    getline(cin, get_move);
    if (get_move == "takeback") 
    {
        if (backup_boards.size() == 1)
        {
            cout << "You can't takeback to starting possition" << endl;
            return false;
        }
        backup_boards.pop_back();
        move_backups.pop_back();
        main_board = backup_boards.back();
        cout << "Takeback was successful!" << endl;
        return true;
    }
    if (get_move.size() != 5)
    {
        cout << "Wrong move format!" << endl;
        return false;
    }
    if (get_move[0] > 'H' or get_move[0] < 'A')
    {
        cout << "Wrong move format!" << endl;
        return false;
    }
    if (get_move[1] > '8' or get_move[1] < '1')
    {
        cout << "Wrong move format!" << endl;
        return false;
    }
    if (get_move[2] != ' ')
    {
        cout << "Wrong move format!" << endl;
        return false;
    }
    if (get_move[3] > 'H' or get_move[3] < 'A')
    {
        cout << "Wrong move format!" << endl;
        return false;
    }
    if (get_move[4] > '8' or get_move[4] < '1')
    {
        cout << "Wrong move format!" << endl;
        return false;
    }

    string position = get_move.substr(0, 2);
    string next_position = get_move.substr(3, 5);

    pair<int , int> now_pos;
    pair<int , int> next_pos;
    
    now_pos.first = position[0] - 'A';
    now_pos.second = position[1] - '1';
    next_pos.first = next_position[0] - 'A';
    next_pos.second = next_position[1] - '1';

    if (check_if_move_is_right(main_board, now_pos, next_pos))
    {
        cout << "Move is done!" << endl;
        Peace pe = main_board.board[now_pos.first][now_pos.second];
        move_backups.push_back({pe, now_pos, next_pos});
        main_board.board[now_pos.first][now_pos.second] = Peace{};
        pe.were_moved = true;
        main_board.board[next_pos.first][next_pos.second] = pe;
        backup_boards.push_back(main_board);
        return true;
    }
    else
    {
        cout << "Move is wrong!" << endl;
        return false;
    }
}

bool can_move(const Board &main_board, const int& color)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (main_board.board[i][j].color == color && main_board.board[i][j].is_empty == false)
            {
                for (int x = 0; x < 8; ++x)
                {
                    for (int y = 0; y < 8; ++y)
                    {
                        pair<int, int> now_pos;
                        pair<int, int> next_pos;

                        now_pos.first = i;
                        now_pos.second = j;

                        next_pos.first = x;
                        next_pos.second = y;

                        auto chm = [&](const function<bool(const Board&, const pair<int , int>&, const pair<int , int>&)> &check){
                            if (check(main_board, now_pos, next_pos) == false) return false;
                            Board board_copy = main_board;
                            Peace pe = board_copy.board[now_pos.first][now_pos.second];
                            board_copy.board[now_pos.first][now_pos.second] = Peace{};
                            pe.were_moved = true;
                            board_copy.board[next_pos.first][next_pos.second] = pe;
                            if (check_king(main_board, pe.color) == false) return false;
                            return true;
                        };
                        if (main_board.board[i][j].is_pawn) if (chm(check_move_for_pawn)) return true;
                        if (main_board.board[i][j].is_rook) if (chm(check_move_for_rook)) return true;
                        if (main_board.board[i][j].is_king) if (chm(check_move_for_king)) return true;
                        if (main_board.board[i][j].is_queen) if (chm(check_move_for_queen)) return true;
                        if (main_board.board[i][j].is_knight) if (chm(check_move_for_knight)) return true;
                        if (main_board.board[i][j].is_bishop) if (chm(check_move_for_bishop)) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool is_peaces_exc_kings(const Board& board)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board.board[i][j].is_empty == false && board.board[i][j].is_king == false)
            {
                return true;
            }
        }
    }
    return false;
}
