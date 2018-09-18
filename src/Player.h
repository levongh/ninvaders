#pragma once

#include "Animate.h"

class Player : public MovableAnimate
{

public:
    Player();
    void reset();
    void moveLeft();
    void moveRight();

    void turboOn();
    void turboOff();

    void fire();
    void explode();
    void reload();

public:
    inline const int& getMissileX() const
    {
        return m_missileX;
    }

    inline const int& getMissileY() const
    {
        return m_missileY;
    }

    virtual bool moveMissile() override;

private:
    void move(int newPosX);

private:
    bool m_fired;
    int  m_missileX;
    int  m_missileY;
};
