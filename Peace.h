// #include <iostream>
// #include "Board.h"
// using namespace std;

// class Peace
// {
// private:
//     bool is_empty = false;
//     bool is_pawn = false;
//     bool is_rook = false;
//     bool is_knight = false;
//     bool is_bishop = false;
//     bool is_king = false;
//     bool is_queen = false;
// public:
//     pair < int , int > position;
//     /*
//         first -  A B C D E F G H
//         second - 1 2 3 4 5 6 7 8
//     */
//     bool check_move_for_pawn(pair < int , int > now_position, pair < int , int > next_position)
//     {
        
//     }
//     bool check_move_for_rook(Board now_board, pair < int , int > now_position, pair < int , int > next_position)
//     {
//         if (now_position.first > next_position.first)
//         {
            
//             return true;
//         }
//         if (now_position.first < next_position.first)
//         {

//             return true;
//         }
//         if (now_position.second > next_position.second)
//         {

//             return true;
//         }
//         if (now_position.second > next_position.second)
//         {

//             return true;
//         }
//         return false;
//     }
//     bool check_move_for_knight(pair < int , int > now_position, pair < int , int > next_position)
//     {
        
//     }
//     bool check_move_for_bishop(pair < int , int > now_position, pair < int , int > next_position)
//     {
        
//     }
//     bool check_move_for_queen(pair < int , int > now_position, pair < int , int > next_position)
//     {
        
//     }
//     bool check_move_for_king(pair < int , int > now_position, pair < int , int > next_position)
//     {
        
//     }
// };