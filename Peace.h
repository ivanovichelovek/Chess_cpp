#include <iostream>

using namespace std;

class Peace
{
public:
    bool is_empty = false;
    bool is_pawn = false;
    bool is_rook = false;
    bool is_knight = false;
    bool is_bishop = false;
    bool is_king = false;
    bool is_queen = false;
    bool were_moved = false;

    int color; // 1 - white, 2 - black
    Peace () {is_empty = true;};
};