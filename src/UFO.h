#pragma once

#include "Animate.h"

class UFO : public Animate
{
public:
    UFO();
    virtual void reset() override;
    void moveLeft();
    int show();

private:
    void move(int posX);

private:
    bool toShow;
};

