#ifndef WAVESOLVER_H
#define WAVESOLVER_H

namespace WaveSolver
{
    enum Params
    {
        EMPTY = -1,
        BARYER = -2,
        START = 0,
        FINISH = -3,
        PATH = -4,
        SIZEX = 50,
        SIZEY = 50,
        COUNT_RANDOM = ((SIZEX * SIZEY)/3),
        COUNT_QUADR = 4
    };

    typedef  int (*matrix_t)[SIZEY];
    void Solve(matrix_t matrix);
}

#endif // WAVESOLVER_H
