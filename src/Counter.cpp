#include "Counter.h"
#include "UIManager.h"
#include "GameTable.h"

Counter::Counter(GameManager* mgr)
    : m_mgr(mgr)
{
    unsigned m_aliensMove     = 0;
    unsigned m_aliensShot     = 0;
    unsigned m_playerShot     = 0;
    unsigned m_ufoMove        = 0;
    unsigned m_titleAnimation = 0;
    unsigned m_gameOver       = 0;
}

void Counter::reset()
{
    m_aliensMove = 0;
    m_aliensShot = 0;
    m_playerShot = 0;
    m_ufoMove    = 0;
}

void Counter::updateCounter()
{
    if (m_aliensShot++ >= 5) {
        m_aliensShot = 0;
    }
    if (m_playerShot++ >= 1) {
        m_playerShot = 0;
    }
    if (m_aliensMove++ >= m_mgr->confMgr->getWeite()) {
        m_aliensMove = 0;
    }
    if (m_ufoMove++ >= 3) {
        m_ufoMove = 0;
    }
}

void Counter::animationUpdate()
{
    if (m_titleAnimation == 0) {
        m_mgr->uiMgr->titleScreenDisplay();
    }
    if (m_titleAnimation++ >= 6) {
        m_titleAnimation = 0;
    }
}

void Counter::checkGameOver()
{
    if (m_gameOver == 100) {
        m_mgr->uiMgr->battleFieldClear();
        m_mgr->confMgr->setMode(Mode::HIGHSCORE);
        m_gameOver = 0;
    } else {
        m_mgr->uiMgr->gameOverDisplay();
        ++m_gameOver;
    }
}

void Counter::checkUFO()
{
    if (m_ufoMove == 0 &&
            m_mgr->gameTable->getUFO()->show() == 1) {
        m_mgr->gameTable->getUFO()->moveLeft();
    }
}

void Counter::checkAliensShot()
{
    if (m_aliensShot == 0 &&
            m_mgr->gameTable->getAliens()->moveMissile()) {
        m_mgr->confMgr->setLive(m_mgr->confMgr->getLive() - 1);
        m_mgr->drawscore();
        m_mgr->gameTable->getPlayer()->explode();
        if (m_mgr->confMgr->getLevel() == 0) {
            m_mgr->confMgr->setMode(Mode::GAME_OVER);
        }
    }
}

void Counter::checkPlayerShot()
{
    if (m_playerShot == 0 &&
            m_mgr->gameTable->getPlayer()->moveMissile() == 1) {
        m_mgr->confMgr->setMode(Mode::NEXT_LEVEL);
    }
}

void Counter::checkAliensMove()
{
    if (m_aliensMove == 0 &&
            m_mgr->gameTable->getAliens()->move() == 1) {
        m_mgr->confMgr->setLive(0);
        m_mgr->confMgr->setMode(Mode::GAME_OVER);
    }
}
