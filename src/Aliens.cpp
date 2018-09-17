#include "UIManager.h"
#include "ConfigurationManager.h"
#include "Aliens.h"

#include "GameTable.h"

int alienshotnum;
int lowest_ship[ALIENS_MAX_NUMBER_X];
int alienshotx[ALIENS_MAX_MISSILES];
int alienshoty[ALIENS_MAX_MISSILES];

int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];
int bunker[BUNKERHEIGHT][BUNKERWIDTH + 1];

Aliens::Aliens()
    : MovableAnimate()
{
}

void Aliens::reset()
{
    // three different types of aliens [5], [10]
    int level[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X]={
        {1,1,1,1,1,1,1,1,1,1},
        {2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2},
        {3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3}
    };

    m_uiMgr->aliensClear(m_posX, m_posY, m_right, m_bottom);
    // reset alien position
    m_posX  = 0;
    m_posY  = 0;
    m_right = 0;
    m_bottom= 0;
    m_left  = 0;
    m_speed = 1;

    for (int i = 0; i < ALIENS_MAX_NUMBER_X; ++i) {
        for (int j = 0; j < ALIENS_MAX_NUMBER_Y; ++j) {
            alienBlock[j][i] = level[j][i];
        }
    }
    for (int i = 0; i < ALIENS_MAX_MISSILES; ++i) {
        if (alienshotx[i] != 0) {
            m_uiMgr->aliensMissileClear(alienshotx[i],alienshoty[i]);	// clear old position
        }
        alienshotx[i] = 0;
        alienshoty[i] = 0;
    }
    alienshotnum  = 1;
    alienshotx[0] = 5;
    alienshoty[0] = 1;
}

bool Aliens::move()
{
    int cx, cy;
    bool result = false;

    render();
    m_uiMgr->aliensClear(m_posX, m_posY, m_right, m_bottom);

    m_posX = m_posX + m_speed;

    // when aliens reached m_left or right screen-border
    if (m_posX == (BUNKERWIDTH + BUNKERX - 5 - m_right) ||
            m_posX == (BUNKERX + m_left)) {
        ++m_posY;
        if (m_posY == SCREENHEIGHT - 2 - m_bottom) {
            result = true;
        }
        if (m_posY == BUNKERY - m_bottom) {
            for(cx = 0; cx < BUNKERWIDTH; ++cx) {
                for(cy = 0; cy < BUNKERHEIGHT; ++cy) {
                    bunker[cy][cx] = 0;
                }
            }
            m_uiMgr->bunkersClear();
        }
        m_speed = m_speed * (-1);
    }
    m_uiMgr->aliensDisplay(m_posX, m_posY, m_right, m_bottom);

    return result;
}

void Aliens::render()
{
    int c = 0;

    m_left = 1;
    m_right =- 1;
    m_bottom =- 1;
    m_confMgr->setNumShip(0);
    for (int k = 0; k < 11; ++k) {
        lowest_ship[k] = -1;
    }

    for (int row = 0; row < ALIENS_MAX_NUMBER_Y * 2; ++row) {
        if ((row % 2) == 0){
            for (int k = 0; k < ALIENS_MAX_NUMBER_X; ++k) {
                if (alienBlock[c][k] != 0) {
                    lowest_ship[k] = row;
                    m_confMgr->setNumShip(1 + m_confMgr->getNumShip());
                    if (m_left == 1 || -k > m_left) {m_left =- k;}
                    if (m_right == -1 || k > m_right) {m_right = k;}
                    if (m_bottom == -1 || c > m_bottom) {m_bottom = c;}
                }
            }
        } else {
            ++c;
        }
    }
    m_bottom = m_bottom * 2;
    m_left   = m_left * 3;
    m_right  = m_right * 3;

    m_uiMgr->aliensRefresh(m_confMgr->getLevel(), &alienBlock[0][0]);

}

bool Aliens::moveMissile()
{
    bool result = false;
    int shootThreshold;
    static int alienshot_counter = 0;

    shootThreshold = (m_confMgr->getSkillLevel() * 8) *
        (m_confMgr->getNumShip() + 2);
    alienshot_counter = alienshot_counter + 10 ;
    // loop all possible missiles
    GameTable* table = GameTable::getInstance();
    for (int i = 0; i < ALIENS_MAX_MISSILES; ++i) {
        if (alienshotx[i] != 0) {
            m_uiMgr->aliensMissileClear(alienshotx[i],alienshoty[i]);
            if (table->bunkersHitCheck(alienshotx[i], alienshoty[i])) {
                alienshotx[i] = 0;
            }
            ++alienshoty[i];
            if (table->playerHitCheck(alienshotx[i], alienshoty[i])) {
                alienshotx[i] = 0;
                result = true;
            }
        } else {
            if (alienshot_counter > shootThreshold && m_confMgr->getNumShip() > 0) {
                alienshot_counter = 0;
                std::uniform_int_distribution<> dis(0, ALIENS_MAX_NUMBER_X);
                int tmp = dis(gen);
                while (lowest_ship[tmp] == -1) {
                    tmp = dis(gen);
                }
                alienshoty[i] = m_posY + lowest_ship[tmp];
                alienshotx[i] = m_posX + tmp * 3;
            }
        }
        if (alienshotx[i] != 0) {
            if (alienshoty[i] == SCREENHEIGHT - 1) {
                alienshotx[i] = 0;
            } else {
                m_uiMgr->aliensMissileDisplay(alienshotx[i], alienshoty[i]);
            }
        }

    }
    return result;
}

void Aliens::bunkersReset()
{
	char bunkerd[BUNKERHEIGHT][BUNKERWIDTH+1] = {
		"        ###                 ###                 ###                 ###         ",
		"       #####               #####               #####               #####        ",
		"      #######             #######             #######             #######       ",
		"      ##   ##             ##   ##             ##   ##             ##   ##       "
	};

    for (int a = 0; a < BUNKERWIDTH; ++a) {
        for (int b = 0; b < BUNKERHEIGHT; ++b) {
            if (bunkerd[b][a] == '#') {
                bunker[b][a] = 1;
             } else {
                 bunker[b][a] = 0;
             }
        }
    }

    m_uiMgr->bunkersDisplay(&bunker[0][0]);
}

