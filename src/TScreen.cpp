#include "TScreen.h"

TScreen::TScreen(QObject *parent) : QObject(parent)
{

}

int TScreen::x() const
{
    return m_X;
}

int TScreen::y() const
{
    return m_Y;
}

int TScreen::width() const
{
    return m_Width;
}

int TScreen::height() const
{
    return m_Height;
}

int TScreen::scale() const
{
    return m_Scale;
}

void TScreen::setX(int _x)
{
    if (m_X == _x)
        return;
    m_X = _x;
    emit xChanged();
}

void TScreen::setY(int _y)
{
    if (m_Y == _y)
        return;
    m_Y = _y;
    emit yChanged();
}

void TScreen::setWidth(int _width)
{
    if (m_Width == _width)
        return;
    m_Width = _width;
    emit widthChanged();
}

void TScreen::setHeight(int _height)
{
    if (m_Height == _height)
        return;
    m_Height = _height;
    emit heightChanged();
}

void TScreen::setScale(int _scale)
{
    if (m_Scale == _scale)
        return;
    m_Scale = _scale;
    emit scaleChanged();
}
