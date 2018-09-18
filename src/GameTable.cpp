#include "GameTable.h"
#include "ConfigurationManager.h"
#include "UIManager.h"

#include "Aliens.h"
#include "UFO.h"
#include "Player.h"
#include "common.h"
#include <iostream>

GameTable* GameTable::s_instance = nullptr;

GameTable* GameTable::getInstance()
{
    return createInstance();
}

GameTable* GameTable::createInstance()
{
    if (nullptr == s_instance) {
        s_instance = new GameTable();
    }
    return s_instance;
}

void GameTable::removeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

GameTable::GameTable()
    : m_ufo(new UFO())
    , m_player(new Player())
    , m_aliens(new Aliens())
    , m_uiMgr(UIManager::getInstance())
    , m_confMgr(ConfigurationManager::getInstance())
{
}

GameTable::~GameTable()
{
    delete m_ufo;
    delete m_player;
    delete m_aliens;
}

Aliens* GameTable::getAliens()
{
    return m_aliens;
}

UFO* GameTable::getUFO()
{
    return m_ufo;
}

Player* GameTable::getPlayer()
{
    return m_player;
}

bool GameTable::playerHitCheck(int hostileShotX, int hostileShotY)
{
    bool result = false;
    if (hostileShotY == PLAYERPOSY) {
        if (hostileShotX >= m_player->getX() &&
                hostileShotX <= m_player->getX() + PLAYERWIDTH - 1) {
            result = true;
        }
    }

    return result;
}

bool GameTable::hitCheck()
{
    int shotx = m_player->getMissileX();
    int shoty = m_player->getMissileY();
	if (shotx >= m_aliens->getX() && shotx <= m_aliens->getX() + ALIENS_MAX_NUMBER_X * 3 - 1
	    && shoty >= m_aliens->getY() && shoty <= m_aliens->getY() + (ALIENS_MAX_NUMBER_Y - 1) * 2) {
		int shipx = (shotx - m_aliens->getX()) / 3;
		int shipy = (shoty - m_aliens->getY()) / 2;
		if (alienBlock[shipy][shipx]) {
            calculateScore(alienBlock[shipy][shipx]);
            alienBlock[shipy][shipx] = 0;
            return true;
		}
	}
	return false;
}

bool GameTable::bunkersHitCheck(int shotx, int shoty)
{
	if (shotx >= BUNKERX && shotx < BUNKERX + BUNKERWIDTH
	    && shoty >= BUNKERY && shoty < BUNKERY + BUNKERHEIGHT) {
		int adjy = shoty - BUNKERY;
		int adjx = shotx - BUNKERX;
		if(bunker[adjy][adjx] == 1){
            bunker[adjy][adjx] = 0;
            return true;
		}
	}
    return false;
}

void GameTable::handleUFO()
{
    int shotX = m_player->getMissileX();
    int shotY = m_player->getMissileY();
    if (shotY == UFOPOSY) {
        if (shotX >= m_ufo->getX() &&
                shotX <= m_ufo->getY() + UFOWIDTH -1) {
            m_ufo->reset();
            calculateScore(UFO_ALIEN_TYPE);
            m_player->reload();
        }
    }
}


void GameTable::calculateScore(int alienType)
{
    int points[4] = {500, 200, 150, 100};
    m_confMgr->setScore(m_confMgr->getScore() + points[alienType]);
    // every 6000 pts player gets a new live
    if (m_confMgr->getScore() % 6000 == 0){
        m_confMgr->setLive(1 + m_confMgr->getLive());
    }
	m_uiMgr->statusDisplay(m_confMgr->getLevel(),
                           m_confMgr->getScore(),
                           m_confMgr->getLive());
}

bool GameTable::handleHit()
{
    bool result = false;
    m_player->reload();
    m_uiMgr->aliensClear(m_aliens->getX(),
                         m_aliens->getY(),
                         m_aliens->getRight(),
                         m_aliens->getBottom());
    m_aliens->render();
    if (m_confMgr->getNumShip() == 0) {
        result = true;
    }
    m_confMgr->updateWeite();
    m_uiMgr->playerMissileClear(m_player->getMissileX(),
                                m_player->getMissileY());
    m_uiMgr->aliensDisplay(m_aliens->getX(),
                           m_aliens->getY(),
                           m_aliens->getRight(),
                           m_aliens->getBottom());
    return result;
}

bool GameTable::hitCheck(Player* player)
{
    bool result = false;
    if (hitCheck()) {
        result = handleHit();
    }
    int missileX = m_player->getMissileX();
    int missileY = m_player->getMissileY();

    if (bunkersHitCheck(missileX, missileY)) {
        m_uiMgr->bunkersClearElement(missileX, missileY);
        m_player->reload();
    }
    handleUFO();
    return result;
}
