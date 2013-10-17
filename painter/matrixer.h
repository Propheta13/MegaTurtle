#ifndef MATRIXER_H
#define MATRIXER_H
#include <stdint.h>

//enum Params
//{
//    EMPTY = -1,
//    BARYER = -2,
//    START = 0,
//    FINISH = -3,
//    PATH = -4,
//    SIZEX = 100,
//    SIZEY = 100,
//    COUNT_RANDOM = ((SIZEX * SIZEY)/3 + 400),
//    COUNT_QUADR = 4
//};


class Matrixer
{
public:

    Matrixer();

    enum Params
    {
        EMPTY = -1,
        BARYER = -2,
        START = 0,
        FINISH = -3,
        PATH = -4,
        SIZEX = 100,
        SIZEY = 100,
        COUNT_RANDOM = ((SIZEX * SIZEY)/3 + 400),
        COUNT_QUADR = 4
    };
    int32_t field [SIZEX][SIZEY];
    typedef  int (*matrix_t)[SIZEY];
    int x_finish, y_finish;
    void Solve(void);

private:

    void randomize_matrix(matrix_t matrix);
    void start_finish_matrix(matrix_t matrix);
    int fill_matrix(matrix_t matrix);
    int path_matrix(matrix_t matrix);
};


#endif // MATRIXER_H
