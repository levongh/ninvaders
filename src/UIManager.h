#pragma once

#include <ncurses.h>
#include <signal.h>

enum class Colour : short
{
    RED     = 1,
    GREEN   = 2,
    YELLOW  = 3,
    BLUE    = 4,
    CYAN    = 5,
    MAGENTA = 6,
    WHITE   = 7
};

#define SCREENHEIGHT 24
#define SCREENWIDTH 80	
	
#define PLAYERWIDTH 5
//#define PLAYERPOSY (SCREENHEIGHT-2)
//
#define BUNKERWIDTH 80
#define BUNKERHEIGHT 4
//#define BUNKERX 0
//#define BUNKERY (SCREENHEIGHT-8)
//	
#define ALIENS_MAX_NUMBER_X 10
#define ALIENS_MAX_NUMBER_Y 5
//
#define UFOWIDTH 5
//#define UFOPOSY 0
//

class UIManager
{
public:
    static UIManager* getInstance();
    static UIManager* createInstance();
    static void removeInstance();

public:
    UIManager() = default;
    void setupUI();

private:
    UIManager (const UIManager& other) = delete;
    UIManager (UIManager&& other) = delete;

    UIManager& operator=(const UIManager& other) = delete;
    UIManager& operator=(UIManager&& other) = delete;

public:
    void titleScreenDisplay();
    void titleScreenClear();
    void battleFieldClear();
    void gameOverDisplay();
    void refreshScreen();
    void playerMissileClear(int x, int y);
    void playerClear(int x, int y);
    void playerDisplay(int x, int y);
    void playerExplosionDisplay(int x, int y);
    void playerMissileDisplay(int x, int y);

private:
    void battleFieldInit();
    void playerInit();
    void playerMissileInit();
    void aliensInit();
    void aliensMissileInit();
    void bunkersInit();
    void ufoInit();
    void gameOverInit();
    void statusInit();
    void titleScreenInit();

private:
    static UIManager* s_instance;

private:
    WINDOW *wBattleField;
    WINDOW *wEmpty;
    WINDOW *wScores;

    WINDOW *wPlayer;
    WINDOW *wPlayerMissile;
    WINDOW *wAliens;
    WINDOW *wAliensMissile;
    WINDOW *wBunkers;
    WINDOW *wGameOver;
    WINDOW *wUfo;
    WINDOW *wStatus;
    WINDOW *wTitleScreen;
};


