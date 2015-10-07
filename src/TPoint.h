/*!
 * @file TPoint.h
 *
 * @brief TPoint represents a point with it's own mass
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 07, 2015
 */

#ifndef TPOINT_H
#define TPOINT_H

#include <QObject>
#include <QDebug>
#include <QVector2D>

class TPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal id READ id NOTIFY idChanged)
    Q_PROPERTY(bool fixed READ fixed WRITE setFixed NOTIFY fixedChanged)
    Q_PROPERTY(qreal mass READ mass WRITE setMass NOTIFY massChanged)
public:
    explicit TPoint(const uint id, const qreal _x, const qreal _y, QObject *parent = 0);

    uint id() const;
    qreal x() const;
    qreal y() const;
    qreal mass() const;
    bool fixed() const;
    bool isObstacle() const;
    QVector2D force() const;
    QVector2D acceleration() const;
    QVector2D speed() const;
    QVector2D position() const;
    qreal criticalRadius() const;
    void setForce(const QVector2D& force);
    void setAcceleration(const qreal _x, const qreal _y);
    void setSpeed(const qreal _x, const qreal _y);
    void setSelected(bool _selected);
    void setFixed(bool _fixed);
    void setMass(qreal _mass);


public slots:
    void setX(const qreal x);
    void setY(const qreal y);

private:
    uint      m_Id       { 0    };
    QVector2D m_Position { 0, 0 };
    qreal     m_Mass     { 20.0 };
    QVector2D m_Force    { 0, 0 };
    QVector2D m_Acceleration   { 0, 0 };
    QVector2D m_Speed          { 0, 0 };
    double    m_CriticalRadius { 1    };

    bool      m_IsObstacle { false };
    bool      m_Fixed      { false };
    bool      m_Selected   { false };

signals:
    void xChanged();
    void yChanged();
    void idChanged();
    void fixedChanged();
    void massChanged();
};

#endif // TPOINT_H
