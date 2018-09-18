#pragma once

/**
 * @class  Player
 * @file   Player.h
 * @brief  
 * @author Levon Ghukasyan
 */

#include "Animate.h"

class Player : public MovableAnimate
{
public:
    Player();
    void reset();

    ///@brief Player moving functions
    ///{
public:
    void moveLeft();
    void moveRight();
    ///}

    ///@brief Player moveing speed
    ///{
public:
    void turboOn();
    void turboOff();
    ///}

    ///@brief fire the missile
    ///{
public:
    void fire();
    ///}

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
