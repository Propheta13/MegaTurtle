#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matrixer.h"

Matrixer::Matrixer()
{
    memset(field, 0, sizeof(field));
//    printf("sizeof = %d \n", sizeof(field));
}

void Matrixer::randomize_matrix(matrix_t matrix, unsigned int len_X, unsigned int len_Y)
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

//    while(count--)
//    {
//        line(matrix, random() % SIZEX, random() % SIZEY, random() % 4, (random() % 10) + 2);
//    }

    do
    {
        do
        {
            x = random();
            x = x % SIZEX;
        }
        while(x>=len_X);

        do
        {
            y=random();
            y = y % SIZEY;
        }
        while(y>=len_Y);

        if (matrix[x][y] == EMPTY)
        {
            matrix[x][y] = BARYER;
            count--;
        }
    }
    while (count);

}


void Matrixer::start_finish_matrix(matrix_t matrix, unsigned int len_X, unsigned int len_Y, int *x_f, int *y_f)
{
    int x, y, i;
    int x_s[2][4];
    int y_s[2][4];
    x_s[0][0] = 0;
    y_s[0][0] = 0;
    x_s[1][0] = len_X / COUNT_QUADR;
    y_s[1][0] = len_Y / COUNT_QUADR;

    x_s[0][1] = 0;
    y_s[0][1] = len_Y - len_Y / COUNT_QUADR;
    x_s[1][1] = len_X / COUNT_QUADR;
    y_s[1][1] = len_Y;

    x_s[0][2] = len_X - len_X / COUNT_QUADR;
    y_s[0][2] = 0;
    x_s[1][2] = len_X;
    y_s[1][2] = len_Y / COUNT_QUADR;


    x_s[0][3] = len_X - len_X / COUNT_QUADR;
    y_s[0][3] = len_Y - len_Y / COUNT_QUADR;
    x_s[1][3] = len_X;
    y_s[1][3] = len_Y;

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
    *x_f = x;
    *y_f = y;

}

int Matrixer::fill_matrix(matrix_t matrix, unsigned int len_X, unsigned int len_Y)
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
        for (x=0; x<len_X; x++)
        {
            for (y=0; y<len_Y; y++)
            {
                if (matrix[x][y] ==  loc)
                {
                    for (k=0; k<(sizeof(dx)/sizeof(int32_t)); k++)
                    {
                        x1=x+dx[k];
                        y1=y+dy[k];
                        if ((x1 < len_X) && (y1 < len_Y))
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

int Matrixer::path_matrix(matrix_t matrix, unsigned int len_X, unsigned int len_Y, unsigned int Fin_X, unsigned int Fin_Y)
{
    unsigned int x = Fin_X, y = Fin_Y, k, x1, y1;
    int mass = matrix[Fin_X][Fin_Y];
//    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
//    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
    int32_t dx[]={0, -1, 1, 0};
    int32_t dy[]={-1, 0, 0, 1};
    //printf("mass = %d\n", mass);
    matrix[Fin_X][Fin_Y] = FINISH;
    do
    {
        mass--;
        for (k=0; k<(sizeof(dx)/sizeof(int32_t)); k++)
        {
            x1=x+dx[k];
            y1=y+dy[k];
            if ((x1 < len_X) && (y1 < len_Y))
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

    for (x=0; x<len_X; x++)
    {
        for (y=0; y<len_Y; y++)
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
    int x_f, y_f;
    srand(time(NULL));

    randomize_matrix(field, SIZEX, SIZEY);
    start_finish_matrix(field, SIZEX, SIZEY, &x_f, &y_f);

    if (fill_matrix (field, SIZEX, SIZEY)) {
    return;
    }

    path_matrix(field, SIZEX, SIZEY, x_f, y_f);
}



