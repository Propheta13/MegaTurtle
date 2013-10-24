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
#include <QObject>

class Matrixer : public QObject
{
    Q_OBJECT
public:

    Matrixer();

    enum Params
    {
        EMPTY = -1,
        BARYER = -2,
        START = 0,
        FINISH = -3,
        PATH = -4,
        SIZEX = 150,
        SIZEY = 150,
        COUNT_RANDOM = ((SIZEX * SIZEY)/3 + 400),
        COUNT_QUADR = 4,
        RESOLVED = 0,
        STEP_OK = -1,
        NO_PATH = 2
    };
    int32_t field [SIZEX][SIZEY];
    typedef  int (*matrix_t)[SIZEY];
    int x_finish, y_finish;
    int fill_step(matrix_t matrix);

public slots:
    void Solve(void);

private:
    int32_t loc;

    void randomize_matrix(matrix_t matrix);
    void start_finish_matrix(matrix_t matrix);
    void fill_matrix(void);
    int path_matrix(matrix_t matrix);

signals:
    void signalChanged();
};


#endif // MATRIXER_H
