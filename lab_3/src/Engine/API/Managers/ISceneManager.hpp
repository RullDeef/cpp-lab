#pragma once

#include "IManager.hpp"


class ISceneManager : public IManager
{
public:
    virtual ~ISceneManager() = default;

    virtual void createEmptyScene() = 0;
    virtual void loadScene() = 0;
};
