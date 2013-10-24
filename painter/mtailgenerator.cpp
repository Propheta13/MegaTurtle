#include "mtailgenerator.h"
#include "mgscene.h"
#include "mdefault.h"
#include "tail.h"
#include "matrixer.h"

#include <QRgb>
#include <QFile>
#include <stdio.h>
#include <QThread>

MTailGenerator::MTailGenerator(MGScene *scene, QObject *parent) :
    QObject(parent)
{
    m_scene = scene;
    m_tail_resolution = MapGenerator::DefaultTailResolution;
    quint32 ts = m_tail_resolution;
    dx = 255;

    int i = 0;

    for(int x=0; x<Matrixer::SIZEX; x++)
    {
        int j = 0;
        for(int y=0; y<Matrixer::SIZEY; y++)
        {
            QVector<QPointF> poly_vector;
            MPoly poly;

            poly.tail.attributes = 0;
            poly.tail.type = Tail::RawStone;
            poly_vector.append(QPointF(i,j));
            poly_vector.append(QPointF(i,j+ts));
            poly_vector.append(QPointF(i+ts,j+ts));
            poly_vector.append(QPointF(i+ts,j));
            poly.poly = QPolygonF(poly_vector);
            poly.colour = Qt::white;
            poly.gi = m_scene->addPolygon(poly.poly, QPen(), QBrush(poly.colour));
            poly.needs_colour_update = false;
            m_poly_base[key(x,y)] = poly;
            j += ts;
        }
        i += ts;
    }

    m_scene->addRect(0,0, m_scene->width(), m_scene->height());
}

void MTailGenerator::setTailResolution(quint32 resolution)
{
    m_tail_resolution = resolution;
}

int MTailGenerator::generate()
{
    int res = 0;

    Matrixer::matrix_t matrix_p = matrix_d->field;

    m_update_queue.clear();
    for(int x=0; x<Matrixer::SIZEX; x++)
    {
        for(int y=0; y<Matrixer::SIZEY; y++)
        {
            MPoly *poly;
            QColor cl;
            poly = &m_poly_base[key(x,y)];

            switch(matrix_p[x][y])
            {
            case Matrixer::EMPTY:
                cl = Qt::white;
                break;
            case Matrixer::BARYER:
                cl = Qt::gray;
                break;
            case Matrixer::START:
                cl = Qt::yellow;
                break;
            case Matrixer::FINISH:
                cl = Qt::blue;
                break;
            case Matrixer::PATH:
                cl = Qt::yellow;//qRgb(255 - poly->colour.red(), 0, 255 - poly->colour.blue());
                break;
            default :
                if(matrix_p[x][y]/256%2 == 0)
                    cl = qRgb(matrix_p[x][y], 0, 255 - matrix_p[x][y]);
                else
                    cl = qRgb(255 - matrix_p[x][y], 0, matrix_p[x][y]);
                break;
            }

            if(cl != poly->colour)
            {
                poly->colour = cl;
                poly->needs_colour_update = true;
                m_update_queue.append(key(x,y));
            }
        }
    }
    return res;
}

void MTailGenerator::draw()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    QVector<int>::iterator it = m_update_queue.begin();

    for(;it != m_update_queue.end(); it++)
    {
        MPoly *tPoly;
        tPoly = &m_poly_base[(int)*it];
        if(tPoly->needs_colour_update)
        {
            brush.setColor(tPoly->colour);
            tPoly->gi->setBrush(brush);
            tPoly->needs_colour_update = false;
        }
    }
}

void MTailGenerator::solve()
{
    QThread *workerThread = new QThread(this);

    connect(workerThread, &QThread::started, matrix_d, &Matrixer::Solve);
    matrix_d->moveToThread(workerThread);

    // Starts an event loop, and emits workerThread->started()
    workerThread->start();
}

void MTailGenerator::slotUpdate()
{
    generate();
    draw();
}

void MTailGenerator::save(const QString fname)
{
//    if(fname.isEmpty())
//        return;

//    Tail::tailmap_header_t header;
//    QFile ofd(fname);
//    ofd.open(QFile::WriteOnly);

//    /* Header:
//     * uint32_t tail_count
//     * uint32_t map_resolution_h
//     * uint32_t map_resolution_w
//     * uint32_t tail_resolution
//     * tail_t tail_list[tail_count]
//     */

//    header.map_resolution_h = m_hmap->height();
//    header.map_resolution_w = m_hmap->width();
//    header.tail_resolution = m_tail_resolution;
//    header.tail_h = header.map_resolution_h/header.tail_resolution;
//    header.tail_w = header.map_resolution_w/header.tail_resolution;
//    header.tail_count = (header.map_resolution_h*header.map_resolution_w)/header.tail_resolution;

//    ofd.write((const char*)&header, sizeof(header));

//    QVector<MPoly>::iterator it = m_poly_base.begin();
//    MPoly *tPoly;

//    for(;it != m_poly_base.end(); it++)
//    {
//        tPoly = (MPoly *)it;
//        ofd.write((const char*)&(tPoly->tail), sizeof(Tail::tail_t));
//    }

//    ofd.close();
}
