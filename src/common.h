#pragma once

#include <random>
#include <string>
#include <exception>

struct CloseProgramm : public std::exception
{
public:
    explicit CloseProgramm(const std::string& what)
        : m_message(what.c_str())
    {
    }

    explicit CloseProgramm(const char* what)
        : m_message(what)
    {
    }

    virtual const char* what() const noexcept override
    {
        return m_message;
    }

private:
    const char* m_message;
};

static std::random_device device;
static std::mt19937 gen(device());

enum class Mode : unsigned
{
    LOOP       = 1,
    NEXT_LEVEL = 2,
    PAUSE      = 3,
    GAME_OVER  = 4,
    EXIT       = 5,
    HIGHSCORE  = 6
};

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

static const int SCREENHEIGHT = 24;
static const int SCREENWIDTH  = 80;
static const int PLAYERWIDTH  = 5;
static const int PLAYERPOSY   = SCREENHEIGHT - 2;
static const int BUNKERWIDTH  = 80;
static const int BUNKERHEIGHT = 4;
static const int BUNKERX      = 0;
static const int BUNKERY      = SCREENHEIGHT - 8;
static const int UFOWIDTH     = 5;
static const int UFOPOSY      = 0;
static const int FPS          = 50;

static const int UFO_ALIEN_TYPE   = 0;
static const int RED_ALIEN_TYPE   = 1;
static const int GREEN_ALIEN_TYPE = 2;
static const int BLUE_ALIEN_TYPE  = 3;

static const int ALIENS_MAX_NUMBER_X = 10;
static const int ALIENS_MAX_NUMBER_Y = 5;
static const int ALIENS_MAX_MISSILES = 10;


extern int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];

extern int bunker[BUNKERHEIGHT][BUNKERWIDTH + 1];
