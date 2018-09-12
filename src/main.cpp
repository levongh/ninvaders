#include <iostream>
#include <stdexcept>

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
        GameManager* gameMgr = GameManager::getInstance();
        gameMgr->setup(argc, argv);

        do {
            gameMgr->readInput();
        } while (true);
        removeSingletones();

    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        removeSingletones();
    } catch (...) {
        removeSingletones();
        std::exit(0);
    }

    return 0;
}
