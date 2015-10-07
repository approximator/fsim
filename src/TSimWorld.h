/*!
 * @file TSimWorld.h
 *
 * @brief Representation of a simulation world that contains points
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 07, 2015
 */

#ifndef SIMWORLD_H
#define SIMWORLD_H

#include "TPoint.h"
#include "TScreen.h"

#include <QList>
#include <QObject>
#include <QAbstractListModel>

class TSimWorld : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TScreen* screen READ screen NOTIFY screenChanged)
    Q_PROPERTY(TPoint* selectedPoint READ selectedPoint WRITE setSelectedPoint NOTIFY selectedPointChanged)
    Q_PROPERTY(bool simPause MEMBER m_SimPause)
    Q_PROPERTY(qreal damperCoeff READ damperCoeff WRITE setDamperCoeff NOTIFY damperCoeffChanged)
public:
    enum Roles {
        Name = Qt::UserRole + 1
    };
    explicit TSimWorld(QObject *parent = 0);
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE int pointsNum() const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE TPoint* getPoint(int index) const;
    Q_INVOKABLE TPoint* getPointAt(qreal _x, qreal _y) const;
    Q_INVOKABLE qreal pointXScreenPos(int index) const;
    Q_INVOKABLE qreal pointYScreenPos(int index) const;

    Q_INVOKABLE qreal xToScreen(qreal xPos) const;
    Q_INVOKABLE qreal yToScreen(qreal yPos) const;
    Q_INVOKABLE qreal xScreenToWorld(qreal xPos) const;
    Q_INVOKABLE qreal yScreenToWorld(qreal yPos) const;

    Q_INVOKABLE void addPoint(qreal _x, qreal _y);
    Q_INVOKABLE void update();

    TScreen* screen() const;
    TPoint* selectedPoint() const;
    qreal damperCoeff() const;
    void setSelectedPoint(TPoint* _point);
    void setDamperCoeff(qreal _coeff);

private:
    TSimWorld(const TSimWorld& other);
    TSimWorld& operator=(const TSimWorld& other);

    TScreen*               m_Screen { nullptr };
    QList<TPoint*>         m_Points { };
    TPoint*                m_SelectedPoint { nullptr };
    QHash<int, QByteArray> m_Roles  { };
    bool                   m_SimPause { false };

    // world parameters
    qreal m_DamperCoeff { 400 };

signals:
    void screenChanged();
    void selectedPointChanged();
    void damperCoeffChanged();

public slots:
};

#endif // SIMWORLD_H
