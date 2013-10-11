#ifndef WAVESOLVER_H
#define WAVESOLVER_H

namespace WaveSolver
{
    enum Params
    {
        EMPTY,
        BARYER,
        START,
        FINISH,
        PATH,
        SIZEX = 50,
        SIZEY = 50
    };

    typedef  int (*matrix_t)[SIZEY];
    void Solve(matrix_t matrix);
}

#endif // WAVESOLVER_H
