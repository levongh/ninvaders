#pragma once

/**
 * @class  Animate
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
        return posX;
    }

    inline int getY() const
    {
        return posY;
    }

protected:
    int posX;
    int posY;

    UIManager* uiMgr;
};
