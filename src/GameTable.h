#pragma once

#include "Aliens.h"
#include "UFO.h"
#include "Player.h"

class GameTable
{

public:
    /*
     * @brief create the singleton object if it is not exist and returns this object
     * \ if it is exist returns it.
     */
    static GameTable* getInstance();

    static GameTable* createInstance();

    /*
     * @brief removes the singleton object
     */
    static void removeInstance();

public:
    Player* getPlayer();
    Aliens* getAliens();
    UFO*    getUFO();

public:
    bool playerHitCheck(int x, int y);
    bool bunkersHitCheck(int x, int y);

    bool hitCheck(Player* player);
    void calculateScore(int type);

private:
    bool hitCheck();
    bool handleHit();
    void handleUFO();

private:
    /*
     * @brief Default constructor
     */
    GameTable();

    /*
     * @brief Copy constructor
     */
    GameTable (const GameTable&) = delete;

    /*
     * @brief Copy assignment operator
     */
    GameTable& operator=(const GameTable&) = delete;

    /*
     * @brief Destructor
     */
    ~GameTable();

private:
    static GameTable* s_instance;

private:
    UFO*    m_ufo;
    Player* m_player;
    Aliens* m_aliens;

    UIManager* m_uiMgr;
    ConfigurationManager* m_confMgr;
};
