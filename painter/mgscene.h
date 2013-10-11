#ifndef MGLWIDGET_H
#define MGLWIDGET_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>

class MGScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MGScene(QString stext, QObject * parent = 0);
    void setBackground(QPixmap *background);

private:
    QGraphicsTextItem *m_stext;
};

#endif // MGLWIDGET_H
