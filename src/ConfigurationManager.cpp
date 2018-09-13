#include "ConfigurationManager.h"

ConfigurationManager* ConfigurationManager::s_instance = nullptr;

ConfigurationManager* ConfigurationManager::getInstance()
{
    if (nullptr == s_instance) {
        s_instance = new ConfigurationManager();
    }
    return s_instance;
}

void ConfigurationManager::removeInstance()
{
    delete s_instance;
    s_instance = nullptr;
}

ConfigurationManager::~ConfigurationManager()
{
}
