/*!
 * @file TPoint.h
 *
 * @brief TPoint represents a point with it's own mass
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 07, 2016
 */

#ifndef TPOINT_H
#define TPOINT_H

#include "QQmlVarPropertyHelpers.h"

#include <QDebug>
#include <QObject>
#include <QVector2D>

class TPoint : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(int, point_id)
    QML_WRITABLE_VAR_PROPERTY(qreal, x)
    QML_WRITABLE_VAR_PROPERTY(qreal, y)
    QML_WRITABLE_VAR_PROPERTY(qreal, mass)
    QML_WRITABLE_VAR_PROPERTY(bool, obstacle)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, force)
    QML_WRITABLE_VAR_PROPERTY(QVector2D, ownForce)
    QML_WRITABLE_VAR_PROPERTY(qreal, criticalRadius)

    QML_WRITABLE_VAR_PROPERTY(bool, acceptNewPoints)

public:
    explicit TPoint(const uint id, const qreal _x, const qreal _y, QObject* parent = 0);
    ~TPoint();

    QVector2D acceleration() const;
    QVector2D speed() const;
    QVector2D position() const;
    void set_acceleration(const qreal _x, const qreal _y);
    void set_speed(const qreal _x, const qreal _y);

    Q_INVOKABLE void addVisibleObject(TPoint* point);
    Q_INVOKABLE const QList<TPoint*>& visibleObjects() const;
    Q_INVOKABLE void clearVisibleObjectsList();

private:
    QVector2D m_Acceleration{ 0, 0 };
    QVector2D m_Speed{ 0, 0 };

    QList<TPoint*> m_visibleObjects;
};

#endif // TPOINT_H
