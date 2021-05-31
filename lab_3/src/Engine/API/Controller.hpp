#pragma once

#include "API/Managers/IManagerFactory.hpp"


class Controller
{
public:
    Controller(std::shared_ptr<IManagerFactory> managerFactory);

    std::shared_ptr<IStateManager> getStateManager();
    std::shared_ptr<ISceneManager> getSceneManager();

private:
    std::shared_ptr<IStateManager> stateManager;
    std::shared_ptr<ISceneManager> sceneManager;
};
