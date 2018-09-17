#pragma once

#include "Animate.h"

class Aliens : public MovableAnimate
{
public:
    Aliens();
    void reset();
    bool move();
    void render();
    bool missileMove();
    void bunkersReset();

public:
    virtual bool moveMissile();

public:
    inline int getRight() const
    {
        return m_right;
    }

    inline int getBottom() const
    {
        return m_bottom;
    }

private:
    int m_right;
    int m_left;
    int m_bottom;
};
