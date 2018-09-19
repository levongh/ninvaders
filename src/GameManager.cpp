#include <stdexcept>
#include <cstdio>
#include <sys/time.h>

#include "ConfigurationManager.h"

#include "UIManager.h"
#include "Player.h"
#include "Aliens.h"
#include "GameManager.h"
#include "GameTable.h"
#include "Counter.h"

GameManager* GameManager::s_instance = nullptr;

GameManager::GameManager()
{
    m_uiMgr = UIManager::getInstance();
    m_confMgr = ConfigurationManager::getInstance();
    m_gameTable = GameTable::createInstance();
    m_counter = new Counter(this);
}

GameManager::~GameManager()
{
    GameTable::removeInstance();
    delete m_counter;
}

GameManager* GameManager::getInstance()
{
    return createInstance();
}

GameManager* GameManager::createInstance()
{
    if (s_instance == nullptr) {
        s_instance = new GameManager();
    }
    return s_instance;
}

void GameManager::removeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

void GameManager::setup(int argc, char** argv)
{
    m_confMgr->reset();

    parseCommandLine(argc, argv);
    UIManager::getInstance()->setupUI();
    setupTimer();
	m_confMgr->setMode(Mode::HIGHSCORE);
}

void GameManager::setupTimer()
{
    struct itimerval myTimer;
    struct sigaction myAction;
    myTimer.it_value.tv_sec = 0;
    myTimer.it_value.tv_usec = 1000000 / FPS;
    myTimer.it_interval.tv_sec = 0;
    myTimer.it_interval.tv_usec = 1000000 / FPS;
    setitimer(ITIMER_REAL, &myTimer, NULL);

    myAction.sa_handler = &GameManager::staticHandler;
    myAction.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &myAction, NULL);
}

void GameManager::handleTimer()
{
    switch (m_confMgr->getMode()) {
        case Mode::NEXT_LEVEL:
            m_confMgr->setLevel(1 + m_confMgr->getLevel());
            initLevel();
            m_counter->reset();
            m_confMgr->updateWeite();
            m_confMgr->setMode(Mode::LOOP);
        case Mode::LOOP:
            m_counter->checkAliensMove();
            m_counter->checkPlayerShot();
            m_counter->checkAliensShot();
            m_counter->checkUFO();
            m_counter->updateCounter();

            m_uiMgr->refreshScreen();
            break;
        case Mode::PAUSE:
            break;
        case Mode::GAME_OVER:
            m_counter->checkGameOver();
            break;
        case Mode::EXIT:
            finish(0);
            break;
        case Mode::HIGHSCORE:
            m_counter->animationUpdate();
            break;
    }
}

void GameManager::parseCommandLine(int argc, char** argv)
{
    if (argc == 3 && argv[1] == "-l") {
        if (argv[2][0] >= '0' && argv[2][0] <= '9') {
            m_confMgr->setSkillLevel(argv[2][0] - 48);
        } else {
            argc = 2;
        }
    }
    if(argc == 2 && argv[1] == "-i") {
        printInfo();
    }
    if (argc == 2 || (argc == 3 && argv[1] == "-l")) {
        printVersion();
        printUsage();
        throw std::invalid_argument("Command line arguments are wrong");
    }
}

void GameManager::drawscore()
{
	m_uiMgr->statusDisplay(m_confMgr->getLevel(),
                         m_confMgr->getScore(),
                         m_confMgr->getLive());
}

void GameManager::printInfo() const
{
}

void GameManager::printVersion() const
{
}

void GameManager::printUsage() const
{
}

void GameManager::initLevel()
{
    m_gameTable->getPlayer()->reset();
    m_gameTable->getAliens()->reset();
    m_gameTable->getUFO()->reset();
	m_gameTable->getAliens()->bunkersReset();
	m_gameTable->getAliens()->render();
	drawscore();
}

void GameManager::readInput()
{
    int ch;
    static int lastmove;
    ch = getch();		// get key pressed
    switch (m_confMgr->getMode()) {
        case Mode::PAUSE:
            if (ch == 'p') {
                m_confMgr->setMode(Mode::LOOP);
            }
            break;
        case Mode::HIGHSCORE:
            if (ch == ' ') {
                m_uiMgr->titleScreenClear();
                m_confMgr->setLevel(0);
                m_confMgr->setScore(0);
                m_confMgr->setLive(3);
                m_confMgr->setMode(Mode::NEXT_LEVEL);
            } else if (ch == 'q') {
                m_confMgr->setMode(Mode::EXIT);
            }
            break;
        case Mode::GAME_OVER:
            break;
        default:
            auto player = m_gameTable->getPlayer();
            if (ch == 'l' || ch == KEY_RIGHT) {
                if (lastmove == 'l') {
                    player->turboOn();
                } else {
                    player->turboOff();
                }
                player->moveRight();
                lastmove = 'l';
            } else if (ch == 'h' || ch == KEY_LEFT) {
                if (lastmove == 'h') {
                    player->turboOn();
                } else {
                    player->turboOff();
                }
                player->moveLeft();
                lastmove = 'h';
            } else if (ch == 'k' || ch == ' ') {
                player->fire();
            } else if (ch == 'p') {
                m_confMgr->setMode(Mode::PAUSE);
            } else if (ch == 'W') {
                m_confMgr->setMode(Mode::NEXT_LEVEL);
            } else if (ch == 'L') {
                m_confMgr->setLive(1 + m_confMgr->getLive());
                drawscore();
            } else if (ch == 'q') {
                m_confMgr->setMode(Mode::EXIT);
            } else {
                lastmove = ' ';
            }
    }
}

void GameManager::finish(int)
{
    endwin();
    printVersion();
    throw CloseProgramm("Closing pogramm");
}

