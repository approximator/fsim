#include <QPainter>
#include <QtMath>
#include <QDebug>

#include "TPoint.h"

TPoint::TPoint(const uint id, const qreal _x, const qreal _y, QObject *parent):
    QObject(parent),
    m_Id(id),
    m_Position(_x, _y)
{

}

void TPoint::setX(const qreal x)
{
    m_Position.setX(x);
}

void TPoint::setY(const qreal y)
{
    m_Position.setY(y);
}

uint TPoint::id() const
{
    return m_Id;
}

qreal TPoint::x() const
{
    return m_Position.x();
}

qreal TPoint::y() const
{
    return m_Position.y();
}


