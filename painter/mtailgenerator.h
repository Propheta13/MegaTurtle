#ifndef MTAILGENERATOR_H
#define MTAILGENERATOR_H

#include <QObject>
#include <QPolygonF>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QMap>

#include "tail.h"
#include "matrixer.h"

class MGScene;

class MTailGenerator : public QObject
{
    Q_OBJECT
public:
    explicit MTailGenerator(MGScene *scene = 0, QObject *parent = 0);

    void setTailResolution(quint32 resolution);
    int generate();
    void solve();
    void draw();
    void save(const QString fname);
    Matrixer *matrix_d;

private:
    MGScene *m_scene;
    QImage  *m_hmap;
    quint32  m_tail_resolution;
    typedef struct
    {
        QPolygonF poly;
        Tail::tail_t tail;
        QColor colour;
        bool needs_colour_update;
        QGraphicsPolygonItem *gi;
    } MPoly;
    int dx;
    QMap<int, MPoly> m_poly_base;
    QVector<int> m_update_queue;
    int key(int x, int y){return (x ^ (y<<0x10));}

public slots:
    void slotUpdate();
};

#endif // MTAILGENERATOR_H
