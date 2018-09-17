#include "UIManager.h"
#include "Animate.h"
#include "ConfigurationManager.h"

Animate::Animate()
    : m_uiMgr(UIManager::getInstance())
{
}

MovableAnimate::MovableAnimate()
    : Animate()
    , m_confMgr(ConfigurationManager::getInstance())
{
}
