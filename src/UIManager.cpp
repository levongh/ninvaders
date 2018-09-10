#include <iostream>

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

void UIManager::setupUI()
{
//	(void) signal(SIGINT, finish);	// <signal.h> on signal "SIGINT" call method "finish"
	(void) initscr();		// <curses.h> do initialization work 
	keypad(stdscr, TRUE);		// <curses.h> enable keypad for input
	(void) nonl();			// <curses.h> disable translation return/ newline for detection of return key
	(void) cbreak();		// <curses.h> do not buffer typed characters, use at once
	(void) noecho();		// <curses.h> do not echo typed characters
	start_color();			// <curses.h> use colors
	init_pair(static_cast<short>(Colour::RED), COLOR_RED, COLOR_BLACK);		// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::GREEN), COLOR_GREEN, COLOR_BLACK);	// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::YELLOW), COLOR_YELLOW, COLOR_BLACK);	// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::BLUE), COLOR_BLUE, COLOR_BLACK);	// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::CYAN), COLOR_CYAN, COLOR_BLACK);	// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::MAGENTA), COLOR_MAGENTA, COLOR_BLACK);	// <curses.h> define color-pair
	init_pair(static_cast<short>(Colour::WHITE), COLOR_WHITE, COLOR_BLACK);	// <curses.h> define color-pair

    // initialize sprites 
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

    wBattleField = newwin(SCREENHEIGHT, SCREENWIDTH, 0, 0);	// new window
    wclear(wBattleField);						// clear window
    mvwin(wBattleField, 0, 0);					// move window
}

void UIManager::playerInit()
{
    wPlayer = newpad(1, PLAYERWIDTH);       // new pad with appropriate size
    wclear(wPlayer);			// clear pad
    wattrset(wPlayer,COLOR_PAIR(Colour::YELLOW));	// set color
    waddstr(wPlayer,"/-^-\\");	        // set sprite
}

void UIManager::playerMissileInit()
{
    wPlayerMissile = newpad(1, 1);		// new pad with appropriate size
    wclear(wPlayerMissile);			// clear pad
    wattrset(wPlayerMissile,COLOR_PAIR(Colour::WHITE));	// set color
    waddch(wPlayerMissile,'!');		// set sprite
    wrefresh(wPlayerMissile);
}

void UIManager::aliensInit()
{
    wAliens = newpad(ALIENS_MAX_NUMBER_Y*2,ALIENS_MAX_NUMBER_X*3);
    wclear(wAliens);
}

void UIManager::aliensMissileInit()
{
    wAliensMissile = newpad(1, 1);		// new pad
    wclear(wAliensMissile);			// clear pad
    wattrset(wAliensMissile, COLOR_PAIR(Colour::CYAN));	// set color
    waddch(wAliensMissile, ':');			// set sprite
}

void UIManager::bunkersInit()
{
    wBunkers = newpad(BUNKERHEIGHT, BUNKERWIDTH);
    wclear(wBunkers);
}

void UIManager::ufoInit()
{
    wUfo = newpad(1, UFOWIDTH);	     // new pad with appropriate size
    wclear(wUfo);
    wattrset(wUfo, COLOR_PAIR(Colour::MAGENTA)); // set color
}

void UIManager::gameOverInit()
{
    // init game-over banner
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
	copywin(wEmpty,wBattleField,0,0,0,0,SCREENHEIGHT-1,SCREENWIDTH-1,0);
}

void UIManager::titleScreenDisplay()
{
	static int frame = 0;
	int x, y;
	int i;
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

	frame++;
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
	for (i = alien_type; i < alien_type + 3; i++) {
		waddstr(wAliens, "           ");
		snprintf(buffer, sizeof(buffer), "%s   = %d", aliens[frame % 2][i], score[i % 3]);
		wattrset(wAliens, COLOR_PAIR(colors[i]));
		waddstr(wAliens, buffer);
	}

	wStartText = newpad(1, 20);
	wclear(wStartText);
	wattrset(wStartText, COLOR_PAIR(Colour::RED));
	waddstr(wStartText, "Press SPACE to start");
	
	x = (SCREENWIDTH / 2) - (41 / 2);
	y = 0;
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
	copywin(wGameOver, wBattleField, 0, 0, y, x, y + 12, x + 30, 0);
	wrefresh(wBattleField);
}

void UIManager::refreshScreen()
{
    redrawwin(wBattleField); // needed to display graphics properly at startup on some terminals
    wrefresh(wBattleField);
}

void UIManager::playerMissileClear(int x, int y)
{
	copywin(wEmpty,wBattleField,0,0,y,x,y,x,0);
}

void UIManager::playerClear(int x, int y)
{
    copywin(wEmpty,wBattleField,0,0,y,x,y,x+PLAYERWIDTH-1,0);
}

void UIManager::playerDisplay(int x, int y)
{
    copywin(wPlayer,wBattleField,0,0,y,x,y,x+PLAYERWIDTH-1,0);
}

void UIManager::playerMissileDisplay(int x, int y)
{
	copywin(wPlayerMissile,wBattleField,0,0,y,x,y,x,0);
}

void UIManager::playerExplosionDisplay(int x, int y)
{
    WINDOW* wPlayerExplosion;
    char playerExplosionChars[16+1]="@~`.,^#*-_=\\/%{}";
    int t,s;

    wPlayerExplosion=newpad(1,PLAYERWIDTH);		// new pad
    wattrset(wPlayerExplosion,COLOR_PAIR(Colour::YELLOW));	// set color

    for(t=0;t<5;t++){			// 5 frames
        wclear(wPlayerExplosion);	// clear pad
        for(s=0;s<PLAYERWIDTH;s++){
            waddch(wPlayerExplosion,playerExplosionChars[rand()%16]);	// sprite
        }

        copywin(wPlayerExplosion,wBattleField,0,0,y,x,y,x+PLAYERWIDTH-1,0); 	// display explostion
        wrefresh(wBattleField);	// refresh battelfield to display explosion frames
        //doSleep(100000);		// play animation not too fast
    }
}
