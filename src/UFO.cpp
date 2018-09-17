#include "UIManager.h"
#include "UFO.h"
#include "GameTable.h"

UFO::UFO()
    : Animate()
{
    reset();
}

void UFO::reset()
{
	m_uiMgr->ufoClear(m_posX, m_posY);
    m_toShow = false;
	m_posY = UFOPOSY;
	m_posX = SCREENWIDTH - UFOWIDTH;
}

void UFO::move(int posX)
{
	m_uiMgr->ufoClear(m_posX, m_posY);
	m_posX = posX;
	m_uiMgr->ufoRefresh();
	m_uiMgr->ufoDisplay(m_posX, m_posY);
}

void UFO::moveLeft()
{
	if (m_posX > 1) {
		move(m_posX - 1);
	} else {
		reset();
	}
}

bool UFO::show()
{
	if (m_toShow &&
            GameTable::getInstance()->getAliens()->getY() > 0) {
        std::uniform_int_distribution<> dis(0, 200);
		if (dis(gen) == 0) {
            m_toShow = true;
		}
	}
	return m_toShow;
}

