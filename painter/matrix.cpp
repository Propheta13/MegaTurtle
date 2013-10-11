#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZEX 20
#define SIZEY 40
#define COUNT_RANDOM ((SIZEX * SIZEY)/3)
#define COUNT_QUADR 4
#define EMPTY -1
#define BARYER -2
#define START 0
#define FINISH -3
#define PATH -4

void print_matrix (int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y)
{
    int x=0, y=0;
    for (y=0; y<len_Y+2; y++)
    {
        printf("%c", '#');
    }
    printf("\n");
    for (x=0; x<len_X; x++)
    {
        printf("%c", '#');
        for (y=0; y<len_Y; y++)
        {
            if (matrix[x][y] == EMPTY) printf("%c", ' ');
            if (matrix[x][y] == BARYER) printf("%c", '#');
            if (matrix[x][y] == START) printf("%c", 'S');
            if (matrix[x][y] == FINISH) printf("%c", 'F');
            if (matrix[x][y] == PATH) printf("%c", '+');

        }
        printf("%c", '#');
        printf("\n");
    }
    for (y=0; y<len_Y+2; y++)
    {
        printf("%c", '#');
    }
    printf("\n");
}
void print_matrix_d (int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y)
{
    int x=0, y=0;
    for (x=0; x<len_X*2+3; x++)
    {
        printf("%c", '#');
    }
    printf("\n");
    for (x=0; x<len_X; x++)
    {
        printf("%c ", '#');
        for (y=0; y<len_Y; y++)
        {
            if (matrix[x][y] == EMPTY) {printf("%c ", '0'); continue;}
            if (matrix[x][y] == BARYER){ printf("%c ", '#'); continue;}
            if (matrix[x][y] == START) {printf("%c ", 'S'); continue;}
            if (matrix[x][y] == FINISH){ printf("%c ", 'F'); continue;}
            if (matrix[x][y] == PATH) {printf("%c ", '+'); continue;}
            printf("%d ", matrix[x][y]);
        }
        printf("%c ", '#');
        printf("\n");
    }
    for (x=0; x<len_X*2+3; x++)
    {
        printf("%c", '#');
    }
    printf("\n");
}

int path_matrix(int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y, uint32_t Fin_X, uint32_t Fin_Y)
{
    uint32_t x = Fin_X, y = Fin_Y, k, x1, y1;
    uint32_t mass = matrix[Fin_X][Fin_Y];
//    int32_t dx[]={0, -1, -1, 1, 0, 1, -1,  1, 1 };
//    int32_t dy[]={-1, 0, -1, 0, 1, 1,  1, -1, 1 };
    int32_t dx[]={0, -1, 1, 0};
    int32_t dy[]={-1, 0, 0, 1};
    printf("mass = %d\n", mass);
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
}

int fill_matrix(int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y)
{
    bool flag = false;
    bool done = false;
    uint32_t x, y, k;
    uint32_t x1, y1;
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

void randomize_matrix(int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y)
{
    uint32_t count = COUNT_RANDOM;
    uint32_t x, y;


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
            x &= 0xFF;
        }
        while(x>=len_X);

        do
        {
            y=random();
            y &= 0xFF;
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


void start_finish_matrix(int32_t (*matrix)[SIZEY], uint32_t len_X, uint32_t len_Y, int *x_f, int *y_f)
{
    int x, y, i;
    uint32_t x_s[2][4];
    uint32_t y_s[2][4];
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

//int main(int argc, char *argv[])
//{
//    int32_t data[SIZEX][SIZEY];
//    int x, y;
//    int x_f, y_f;
//    time_t rawtime;
//    struct tm * timeinfo;
//    time( &rawtime );
//    timeinfo = localtime ( &rawtime );
//    srandom((unsigned int)rawtime);


////    for (x=0; x < SIZEX; x++)
////    {
////        for (y=0; y < SIZEY; y++)
////        {
////            if ((3 & random()) == 1) data[x][y] = BARYER;
////            else data[x][y] = EMPTY;
////        }
////    }

//    randomize_matrix(data, SIZEX, SIZEY);
//    start_finish_matrix(data, SIZEX, SIZEY, &x_f, &y_f);

//    //find finish


////    print_matrix(data, SIZEX, SIZEY);
//    printf("\n");
//    sleep(1);
//    if (fill_matrix (data, SIZEX, SIZEY)) {
//        printf("bad matrix\n");
//    return 0;
//    }

////    print_matrix_d(data, SIZEX, SIZEY);

//    path_matrix(data, SIZEX, SIZEY, x_f, y_f);
//    print_matrix(data, SIZEX, SIZEY);



//    return 0;
//}

