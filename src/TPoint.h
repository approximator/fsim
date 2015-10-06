#ifndef TPOINT_H
#define TPOINT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QVector2D>
#include <QColor>
#include <QFont>
#include <qmath.h>


class TPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
public:
    explicit TPoint(const uint id, const qreal _x, const qreal _y, QObject *parent = 0);

    uint id() const;
    qreal x() const;
    qreal y() const;

public slots:
    void setX(const qreal x);
    void setY(const qreal y);

private:
    uint m_Id;
    QVector2D m_Position;

signals:
    void xChanged(qreal);
    void yChanged(qreal);
};

#endif // TPOINT_H
