#pragma once

class UIManager;
class GameTable;
class ConfigurationManager;
class Counter;

class GameManager
{
public:
    static GameManager* getInstance();
    static GameManager* createInstance();
    static void removeInstance();

    static void staticHandler(int)
    {
        s_instance->handleTimer();
    }

public:
    GameManager();
    ~GameManager();
    void setup(int argc, char** argv);

private:
    GameManager(const GameManager& other) = delete;
    GameManager(GameManager&& other) = delete;

    GameManager& operator=(const GameManager& other) = delete;
    GameManager& operator=(GameManager&& other) = delete;

public:
    void readInput();

private:
    void printInfo() const;
    void printVersion() const;
    void printUsage() const;

    void parseCommandLine(int argc, char** argv);
    void setupTimer();
    void handleTimer();

private:
    void initLevel();
    void drawscore();

    void finish(int);

private:
    UIManager* m_uiMgr;
    ConfigurationManager* m_confMgr;
    GameTable* m_gameTable;

    friend class Counter;
    Counter* m_counter;

private:
    static GameManager* s_instance;

};

