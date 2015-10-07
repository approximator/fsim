/*!
 * @file TSimWorld.cpp
 *
 * @brief Representation of a simulation world that contains points
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 07, 2015
 */

#include "TSimWorld.h"

#include <QtMath>

TSimWorld::TSimWorld(QObject *parent) :
    QAbstractListModel(parent)
{
    qRegisterMetaType<TPoint*>("TPoint*");
    qRegisterMetaType<TScreen*>("TScreen*");

    m_Screen = new TScreen(this);
    m_Roles.insert(Roles::Name, "name");
}

int TSimWorld::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_Points.size();
}

QVariant TSimWorld::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= m_Points.size())
        return QVariant();

    switch (role)
    {
    case Name:
    case Qt::DisplayRole:
        return QVariant::fromValue(m_Points.at(index.row())->id());
        break;
    default:
        return QVariant();
        break;
    }
}

TScreen *TSimWorld::screen() const
{
    return m_Screen;
}

TPoint *TSimWorld::selectedPoint() const
{
    return m_SelectedPoint;
}

qreal TSimWorld::damperCoeff() const
{
    return m_DamperCoeff;
}

void TSimWorld::setSelectedPoint(TPoint *_point)
{
    if (m_SelectedPoint == _point)
        return;

    for (const auto& point : m_Points)
        point->setSelected(false);

    if (_point)
        _point->setSelected(true);

    m_SelectedPoint = _point;
    emit selectedPointChanged();
}

void TSimWorld::setDamperCoeff(qreal _coeff)
{
    if (m_DamperCoeff == _coeff)
        return;

    m_DamperCoeff = _coeff;
    emit damperCoeffChanged();
}

int TSimWorld::pointsNum() const
{
    return m_Points.size();
}

QHash<int, QByteArray> TSimWorld::roleNames() const
{
    return m_Roles;
}

TPoint *TSimWorld::getPoint(int index) const
{
    return m_Points.at(index);
}

TPoint *TSimWorld::getPointAt(qreal _x, qreal _y) const
{
    const qreal eps = 10 / m_Screen->scale();
    for (const auto &point : m_Points)
        if (std::fabs(point->x() - _x) < eps && std::fabs(point->y() - _y) < eps)
            return point;
    return nullptr;
}

qreal TSimWorld::pointXScreenPos(int index) const
{
    return xToScreen(m_Points.at(index)->x());
}

qreal TSimWorld::pointYScreenPos(int index) const
{
    return yToScreen(m_Points.at(index)->y());
}

qreal TSimWorld::xToScreen(qreal xPos) const
{
    return xPos * m_Screen->scale() + m_Screen->offsetX();
}

qreal TSimWorld::yToScreen(qreal yPos) const
{
    return m_Screen->height() - yPos * m_Screen->scale() + m_Screen->offsetY();
}

qreal TSimWorld::xScreenToWorld(qreal xPos) const
{
    return (xPos - m_Screen->offsetX()) / m_Screen->scale();
}

qreal TSimWorld::yScreenToWorld(qreal yPos) const
{
    return (m_Screen->height() - yPos + m_Screen->offsetY()) / m_Screen->scale();
}

void TSimWorld::addPoint(qreal _x, qreal _y)
{
    m_Points.push_back(new TPoint(m_Points.size(), _x, _y, this));
}

inline qreal rungeKutta(const qreal h, const qreal val)
{
    const qreal k1 = h * val;
    const qreal k2 = h * val + k1 / 2;
    const qreal k3 = h * val + k2 / 2;
    const qreal k4 = h * val + k3;
    const qreal d = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return d;
}

void TSimWorld::update()
{
    if (m_SimPause)
        return;

    // Update forces and positions
    for (auto i = m_Points.begin(), ee = m_Points.end(); i != ee; ++i)
    {
        TPoint* point = (*i);
        if (point->fixed())
            continue;

        for (auto j = i + 1; j != ee; ++j)
        {
            TPoint* otherPoint = (*j);
            // if (point == otherPoint) //! @todo: remove this
            // {
            //     qDebug() << "continue";
            //     continue;
            // }

            const qreal distance = point->position().distanceToPoint(otherPoint->position()); // distance
            QVector2D Fij = (otherPoint->position() - point->position()).normalized();  // Force direction

            const qreal gravityForce = 400;
            const qreal criticalRadius = (point->criticalRadius() + otherPoint->criticalRadius());

            qreal attractiveForce = 0;
            if (!otherPoint->isObstacle())
                attractiveForce = point->mass() * otherPoint->mass() / qPow(distance, 2);                         //        mi * mj / d^2

            const qreal repulsiveForce = criticalRadius * point->mass() * otherPoint->mass() / qPow(distance, 3); //  Rcr * mi * mj / d^3
            const qreal forceMagnitude = gravityForce * (attractiveForce - repulsiveForce);
            Fij *= forceMagnitude;     // forceDirection * forceMagnitude
            point->setForce(point->force() + Fij); // Fi = Fi + Fij
            otherPoint->setForce(otherPoint->force() - Fij);
        }

        // Update point position
        const qreal udx = -m_DamperCoeff * point->speed().x();
        const qreal udy = -m_DamperCoeff * point->speed().y();

        point->setAcceleration( // d^2x/dt^2 = 1/m * (F + (u * dx/dt))
                                (point->force().x() + udx) / point->mass(),
                                (point->force().y() + udy) / point->mass());

        const qreal h = 0.0005;
        point->setSpeed(point->speed().x() + rungeKutta(h, point->acceleration().x()),
                        point->speed().y() + rungeKutta(h, point->acceleration().y()));

        point->setX(point->x() + rungeKutta(h, point->speed().x()));
        point->setY(point->y() + rungeKutta(h, point->speed().y()));
        point->setForce(QVector2D(0, 0));
    }
}

QVector2D TSimWorld::forceAt(qreal _x, qreal _y)
{
    QVector2D pos = QVector2D(_x, _y);
    QVector2D force = QVector2D(0, 0);
    for (QList<TPoint*>::iterator j = m_Points.begin(), j_end = m_Points.end(); j != j_end; ++j)
    {
        if (pos == (*j)->position())
            continue;

        const qreal distance = pos.distanceToPoint((*j)->position()); // distance

        if (distance < 0.5)
            return QVector2D(0, 0);

        QVector2D Fij = ((*j)->position() - pos).normalized();  // Force direction

        const qreal gravityForce = 400;
        const qreal criticalRadius = (*j)->criticalRadius();

        const qreal attractiveForce = 1 * (*j)->mass() / qPow(distance, 2);                 //        mi * mj / d^2
        const qreal repulsiveForce = criticalRadius * 1 * (*j)->mass() / qPow(distance, 3); //  Rcr * mi * mj / d^3

        const qreal forceMagnitude = gravityForce * (attractiveForce - repulsiveForce);

        Fij *= forceMagnitude;     // forceDirection * forceMagnitude

        force += Fij; // Fi = Fi + Fij
    }

    if (force.length() > 400)
        force = force.normalized() * 400;

    return force;
}

