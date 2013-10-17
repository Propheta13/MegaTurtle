#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matrixer.h"

Matrixer::Matrixer()
{
    time_t rawtime;
    time( &rawtime );
    srandom((unsigned int)rawtime);
    memset(field, 0, sizeof(field));
    randomize_matrix(field);
    start_finish_matrix(field);
}

void Matrixer::randomize_matrix(matrix_t matrix)
{
    unsigned int count = COUNT_RANDOM;
    unsigned int x, y;

    for (x=0; x < SIZEX; x++)
    {
        for (y=0; y < SIZEY; y++)
        {
            matrix[x][y] = EMPTY;
        }
    }

    do
    {
        do
        {
            x = random();
            x = x % SIZEX;
        }
        while(x>=SIZEX);

        do
        {
            y=random();
            y = y % SIZEY;
        }
        while(y>=SIZEY);

        if (matrix[x][y] == EMPTY)
        {
            matrix[x][y] = BARYER;
            count--;
        }
    }
    while (count);

}


void Matrixer::start_finish_matrix(matrix_t matrix)
{
    int x, y, i;
    int x_s[2][4];
    int y_s[2][4];
    x_s[0][0] = 0;
    y_s[0][0] = 0;
    x_s[1][0] = SIZEX / COUNT_QUADR;
    y_s[1][0] = SIZEY / COUNT_QUADR;

    x_s[0][1] = 0;
    y_s[0][1] = SIZEY - SIZEY / COUNT_QUADR;
    x_s[1][1] = SIZEX / COUNT_QUADR;
    y_s[1][1] = SIZEY;

    x_s[0][2] = SIZEX - SIZEX / COUNT_QUADR;
    y_s[0][2] = 0;
    x_s[1][2] = SIZEX;
    y_s[1][2] = SIZEY / COUNT_QUADR;


    x_s[0][3] = SIZEX - SIZEX / COUNT_QUADR;
    y_s[0][3] = SIZEY - SIZEY / COUNT_QUADR;
    x_s[1][3] = SIZEX;
    y_s[1][3] = SIZEY;

    //find start
    i=0;
    do
    {
        x = random();
        x &= 0xFFF;
    }
    while(!((x > x_s[0][i]) && (x < x_s[1][i])));
    do
    {
        y = random();
        y &= 0xFFF;
    }
    while(!((y > y_s[0][i]) && (y < y_s[1][i])));
    matrix[x][y] = START;

    i=3;
    do
    {
        do
        {
            x = random();
            x &= 0xFFF;
        }
        while(!((x > x_s[0][i]) && (x < x_s[1][i])));
        do
        {
            y = random();
            y &= 0xFFF;
        }
        while(!((y > y_s[0][i]) && (y < y_s[1][i])));
    }
    while(matrix[x][y] == START);
    matrix[x][y] = FINISH;
//    *x_f = x;
//    *y_f = y;
    x_finish = x;
    y_finish = y;

}

int Matrixer::fill_matrix(matrix_t matrix)
{
    bool flag = false;
    bool done = false;
    unsigned int x, y, k;
    unsigned int x1, y1;
//    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
//    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
    int32_t dx[]={0, -1, 1, 0};
    int32_t dy[]={-1, 0, 0, 1};
    int32_t loc = 0;
    do
    {
        flag = false;
        for (x=0; x<SIZEX; x++)
        {
            for (y=0; y<SIZEY; y++)
            {
                if (matrix[x][y] ==  loc)
                {
                    for (k=0; k<(sizeof(dx)/sizeof(int32_t)); k++)
                    {
                        x1=x+dx[k];
                        y1=y+dy[k];
                        if ((x1 < SIZEX) && (y1 < SIZEY))
                        {
                            if (matrix[x1][y1] == EMPTY)
                            {
                                matrix[x1][y1] = loc + 1;
                                flag = true;
                            }
                            if (matrix[x1][y1] == FINISH)
                            {
                                matrix[x1][y1] = loc + 1;
                                done = true;
                                break;
                            }
                        }
                    }
                }
                if (done) {break;}
            }
            if (done) {break;}
        }
        loc ++;
    }
    while(flag && !done);
    if (done) {return 0;}
    return -1;

}

int Matrixer::path_matrix(matrix_t matrix)
{
    unsigned int x = x_finish, y = y_finish, k, x1, y1;
    int mass = matrix[x_finish][y_finish];
//    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
//    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
    int32_t dx[]={0, -1, 1, 0};
    int32_t dy[]={-1, 0, 0, 1};
    //printf("mass = %d\n", mass);
    matrix[x_finish][y_finish] = FINISH;
    do
    {
        mass--;
        for (k=0; k<(sizeof(dx)/sizeof(int32_t)); k++)
        {
            x1=x+dx[k];
            y1=y+dy[k];
            if ((x1 < SIZEX) && (y1 < SIZEY))
            {
                if (matrix[x1][y1] == mass)
                {
                    matrix[x1][y1] = PATH;
                    x=x1;
                    y=y1;
                    break;
                }
            }
        }
    }
    while(mass);
    matrix[x][y] = START;

    for (x=0; x<SIZEX; x++)
    {
        for (y=0; y<SIZEY; y++)
        {
            if ((matrix[x][y] != START) &&
                    (matrix[x][y] != BARYER) &&
                    (matrix[x][y] != FINISH) &&
                    (matrix[x][y] != PATH) )
            {
                matrix[x][y] = EMPTY;
            }
        }
    }

    return 0;
}

void Matrixer::Solve(void)
{

    if (fill_matrix (field)) {
    return;
    }

    path_matrix(field);
}



