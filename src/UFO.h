#pragma once

#include "Animate.h"

class UFO : public Animate
{
public:
    UFO();
    virtual void reset() override;
    void moveLeft();
    bool show();

private:
    void move(int posX);

private:
    bool m_toShow;
};

