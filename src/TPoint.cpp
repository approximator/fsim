/*!
 * @file TPoint.cpp
 *
 * @brief TPoint represents a point with it's own mass
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 07, 2016
 */

#include "TPoint.h"

#include <QDebug>

TPoint::TPoint(const uint _id, const qreal _x, const qreal _y, QObject *parent)
    : QObject(parent)
    , m_point_id(_id)
    , m_x(_x)
    , m_y(_y)
    , m_mass(80.0)
    , m_fixed(false)
    , m_obstacle(false)
    , m_force()
    , m_criticalRadius(1)
{
    qDebug() << "Added point [" << point_id() << "]: " << _x << ", " << _y;
}

TPoint::~TPoint()
{
    qDebug() << "Deleted point: " << point_id();
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
    return QVector2D(m_x, m_y);
}

void TPoint::set_acceleration(const qreal _x, const qreal _y)
{
    m_Acceleration.setX(_x);
    m_Acceleration.setY(_y);
}

void TPoint::set_speed(const qreal _x, const qreal _y)
{
    m_Speed.setX(_x);
    m_Speed.setY(_y);
}
