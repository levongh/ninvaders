#include <iostream>
#include <chrono>
#include <thread>

#include "UIManager.h"

UIManager* UIManager::s_instance = nullptr;

UIManager* UIManager::getInstance()
{
    return createInstance();
}

UIManager* UIManager::createInstance()
{
    if (s_instance == nullptr) {
        s_instance = new UIManager();
    }
    return s_instance;
}

void UIManager::removeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

void UIManager::prepearInit()
{
    signal(SIGINT, finish);
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	start_color();
}

void UIManager::initPair()
{
    init_pair(static_cast<short>(Colour::RED), COLOR_RED, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::GREEN), COLOR_GREEN, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::YELLOW), COLOR_YELLOW, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::BLUE), COLOR_BLUE, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::CYAN), COLOR_CYAN, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::MAGENTA), COLOR_MAGENTA, COLOR_BLACK);
    init_pair(static_cast<short>(Colour::WHITE), COLOR_WHITE, COLOR_BLACK);
}

void UIManager::setupUI()
{
    prepearInit();
    initPair();

    battleFieldInit();
    playerInit();
    playerMissileInit();
    aliensInit();
    aliensMissileInit();
    bunkersInit();
    ufoInit();
    gameOverInit();
    statusInit();
    titleScreenInit();
}

void UIManager::battleFieldInit()
{
    wEmpty = newpad(SCREENHEIGHT, SCREENWIDTH);
    wclear(wEmpty);

    wBattleField = newwin(SCREENHEIGHT, SCREENWIDTH, 0, 0);
    wclear(wBattleField);
    mvwin(wBattleField, 0, 0);
}

void UIManager::playerInit()
{
    wPlayer = newpad(1, PLAYERWIDTH);
    wclear(wPlayer);
    wattrset(wPlayer,COLOR_PAIR(Colour::YELLOW));
    waddstr(wPlayer,"/-^-\\");
}

void UIManager::playerMissileInit()
{
    wPlayerMissile = newpad(1, 1);
    wclear(wPlayerMissile);
    wattrset(wPlayerMissile,COLOR_PAIR(Colour::WHITE));
    waddch(wPlayerMissile,'!');
    wrefresh(wPlayerMissile);
}

void UIManager::aliensInit()
{
    wAliens = newpad(ALIENS_MAX_NUMBER_Y * 2,
                     ALIENS_MAX_NUMBER_X * 3);
    wclear(wAliens);
}

void UIManager::aliensMissileInit()
{
    wAliensMissile = newpad(1, 1);
    wclear(wAliensMissile);
    wattrset(wAliensMissile, COLOR_PAIR(Colour::CYAN));
    waddch(wAliensMissile, ':');
}

void UIManager::bunkersInit()
{
    wBunkers = newpad(BUNKERHEIGHT, BUNKERWIDTH);
    wclear(wBunkers);
}

void UIManager::ufoInit()
{
    wUfo = newpad(1, UFOWIDTH);
    wclear(wUfo);
    wattrset(wUfo, COLOR_PAIR(Colour::MAGENTA));
}

void UIManager::gameOverInit()
{
    wGameOver = newpad(13, 31);
    wclear(wGameOver);
    wattrset(wGameOver, COLOR_PAIR(Colour::WHITE));
    waddstr(wGameOver, "                               ");
    waddstr(wGameOver, "  #####   ####  ##   ## ###### ");
    waddstr(wGameOver, " ##      ##  ## ####### ##     ");
    waddstr(wGameOver, " ## ###  ###### ## # ## #####  ");
    waddstr(wGameOver, " ##  ##  ##  ## ##   ## ##     ");
    waddstr(wGameOver, "  #####  ##  ## ##   ## ###### ");
    waddstr(wGameOver, "                               ");
    waddstr(wGameOver, "  ####  ##   ## ###### ######  ");
    waddstr(wGameOver, " ##  ## ##   ## ##     ##   ## ");
    waddstr(wGameOver, " ##  ##  ## ##  #####  ######  ");
    waddstr(wGameOver, " ##  ##  ## ##  ##     ##  ##  ");
    waddstr(wGameOver, "  ####    ###   ###### ##   ## ");
    waddstr(wGameOver, "                               ");
}

void UIManager::statusInit()
{
    wStatus = newpad(1, 55);
    wclear(wStatus);
}

void UIManager::titleScreenInit()
{
    wTitleScreen = newpad(SCREENHEIGHT, SCREENWIDTH);
    wclear(wTitleScreen);
}

void UIManager::titleScreenClear()
{
    battleFieldClear();
}

void UIManager::battleFieldClear()
{
	copywin(wEmpty, wBattleField,
            0, 0, 0, 0,
            SCREENHEIGHT - 1,
            SCREENWIDTH - 1, 0);
}

void UIManager::titleScreenDisplay()
{
	static int frame = 0;
	WINDOW *wTitleText;
	WINDOW *wAliens;
	WINDOW *wStartText;
	char ufo[4][6] = {"<o o>", "<oo >", "<o o>", "< oo>"};
	char aliens[2][9][3+1] = {
		{",^,", "_O-", "-o-",  "o=o", "<O>", "_x_", "*^*", "\\_/", "o o"},
		{".-.", "-O_", "/o\\", "o-o", "<o>", "-x-", "o^o", "/~\\", "oo "}
	};
	int score[3] = {200, 150, 100};
	int colors[9] = {static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE),
                     static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE),
                     static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE)
                    };
	char buffer[12];
	static int alien_type = 0;

	wTitleText = newpad(4, 41);
	wclear(wTitleText);
	wattrset(wTitleText, COLOR_PAIR(Colour::YELLOW));
	waddstr(wTitleText, "        ____                 __          ");
	waddstr(wTitleText, "  ___  /  _/__ _  _____  ___/ /__ _______");
    waddstr(wTitleText, " / _ \\_/ // _ \\ |/ / _ `/ _  / -_) __(_-<");
	waddstr(wTitleText, "/_//_/___/_//_/___/\\_,_/\\_,_/\\__/_/ /___/");

	++frame;
	wAliens = newpad(7, 11);
	wclear(wAliens);
	snprintf(buffer, sizeof(buffer),"%s = 500", ufo[frame % 4]);
	wattrset(wAliens, COLOR_PAIR(Colour::MAGENTA));
	waddstr(wAliens, buffer);
	if ((frame = frame % 60) == 0) {
		alien_type = 0;
	} else if (frame == 20) {
		alien_type = 3;
	} else if (frame == 40) {
		alien_type = 6;
	}
	for (int i = alien_type; i < alien_type + 3; i++) {
		waddstr(wAliens, "           ");
		snprintf(buffer, sizeof(buffer), "%s   = %d", aliens[frame % 2][i], score[i % 3]);
		wattrset(wAliens, COLOR_PAIR(colors[i]));
		waddstr(wAliens, buffer);
	}

	wStartText = newpad(1, 20);
	wclear(wStartText);
	wattrset(wStartText, COLOR_PAIR(Colour::RED));
	waddstr(wStartText, "Press SPACE to start");

	int x = (SCREENWIDTH / 2) - (41 / 2);
	int y = 0;
	copywin(wTitleText, wTitleScreen, 0, 0, y, x, y + 3, x + 40, 0);

	x = (SCREENWIDTH / 2) - (11 / 2);
	y = 8;
	copywin(wAliens, wTitleScreen, 0, 0, y, x , y + 6, x + 10, 0);

	x = (SCREENWIDTH / 2) - (20 / 2);
	y = SCREENHEIGHT - 2;
	copywin(wStartText, wTitleScreen, 0, 0, y, x, y, x + 19, 0);

	copywin(wTitleScreen, wBattleField, 0, 0, 0, 0, SCREENHEIGHT-1, SCREENWIDTH-1, 0);

	wrefresh(wBattleField);
}

void UIManager::gameOverDisplay()
{
	int x = (SCREENWIDTH / 2) - (31 / 2);
	int y = (SCREENHEIGHT / 2) - (13 / 2);
	copywin(wGameOver, wBattleField,
            0, 0, y, x, y + 12, x + 30, 0);
	wrefresh(wBattleField);
}

void UIManager::refreshScreen()
{
    redrawwin(wBattleField);
    wrefresh(wBattleField);
}

void UIManager::playerMissileClear(int x, int y)
{
	copywin(wEmpty, wBattleField,
            0, 0, y, x, y, x, 0);
}

void UIManager::playerClear(int x, int y)
{
    copywin(wEmpty, wBattleField,
            0, 0, y, x, y, x + PLAYERWIDTH - 1, 0);
}

void UIManager::playerDisplay(int x, int y)
{
    copywin(wPlayer, wBattleField,
            0, 0, y, x, y, x + PLAYERWIDTH - 1, 0);
}

void UIManager::playerMissileDisplay(int x, int y)
{
	copywin(wPlayerMissile, wBattleField,
            0, 0, y, x, y, x, 0);
}

void UIManager::playerExplosionDisplay(int x, int y)
{
    WINDOW* wPlayerExplosion;
    char playerExplosionChars[16+1]="@~`.,^#*-_=\\/%{}";

    wPlayerExplosion=newpad(1,PLAYERWIDTH);
    wattrset(wPlayerExplosion,COLOR_PAIR(Colour::YELLOW));	// set color

    for(int t = 0; t < 5; ++t) {
        wclear(wPlayerExplosion);
        for(int s = 0; s < PLAYERWIDTH; ++s) {
            waddch(wPlayerExplosion,playerExplosionChars[rand()%16]);
        }
        copywin(wPlayerExplosion, wBattleField,
                0, 0, y, x, y, x + PLAYERWIDTH - 1, 0);
        wrefresh(wBattleField);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void UIManager::aliensDisplay(int x, int y, int wid, int hgt)
{
    copywin(wAliens, wBattleField,
            0, 0, y, x, y + hgt, x + wid + 2, 0);
}

void UIManager::aliensClear(int x, int y, int wid, int hgt)
{
    copywin(wEmpty, wBattleField,
            0, 0, y, x, y + hgt, x + wid + 2, 0);
}

void UIManager::aliensMissileDisplay(int x, int y)
{
    copywin(wAliensMissile, wBattleField,
            0, 0, y, x, y, x, 0);
}

void UIManager::aliensMissileClear(int x, int y)
{
    copywin(wEmpty, wBattleField,
            0, 0, y, x, y, x, 0);
}

void UIManager::aliensRefresh(int level, int *pAliens)
{
    static int frame = 0; // used for animation; mod 2 == 0: frame1, mod2 == 1: frame2
    int c = 0;
    int alienType = 0;
    char ships[2][9][3 + 1] = {
        {",^,", "_O-", "-o-",  "o=o", "<O>", "_x_", "*^*", "\\_/", "o o"},
        {".-.", "-O_", "/o\\", "o-o", "<o>", "-x-", "o^o", "/~\\", "oo "}
    };
	int colors[9] = {static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE),
                     static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE),
                     static_cast<short>(Colour::RED),
                     static_cast<short>(Colour::GREEN),
                     static_cast<short>(Colour::BLUE)
                    };

    wclear(wAliens);
    wattrset(wAliens, COLOR_PAIR(Colour::RED));
    ++frame;
    for (int row = 0; row < ALIENS_MAX_NUMBER_Y * 2; ++row) {
        for (int k = 0; k < ALIENS_MAX_NUMBER_X; ++k) {
            if ((row % 2) == 0) {
                alienType = *(pAliens + c * (ALIENS_MAX_NUMBER_X) + k);
                if (alienType != 0) {
                    wattrset(wAliens, COLOR_PAIR(colors[alienType - 1]));
                    waddch(wAliens,
                            ships[frame % 2][alienType -1 +(3 * ((level - 1) % 3))][0]);
                    waddch(wAliens,
                            ships[frame % 2][alienType -1 +(3 * ((level - 1) % 3))][1]);
                    waddch(wAliens,
                            ships[frame % 2][alienType -1 +(3 * ((level - 1) % 3))][2]);
                    if (alienType > 4) {
                        *(pAliens + c * ALIENS_MAX_NUMBER_X + k) = (alienType + 1) % 9;
                    }
                } else {
                    waddstr(wAliens,"   ");
                }
            } else {
                waddstr(wAliens,"   ");
            }
        }
        if ((row % 2) == 1) {++c;}
    }
}

void UIManager::bunkersClear()
{
    copywin(wEmpty, wBattleField,
            0, 0, BUNKERY, BUNKERX, BUNKERY + BUNKERHEIGHT - 1, BUNKERX + BUNKERWIDTH - 1, 0);
}

void UIManager::bunkersClearElement(int x, int y)
{
	copywin(wEmpty, wBattleField,
            0, 0, y, x, y, x, 0);
}

void UIManager::bunkersDisplay(int *pBunker)
{
    wclear(wBunkers);
    wattrset(wBunkers,COLOR_PAIR(Colour::CYAN));
    for (int l = 0; l < BUNKERHEIGHT; ++l) {
        for (int k = 0; k < BUNKERWIDTH; ++k) {
            if (*(pBunker + (l * (BUNKERWIDTH + 1)) + k) == 1) {
                waddch(wBunkers,'#');
            } else {
                waddch(wBunkers,' ');
            }
        }
    }
    copywin(wBunkers, wBattleField,
            0, 0, BUNKERY, BUNKERX, BUNKERY + BUNKERHEIGHT - 1, BUNKERX + BUNKERWIDTH - 1, 0);
}

void UIManager::finish(int sig)
{
	endwin();
    std::exit(0);
}


void UIManager::ufoRefresh()
{
	char ufo[4][6] = {"<o o>", "<oo >", "<o o>", "< oo>"};
	static int frame = 0;

	wclear(wUfo);
    wattrset(wUfo, COLOR_PAIR(Colour::MAGENTA));
	waddstr(wUfo, ufo[frame % 4]);
	++frame;
}

void UIManager::ufoDisplay(int x, int y)
{
	copywin(wUfo, wBattleField,
            0, 0, y, x, y, x + UFOWIDTH - 1, 0);
}

void UIManager::ufoClear(int x, int y)
{
	copywin(wEmpty, wBattleField,
            0, 0, y, x, y, x + UFOWIDTH - 1, 0);
}

void UIManager::statusDisplay(int level, int score, int lives)
{
    char strStatus[55];

    int xOffset = (SCREENWIDTH / 2) - 24;

    sprintf(strStatus, "Level: %2.2d Score: %2.7d Lives: ", level, score);

    wclear(wStatus);
    wattrset(wStatus, COLOR_PAIR(Colour::RED));
    waddstr(wStatus, strStatus);

    for (int t = 1; ((t <= 5) && (t < lives)); t++){
        waddstr(wStatus, "/-\\ ");
    }
    copywin(wStatus, wBattleField,
            0, 0, SCREENHEIGHT-1, xOffset, SCREENHEIGHT - 1, xOffset + 54, 0);
}
