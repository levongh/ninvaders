#pragma once

#include <random>

static std::random_device device;
static std::mt19937 gen(device());

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
#define PLAYERPOSY (SCREENHEIGHT-2)

#define BUNKERWIDTH 80
#define BUNKERHEIGHT 4
#define BUNKERX 0
#define BUNKERY (SCREENHEIGHT-8)

#define ALIENS_MAX_NUMBER_X 10
#define ALIENS_MAX_NUMBER_Y 5
#define ALIENS_MAX_MISSILES 10

#define UFOWIDTH 5
#define UFOPOSY 0

namespace common {

static int alienBlock[ALIENS_MAX_NUMBER_Y][ALIENS_MAX_NUMBER_X];

static int bunker[BUNKERHEIGHT][BUNKERWIDTH + 1];

}
