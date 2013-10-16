#ifndef MTAILGENERATOR_H
#define MTAILGENERATOR_H

#include <QObject>
#include <QPolygonF>
#include <QColor>

#include "tail.h"
#include "matrixer.h"

class MGScene;

class MTailGenerator : public QObject
{
    Q_OBJECT
public:
    explicit MTailGenerator(MGScene *scene = 0, QObject *parent = 0);

    void setTailResolution(quint32 resolution);
    void generate();
    void draw();
    void save(const QString fname);

private:
    MGScene *m_scene;
    QImage  *m_hmap;
    quint32  m_tail_resolution;
    Matrixer::matrix_t m_matrix;

    typedef struct
    {
        QPolygonF poly;
        Tail::tail_t tail;
        QColor colour;
    } MPoly;

    QVector<MPoly> m_poly_base;
};

#endif // MTAILGENERATOR_H
