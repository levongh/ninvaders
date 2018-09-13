#include "common.h"
#include "GameManager.h"
#include "ConfigurationManager.h"

/**
 * @class  Counter
 * @file   Counter.h
 * @brief  Counter class designed to calculate and update game state
 * @author Levon Ghukasyan
 */

class Counter
{
public:
    Counter(GameManager* mgr);

    /**
     * @brief reset
     */
    void reset();

    /**
     * @brief updateCounter function is updateteing the counter data
     */
    void updateCounter();

    /**
     * @brief animationUpdate functions checks if neded titel display animation and updates title screen
     */
    void animationUpdate();

    /**
     * @brief checkGameOver functions checks if the game should be in GAME_OVER state
     */
    void checkGameOver();

    /**
     * @brief checkUFO functions checks if UFO is movable if so it moves
     */
    void checkUFO();

    /**
     * @brief checkAliensShot checks if alien shotted the player is the player live is expiered
     *        then the game goes to the GAME_OVER game
     */
    void checkAliensShot();

    /**
     * @brief checkPlayerShot checks if allien was shotted by player
     */
    void checkPlayerShot();

    /**
     * @brief checkAliensMove function checks if allien can move or not
     *        if the alienc can not move the game is moving to GAME_OVER state
     */
    void checkAliensMove();

private:
    unsigned m_aliensMove;
    unsigned m_aliensShot;
    unsigned m_playerShot;
    unsigned m_ufoMove;
    unsigned m_titleAnimation;
    unsigned m_gameOver;

private:
    GameManager* m_mgr;
};
