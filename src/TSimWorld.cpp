#include "TSimWorld.h"

TSimWorld::TSimWorld(QObject *parent) :
    QAbstractListModel(parent)
{
    qRegisterMetaType<TPoint*>("TPoint*");
    qRegisterMetaType<TScreen*>("TScreen*");

    m_Screen = new TScreen(this);
    m_Roles.insert(Roles::Name, "name");

    m_Points.push_back(new TPoint(0, 10.0, 10.0, this));
    m_Points.push_back(new TPoint(1, 11.0, 10.0, this));
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

