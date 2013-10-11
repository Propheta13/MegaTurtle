#include "wavesolver.h"

void WaveSolver::Solve(matrix_t matrix)
{
    for(int x=0; x<SIZEX; x++)
    {
        for(int y=0; y<SIZEY; y++)
        {
            matrix[x][y] = EMPTY;
            if(x == y)
            {
                matrix[x][y] = BARYER;
            }
        }
    }
}

