#include <iostream>
#include <vector>
// #include "Peace.h"
// #include "Board.h"

using namespace std;

class Board {};
class Peace {};

struct Move
{
    Peace & peace;
    pair < int , int > now_position;
    pair < int , int > next_position;
};

vector<Board> backup_boards;
vector<Move> move_backups;

void check_king(Board now_board, Peace king) {};

class Peace
{
private:
    bool is_empty = false;
    bool is_pawn = false;
    bool is_rook = false;
    bool is_knight = false;
    bool is_bishop = false;
    bool is_king = false;
    bool is_queen = false;
    bool were_moved = false;

    int color = 0;
    // 0 - empty, 1 - white, 2 - black
public:
    pair < int , int > position;
    /*
        first -  A B C D E F G H
        second - 1 2 3 4 5 6 7 8
    */
    bool check_move_for_pawn(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
    {
        if (now_board.board[now_position.first][now_position.second].color == 
            now_board.board[next_position.first][next_position.second].color)
            return false;
        if (now_board.board[now_position.first][now_position.second].color == 1)
        {
            if (abs(next_position.first - now_position.first) > 1 or next_position.second - now_position.second > 2) 
                return false;
            if (next_position.first == now_position.first)
            {
                if (now_board.board[next_position.first][next_position.second].is_empty) 
                {
                    if (next_position.second - now_position.second == 1)
                        return true;
                    if (next_position.second - now_position.second == 2)
                    {
                        if (now_board.board[now_position.first][now_position.second].were_moved == false && now_board.board[next_position.first][next_position.second - 1].is_empty)
                            return true;
                        return false;
                    }
                    return false;
                }
                return false;
            }
            if (abs(now_position.first - next_position.first) == 1)
            {
                if (next_position.second - now_position.second == 2)
                    return false;
                if (now_board.board[next_position.first][next_position.second].color == 2)
                    return true;
                if (now_board.board[next_position.first][next_position.second].is_empty){
                    Peace pe = now_board.board[now_position.first][next_position.second];
                    if (pe.is_pawn && pe.color == 2 && (&move_backups.back().peace == &pe))
                    {
                        if (move_backups.back().now_position.first == move_backups.back().next_position.first &&
                            move_backups.back().now_position.second == move_backups.back().next_position.second + 2)
                            return true;
                        return false;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        if (now_board.board[now_position.first][now_position.second].color == 2)
        {
            if (abs(now_position.first - next_position.first) > 1 or now_position.second - next_position.second > 2) 
                return false;
            if (next_position.first == now_position.first)
            {
                if (now_board.board[next_position.first][next_position.second].is_empty) 
                {
                    if (now_position.second - next_position.second == 1)
                        return true;
                    if (now_position.second - next_position.second == 2)
                    {
                        if (now_board.board[now_position.first][now_position.second].were_moved == false && now_board.board[next_position.first][next_position.second + 1].is_empty)
                            return true;
                        return false;
                    }
                    return false;
                }
                return false;
            }
            if (abs(now_position.first - next_position.first) == 1)
            {
                if (now_position.second - next_position.second == 2)
                    return false;
                if (now_board.board[next_position.first][next_position.second].color == 1)
                    return true;
                if (now_board.board[next_position.first][next_position.second].is_empty){
                    Peace pe = now_board.board[now_position.first][next_position.second];
                    if (pe.is_pawn && pe.color == 1 && (&move_backups.back().peace == &pe))
                    {
                        if (move_backups.back().now_position.first == move_backups.back().next_position.first &&
                            move_backups.back().now_position.second == move_backups.back().next_position.second - 2)
                            return true;
                        return false;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }

    bool check_move_for_rook(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
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
    }

    bool check_move_for_knight(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
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

    bool check_move_for_bishop(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
    {
        if (now_board.board[now_position.first][now_position.second].color == 
            now_board.board[next_position.first][next_position.second].color)
            return false;
        
    }

    bool check_move_for_queen(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
    {
        if (now_board.board[now_position.first][now_position.second].color == 
            now_board.board[next_position.first][next_position.second].color)
            return false;
        
    }

    bool check_move_for_king(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
    {
        if (now_board.board[now_position.first][now_position.second].color == 
            now_board.board[next_position.first][next_position.second].color)
            return false;
        
    }
};

class Board
{
public:
    Peace board[8][8];
};

bool check_if_move_is_right(Board board, string position, string next_position)
{

}

void make_move(){
    cout << "Make a move: ";
    string get_move;
    getline(cin, get_move);
    if (get_move == "takeback") 
    {
        if (backup_boards.size() == 1)
        {
            cout << "You can't takeback to starting possition" << endl;
            return;
        }
        backup_boards.pop_back();
        cout << "Takeback was successful!" << endl;
        return;
    }
    if (get_move.size() != 5)
    {
        cout << "Wrong move format!" << endl;
        return;
    }
    if (get_move[0] > 'H' or get_move[0] < 'A')
    {
        cout << "Wrong move format!" << endl;
        return;
    }
    if (get_move[1] > '8' or get_move[1] < '1')
    {
        cout << "Wrong move format!" << endl;
        return;
    }
    if (get_move[2] != ' ')
    {
        cout << "Wrong move format!" << endl;
        return;
    }
    if (get_move[3] > 'H' or get_move[3] < 'A')
    {
        cout << "Wrong move format!" << endl;
        return;
    }
    if (get_move[4] > '8' or get_move[4] < '1')
    {
        cout << "Wrong move format!" << endl;
        return;
    }

}

int main(){
    
    return 0;
}