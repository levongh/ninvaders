#pragma once

/**
 * @class  Animate MovableAnimate
 * @file   Animate.h
 * @brief  base class for all game animates
 * @author Levon Ghukasyan
 */

class UIManager;

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

    UIManager* uiMgr;
};

class MovableAnimate : public Animate
{
public:
    virtual bool moveMissile();

protected:
    int m_speed;
};
