/*!
 * @file TSimWorld.cpp
 *
 * @brief Representation of a simulation world that contains points
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 07, 2016
 */

#include "TSimWorld.h"

#include <QtMath>

TSimWorld::TSimWorld(QObject *parent)
    : QObject(parent)
    , m_model(new TPointsModel(this, "x", "y"))
    , m_screen(new TScreen(this))
    , m_selectedPoint(nullptr)
    , m_gravity(1000)
    , m_damperCoefficient(5000)
{
    qRegisterMetaType<TPoint *>("TPoint*");
    qRegisterMetaType<TScreen *>("TScreen*");
}

TPoint *TSimWorld::getPointAt(qreal _x, qreal _y) const
{
    const int eps = 5; // 5 screen dots
    for (auto point = m_model->constBegin(), ee = m_model->constEnd(); point != ee; ++point)
        if (std::fabs(xToScreen((*point)->x()) - xToScreen(_x)) < eps
            && std::fabs(yToScreen((*point)->y()) - yToScreen(_y)) < eps)
            return (*point);
    return nullptr;
}

qreal TSimWorld::xToScreen(qreal xPos) const
{
    return xPos * m_screen->scale() + m_screen->offsetX();
}

qreal TSimWorld::yToScreen(qreal yPos) const
{
    return m_screen->height() - yPos * m_screen->scale() + m_screen->offsetY();
}

qreal TSimWorld::xToWorld(qreal xPos) const
{
    return (xPos - m_screen->offsetX()) / m_screen->scale();
}

qreal TSimWorld::yToWorld(qreal yPos) const
{
    return (m_screen->height() - yPos + m_screen->offsetY()) / m_screen->scale();
}

TPoint *TSimWorld::addPoint(qreal _x, qreal _y)
{
    auto newPoint = new TPoint(m_model->count(), _x, _y, m_model);
    for (auto point = m_model->constBegin(), lastPoint = m_model->constEnd(); point != lastPoint; ++point) {
        newPoint->addVisibleObject(*point);
        (*point)->addVisibleObject(newPoint);
    }
    m_model->append(newPoint);
    return newPoint;
}

inline qreal rungeKutta(const qreal h, const qreal val)
{
    const qreal k1 = h * val;
    const qreal k2 = h * val + k1 / 2;
    const qreal k3 = h * val + k2 / 2;
    const qreal k4 = h * val + k3;
    const qreal d  = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return d;
}

void TSimWorld::update()
{
    // Update forces and positions
    for (auto i = m_model->constBegin(), ee = m_model->constEnd(); i != ee; ++i) {
        TPoint *point = (*i);

        for (auto j = point->visibleObjects().begin(); j != point->visibleObjects().end(); ++j) {
            TPoint *otherPoint = (*j);
            if (point == otherPoint) {
                continue;
            }

            const qreal distance = point->position().distanceToPoint(otherPoint->position()); // distance
            QVector2D Fij        = (otherPoint->position() - point->position()).normalized(); // Force direction

            const qreal criticalRadius = (point->criticalRadius() + otherPoint->criticalRadius());

            qreal attractiveForce = 0;
            if (!otherPoint->obstacle())
                attractiveForce = point->mass() * otherPoint->mass() / qPow(distance, 2); //        mi * mj / d^2

            const qreal repulsiveForce
                = criticalRadius * point->mass() * otherPoint->mass() / qPow(distance, 3); //  Rcr * mi * mj / d^3
            const qreal forceMagnitude = gravity() * (attractiveForce - repulsiveForce);
            Fij *= forceMagnitude;                  // forceDirection * forceMagnitude
            point->set_force(point->force() + Fij); // Fi = Fi + Fij
        }

        point->set_force(point->force() + point->ownForce());

        // Update point position
        const qreal udx = -damperCoefficient() * point->speed().x();
        const qreal udy = -damperCoefficient() * point->speed().y();

        point->set_acceleration( // d^2x/dt^2 = 1/m * (F + (u * dx/dt))
            (point->force().x() + udx) / point->mass(), (point->force().y() + udy) / point->mass());

        const qreal h = 0.0005;
        point->set_speed(point->speed().x() + rungeKutta(h, point->acceleration().x()),
            point->speed().y() + rungeKutta(h, point->acceleration().y()));

        point->set_x(point->x() + rungeKutta(h, point->speed().x()));
        point->set_y(point->y() + rungeKutta(h, point->speed().y()));
        point->set_force(QVector2D(0, 0));
    }
}

void TSimWorld::clean()
{
    m_model->clear();
}

QVector2D TSimWorld::forceAt(qreal _x, qreal _y)
{
    QVector2D pos   = QVector2D(_x, _y);
    QVector2D force = QVector2D(0, 0);
    for (auto j = m_model->constBegin(), j_end = m_model->constEnd(); j != j_end; ++j) {
        if (pos == (*j)->position())
            continue;

        const qreal distance = pos.distanceToPoint((*j)->position()); // distance

        if (distance < 0.5)
            return QVector2D(0, 0);

        QVector2D Fij = ((*j)->position() - pos).normalized(); // Force direction

        const qreal criticalRadius  = (*j)->criticalRadius();
        const qreal attractiveForce = 1 * (*j)->mass() / qPow(distance, 2);                  //        mi * mj / d^2
        const qreal repulsiveForce  = criticalRadius * 1 * (*j)->mass() / qPow(distance, 3); //  Rcr * mi * mj / d^3
        const qreal forceMagnitude  = gravity() * (attractiveForce - repulsiveForce);
        Fij *= forceMagnitude; // forceDirection * forceMagnitude
        force += Fij;          // Fi = Fi + Fij
    }

    return force.length() > 400 ? force.normalized() * 400 : force;
}
