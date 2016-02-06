/*!
 * @file TScreen.h
 *
 * @brief User screen
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 05, 2016
 */

#ifndef TSCREEN_H
#define TSCREEN_H

#include "QQmlVarPropertyHelpers.h"

#include <QObject>

class TScreen : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(int, x)
    QML_WRITABLE_VAR_PROPERTY(int, y)
    QML_WRITABLE_VAR_PROPERTY(int, width)
    QML_WRITABLE_VAR_PROPERTY(int, height)
    QML_WRITABLE_VAR_PROPERTY(int, scale)
    QML_WRITABLE_VAR_PROPERTY(int, offsetX)
    QML_WRITABLE_VAR_PROPERTY(int, offsetY)

public:
    explicit TScreen(QObject *parent = 0);
};

#endif // TSCREEN_H
