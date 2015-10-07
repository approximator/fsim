/*!
 * @file TPoint.cpp
 *
 * @brief TPoint represents a point with it's own mass
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 07, 2015
 */

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
    // qDebug() << id() << "  x = " << x;
}

void TPoint::setY(const qreal y)
{
    m_Position.setY(y);
    // qDebug() << id() << "  y = " << y;
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

qreal TPoint::mass() const
{
    return m_Mass;
}

bool TPoint::fixed() const
{
    return m_Fixed;
}

bool TPoint::isObstacle() const
{
    return m_IsObstacle;
}

QVector2D TPoint::force() const
{
    return m_Force;
}

QVector2D TPoint::acceleration() const
{
    return m_Acceleration;
}

QVector2D TPoint::speed() const
{
    return m_Speed;
}

QVector2D TPoint::position() const
{
    return m_Position;
}

qreal TPoint::criticalRadius() const
{
    return m_CriticalRadius;
}

void TPoint::setForce(const QVector2D &force)
{
    m_Force = force;
    // qDebug() << id() << "  f = " << force;
}

void TPoint::setAcceleration(const qreal _x, const qreal _y)
{
    m_Acceleration.setX(_x);
    m_Acceleration.setY(_y);
}

void TPoint::setSpeed(const qreal _x, const qreal _y)
{
    m_Speed.setX(_x);
    m_Speed.setY(_y);
}


