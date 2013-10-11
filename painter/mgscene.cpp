#include <QPainter>
#include <QPixmap>
#include <QGraphicsTextItem>

#include "mgscene.h"

MGScene::MGScene(QString stext, QObject *parent) : QGraphicsScene(parent) {
    m_stext = addText(stext);
}

void MGScene::setBackground(QPixmap *background)
{
    removeItem(m_stext);
    addPixmap(*background);
}
