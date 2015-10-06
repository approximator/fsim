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
public:
    explicit TScreen(QObject *parent = 0);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    int scale() const;

    void setX(int _x);
    void setY(int _y);
    void setWidth(int _width);
    void setHeight(int _height);
    void setScale(int _height);

private:
    int m_X      = 0;
    int m_Y      = 0;
    int m_Width  = 0;
    int m_Height = 0;
    int m_Scale  = 0;

signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void scaleChanged();


public slots:
};

Q_DECLARE_METATYPE(TScreen *)

#endif // TSCREEN_H
