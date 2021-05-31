#pragma once

#include <memory>
#include "IStateManager.hpp"
#include "ISceneManager.hpp"


class IManagerFactory
{
public:
    virtual ~IManagerFactory() = default;

    virtual std::shared_ptr<IStateManager> createStateManager() = 0;
    virtual std::shared_ptr<ISceneManager> createSceneManager(std::shared_ptr<IStateManager> stateManager) = 0;
};
