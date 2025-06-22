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

    void make_empty()
    {
        is_empty = true;
        is_pawn = false;
        is_rook = false;
        is_knight = false;
        is_bishop = false;
        is_king = false;
        is_queen = false;
        were_moved = false;

        color = 0; // 1 - white, 2 - black
    }

    void print() const
    {
        if (is_empty) 
        {
            cout << ".";
            return;
        }
        if (color == 1) cout << "W";
        else cout << "B";
        if (is_pawn) cout << "P";
        if (is_knight) cout << "N";
        if (is_bishop) cout << "B";
        if (is_rook) cout << "R";
        if (is_king) cout << "K";
        if (is_queen) cout << "Q";
    }
};