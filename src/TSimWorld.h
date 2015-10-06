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

    TScreen* screen() const;

private:
    TScreen* m_Screen { nullptr };
    QList<TPoint*> m_Points { };
    QHash<int, QByteArray> m_Roles { };

signals:
    void screenChanged();

public slots:
};

#endif // SIMWORLD_H
