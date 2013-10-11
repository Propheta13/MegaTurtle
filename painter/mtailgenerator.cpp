#include "mtailgenerator.h"
#include "mgscene.h"
#include "mdefault.h"
#include "tail.h"

#include <QRgb>
#include <QFile>

MTailGenerator::MTailGenerator(MGScene *scene, QObject *parent) :
    QObject(parent)
{
    m_scene = scene;
    m_tail_resolution = MapGenerator::DefaultTailResolution;
}

void MTailGenerator::setTailResolution(quint32 resolution)
{
    m_tail_resolution = resolution;
}

void MTailGenerator::generate()
{
    quint32 ts = m_tail_resolution;
    int i = 0;

    int matrix[WaveSolver::SIZEX][WaveSolver::SIZEY];
    WaveSolver::matrix_t matrix_p = matrix;

    WaveSolver::Solve(matrix_p);

    m_poly_base.clear();

    for(int x=0; x<WaveSolver::SIZEX; x++)
    {
        int j = 0;
        for(int y=0; y<WaveSolver::SIZEY; y++)
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

            switch(matrix_p[x][y])
            {
            case WaveSolver::EMPTY:
                poly.colour = Qt::white;
                break;
            case WaveSolver::BARYER:
                poly.colour = Qt::black;
                break;
            case WaveSolver::START:
                poly.colour = Qt::yellow;
                break;
            case WaveSolver::FINISH:
                poly.colour = Qt::blue;
                break;
            case WaveSolver::PATH:
                poly.colour = Qt::green;
                break;
            }

            m_poly_base.append(poly);
            j += ts;
        }
        i += ts;
    }
}

void MTailGenerator::draw()
{
    m_scene->clear();
    QVector<MPoly>::iterator it = m_poly_base.begin();
    MPoly *tPoly;

    m_scene->addRect(0,0, m_scene->width(), m_scene->height());

    for(;it != m_poly_base.end(); it++)
    {
        tPoly = (MPoly *)it;
        m_scene->addPolygon(tPoly->poly, QPen(), QBrush(tPoly->colour));
    }
}

void MTailGenerator::save(const QString fname)
{
    if(fname.isEmpty())
        return;

    Tail::tailmap_header_t header;
    QFile ofd(fname);
    ofd.open(QFile::WriteOnly);

    /* Header:
     * uint32_t tail_count
     * uint32_t map_resolution_h
     * uint32_t map_resolution_w
     * uint32_t tail_resolution
     * tail_t tail_list[tail_count]
     */

    header.map_resolution_h = m_hmap->height();
    header.map_resolution_w = m_hmap->width();
    header.tail_resolution = m_tail_resolution;
    header.tail_h = header.map_resolution_h/header.tail_resolution;
    header.tail_w = header.map_resolution_w/header.tail_resolution;
    header.tail_count = (header.map_resolution_h*header.map_resolution_w)/header.tail_resolution;

    ofd.write((const char*)&header, sizeof(header));

    QVector<MPoly>::iterator it = m_poly_base.begin();
    MPoly *tPoly;

    for(;it != m_poly_base.end(); it++)
    {
        tPoly = (MPoly *)it;
        ofd.write((const char*)&(tPoly->tail), sizeof(Tail::tail_t));
    }

    ofd.close();
}
