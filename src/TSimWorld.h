/*!
 * @file TSimWorld.h
 *
 * @brief Representation of a simulation world that contains points
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 07, 2016
 */

#ifndef SIMWORLD_H
#define SIMWORLD_H

#include "QQmlObjectListModel.h"
#include "TPoint.h"
#include "TScreen.h"

#include <QAbstractListModel>
#include <QList>
#include <QObject>

typedef QQmlObjectListModel<TPoint> TPointsModel;

class TSimWorld : public QObject
{
    Q_OBJECT
    QML_READONLY_VAR_PROPERTY(TPointsModel *, model)
    QML_READONLY_VAR_PROPERTY(TScreen *, screen)
    QML_WRITABLE_VAR_PROPERTY(TPoint *, selectedPoint)
    QML_WRITABLE_VAR_PROPERTY(qreal, gravity)
    QML_WRITABLE_VAR_PROPERTY(qreal, damperCoefficient)

public:
    explicit TSimWorld(QObject *parent = 0);

    Q_INVOKABLE TPoint *getPointAt(qreal _x, qreal _y) const;

    Q_INVOKABLE qreal xToScreen(qreal xPos) const;
    Q_INVOKABLE qreal yToScreen(qreal yPos) const;
    Q_INVOKABLE qreal xToWorld(qreal xPos) const;
    Q_INVOKABLE qreal yToWorld(qreal yPos) const;

    Q_INVOKABLE TPoint *addPoint(qreal _x, qreal _y);
    Q_INVOKABLE void update();
    Q_INVOKABLE void clean();
    Q_INVOKABLE QVector2D forceAt(qreal _x, qreal _y);

private:
    TSimWorld(const TSimWorld &other) = delete;
    TSimWorld &operator=(const TSimWorld &other) = delete;

public slots:
};

#endif // SIMWORLD_H
