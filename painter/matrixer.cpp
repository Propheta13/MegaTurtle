#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matrixer.h"

Matrixer::Matrixer() : QObject()
{
    time_t rawtime;
    time( &rawtime );
    srandom((unsigned int)rawtime);
    memset(field, 0, sizeof(field));
    randomize_matrix(field);
    start_finish_matrix(field);
    loc = 0;
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
    //matrix[x][y] = START;
    matrix[1][1] = START;

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
    matrix[SIZEX-1][SIZEY-1] = FINISH;
    //matrix[x][y] = FINISH;
//    *x_f = x;
//    *y_f = y;
//    x_finish = x;
//    y_finish = y;
    x_finish = SIZEX-1;
    y_finish = SIZEY-1;

    y = 50;
    for(x=0;x<SIZEX-50;x++)
    {
        matrix[x][y] = BARYER;
    }

    y = 100;

    for(x=50;x<SIZEX;x++)
    {
        matrix[x][y] = BARYER;
    }

//    y = 150;
//    for(x=0;x<SIZEX-50;x++)
//    {
//        matrix[x][y] = BARYER;
//    }

//    y = 200;

//    for(x=50;x<SIZEX;x++)
//    {
//        matrix[x][y] = BARYER;
//    }

//    y = 250;
//    for(x=0;x<SIZEX-50;x++)
//    {
//        matrix[x][y] = BARYER;
//    }

//    y = 300;

//    for(x=50;x<SIZEX;x++)
//    {
//        matrix[x][y] = BARYER;
//    }
}

//int Matrixer::fill_matrix(matrix_t matrix)
//{
//    bool flag = false;
//    bool done = false;
//    unsigned int x, y, k;
//    unsigned int x1, y1;
////    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
////    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
//    int32_t dx[]={0, -1, 1, 0};
//    int32_t dy[]={-1, 0, 0, 1};
////    int32_t loc = 0;
//    do
//    {
//        flag = false;
//        for (x=0; x<SIZEX; x++)
//        {
//            for (y=0; y<SIZEY; y++)
//            {
//                if (matrix[x][y] ==  loc)
//                {
//                    for (k=0; k<(sizeof(dx)/sizeof(int32_t)); k++)
//                    {
//                        x1=x+dx[k];
//                        y1=y+dy[k];
//                        if ((x1 < SIZEX) && (y1 < SIZEY))
//                        {
//                            if (matrix[x1][y1] == EMPTY)
//                            {
//                                matrix[x1][y1] = loc + 1;
//                                flag = true;
//                            }
//                            if (matrix[x1][y1] == FINISH)
//                            {
//                                matrix[x1][y1] = loc + 1;
//                                done = true;
//                                break;
//                            }
//                        }
//                    }
//                }
//                if (done) {break;}
//            }
//            if (done) {break;}
//        }
//        loc ++;
//    }
//    while(flag && !done);
//    if (done) {return 0;}
//    return -1;

//}

int Matrixer::fill_step(matrix_t matrix)
{
    bool flag = false;
    bool done = false;
    unsigned int x, y, k;
    unsigned int x1, y1;
//    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
//    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
    int32_t dx[]={0, -1, 1, 0};
    int32_t dy[]={-1, 0, 0, 1};

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

    emit signalChanged();

    if (done) { printf("loc =%d\n", loc);
        return RESOLVED;}
    if (flag) {return STEP_OK;}
    return NO_PATH;

}

void Matrixer::fill_matrix(void)
{
    while (fill_step(field) == STEP_OK);
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

    if (mass < 0) {return 0;}

    while(mass)
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
                    emit signalChanged();
                    break;
                }
            }
        }
    }
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

    emit signalChanged();

    return 0;
}

void Matrixer::Solve(void)
{

    fill_matrix();
    path_matrix(field);
}



