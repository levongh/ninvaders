#pragma once

#include <ncurses.h>
#include <signal.h>

#include "common.h"

/**
 * @brief UIManager class which based on ncurses lib and does specific objects drowing
 * @author Levon Ghukasyan
 **/

class UIManager
{
    ///@brief static functionality
    ///@{
public:
    static UIManager* getInstance();
    static UIManager* createInstance();
    static void removeInstance();
    ///@}

    ///@brief
    ///@{
public:
    UIManager() = default;
    void setupUI();
    ///@}

    ///@brief private constructors and assignmnt operats
    ///{
private:
    UIManager (const UIManager& other) = delete;
    UIManager (UIManager&& other) = delete;

    UIManager& operator=(const UIManager& other) = delete;
    UIManager& operator=(UIManager&& other) = delete;
    ///@}

    ///@brief initalization functionalities
    ///@
public:
    void titleScreenDisplay();
    void titleScreenClear();
    void battleFieldClear();
    void gameOverDisplay();
    void refreshScreen();
    ///@}

    ///@brief player specific functionalities
    ///@{
public:
    void playerMissileClear(int x, int y);
    void playerClear(int x, int y);
    void playerDisplay(int x, int y);
    void playerExplosionDisplay(int x, int y);
    void playerMissileDisplay(int x, int y);
    ///@}

    ///@brief aliens specific functionalities
    ///@{
public:
    void aliensDisplay(int x, int y, int wid, int hgt);
    void aliensClear(int x, int y, int wid, int hgt);
    void aliensMissileDisplay(int x, int y);
    void aliensMissileClear(int x, int y);
    void aliensRefresh(int level, int *pAliens);
    ///@}

    ///@brief bunker Specific functionalities
    ///@{
public:
    void bunkersClear();
    void bunkersClearElement(int x, int y);
    void bunkersDisplay(int *pBunker);
    ///@}

    ///@brief UFO specific functionalities
    ///@{
public:
    void ufoRefresh();
    void ufoDisplay(int x, int y);
    void ufoClear(int x, int y);
    void statusDisplay(int level, int score, int lives);
    ///@}

public:
    static void finish(int);

private:
    void prepearInit();
    void initPair();
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


