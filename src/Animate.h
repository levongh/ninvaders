#pragma once

/**
 * @class  Animate MovableAnimate
 * @file   Animate.h
 * @brief  base class for all game animates
 * @author Levon Ghukasyan
 */

class UIManager;
class ConfigurationManager;


class Animate
{
public:
    Animate();

public:
    virtual void reset() = 0;

public:
    inline int getX() const
    {
        return m_posX;
    }

    inline int getY() const
    {
        return m_posY;
    }

protected:
    int m_posX;
    int m_posY;

    UIManager* m_uiMgr;
};

class MovableAnimate : public Animate
{
public:
    MovableAnimate();

public:
    virtual bool moveMissile() = 0;

protected:
    int m_speed;

protected:
    ConfigurationManager* m_confMgr;
};
