#include "ConfigurationManager.h"
#include "UIManager.h"
#include "Player.h"
#include "GameTable.h"

Player::Player()
    : MovableAnimate()
{
    reset();
}

void Player::reset()
{
    if (m_fired) {
        m_uiMgr->playerMissileClear(m_missileX, m_missileY);
    }
    m_uiMgr->playerClear(m_posX, m_posY);
    m_posY     = PLAYERPOSY;
    m_posX     = 0;
    m_speed    = 1;
    m_fired    = false;
    m_missileX = 0;
    m_missileY = 0;

    m_uiMgr->playerDisplay(m_posX, m_posY);
}

void Player::move(int newPosX)
{
    m_uiMgr->playerClear(m_posX, m_posY);
    m_posX = newPosX;
    m_uiMgr->playerDisplay(m_posX, m_posY);
}

void Player::moveLeft()
{
    if (m_posX > m_speed) {
        move(m_posX - m_speed);
    } else {
        move(0);
    }
}

void Player::moveRight()
{
    if (m_posX < SCREENWIDTH - PLAYERWIDTH - m_speed) {
        move(m_posX + m_speed);
    } else {
        move(SCREENWIDTH - PLAYERWIDTH);
    }
}

void Player::turboOn()
{
	m_speed = 2;
}

void Player::turboOff()
{
	m_speed = 1;
}

void Player::fire()
{
    if (!m_fired) {
        m_fired = true;
        m_missileX = m_posX + PLAYERWIDTH / 2;
        m_missileY = PLAYERPOSY;
    }
}

void Player::reload()
{
    m_fired = false;
}

bool Player::moveMissile()
{
    // only do movements if there is a missile to move
    if (m_fired) {
        m_uiMgr->playerMissileClear(m_missileX, m_missileY);		// clear old missile position
        m_uiMgr->playerDisplay(m_posX, m_posY);
        --m_missileY;

        if (m_missileY < 0) {
            reload();
        } else {
            m_uiMgr->playerMissileDisplay(m_missileX, m_missileY);
        }
        GameTable* table = GameTable::getInstance();
        return table->hitCheck(this);
    }
}

void Player::explode()
{
	m_uiMgr->playerExplosionDisplay(m_posX, m_posY);
	m_uiMgr->playerDisplay(m_posX, m_posY);
}

