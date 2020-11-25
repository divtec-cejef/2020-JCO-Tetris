#include "tetris.h"

Tetris::Tetris()
{

    // Enumération définissant les valeurs que peuvent avoir
    // les cellules du tableau
    typedef enum {
        SQUARE_YELLOW,
        LINE_CYAN,
        T_PURPLE,
        ZLEFT_RED,
        ZRIGHT_GREEN,
        LRIGHT_BLUE,
        LLEFT_ORANGE,
        TETRIS_NULL
    } TetrisValue;

    // Dimension du tableau
    static const int TB_COLUMNS = 20;
    static const int TB_ROW = 10;

    // Déclaration du tableau
    static TetrisValue tbTetris[TB_COLUMNS][TB_ROW];


}
