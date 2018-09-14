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
	uiMgr->ufoClear(posX, posY);
    toShow = false;
	posY = UFOPOSY;
	posX = SCREENWIDTH - UFOWIDTH;
}

void UFO::move(int posX)
{
	uiMgr->ufoClear(posX, posY);
	posX = posX;
	uiMgr->ufoRefresh();
	uiMgr->ufoDisplay(posX, posY);
}

void UFO::moveLeft()
{
	if (posX > 1) {
		move(posX - 1);
	} else {
		reset();
	}
}

int UFO::show()
{
	if (toShow &&
            GameTable::getInstance()->getAliens()->getY() > 0) {
        std::uniform_int_distribution<> dis(0, 200);
		if (dis(gen) == 0) {
            toShow = true;
		}
	}
	return toShow;
}

