/*!
 * @file TScreen.cpp
 *
 * @brief User screen
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Feb 05, 2016
 */

#include "TScreen.h"

TScreen::TScreen(QObject *parent)
    : QObject(parent)
    , m_x(0)
    , m_y(0)
    , m_width(100)
    , m_height(100)
    , m_scale(50.0)
    , m_offsetX(0)
    , m_offsetY(0)
{
}
