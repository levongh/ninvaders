#include "GameManager.h"
#include "UIManager.h"

namespace {

void createSingletones()
{
    GameManager::createInstance();
    UIManager::createInstance();
}

void removeSingletones()
{
    GameManager::removeInstance();
    UIManager::removeInstance();
}

}

int main(int argc, char** argv)
{
    try {
        createSingletones();
        GameManager::getInstance()->setup(argc, argv);
    } catch (...) {
        removeSingletones();
    }

    GameManager* gameMgr = GameManager::getInstance();
    do {
        gameMgr->readInput();
    } while (true);

    removeSingletones();

    return 0;
}
