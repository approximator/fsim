/*!
 * @file TScreen.h
 *
 * @brief User screen
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 07, 2015
 */

#ifndef TSCREEN_H
#define TSCREEN_H

#include <QObject>

class TScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ x WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(int offsetX READ offsetX WRITE setOffsetX NOTIFY offsetXChanged)
    Q_PROPERTY(int offsetY READ offsetY WRITE setOffsetY NOTIFY offsetYChanged)
public:
    explicit TScreen(QObject *parent = 0);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    qreal scale() const;
    int offsetX() const;
    int offsetY() const;

    void setX(int _x);
    void setY(int _y);
    void setWidth(int _width);
    void setHeight(int _height);
    void setScale(int _height);
    void setOffsetX(int _offsetX);
    void setOffsetY(int _offsetY);

private:
    int   m_X       = 0;
    int   m_Y       = 0;
    int   m_Width   = 0;
    int   m_Height  = 0;
    qreal m_Scale   = 50.0;
    int   m_OffsetX = 0;
    int   m_OffsetY = 0;

signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void scaleChanged();
    void offsetXChanged();
    void offsetYChanged();

public slots:
};

#endif // TSCREEN_H
