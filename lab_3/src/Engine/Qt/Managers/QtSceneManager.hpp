#pragma once

#include <memory>
#include "API/Managers/IStateManager.hpp"
#include "API/Managers/ISceneManager.hpp"


class QtSceneManager : public ISceneManager
{
public:
    QtSceneManager(std::shared_ptr<IStateManager> stateManager);
    virtual ~QtSceneManager() = default;

    virtual void createEmptyScene() override;
    virtual void loadScene() override;

private:
    std::shared_ptr<IStateManager> stateManager;
};
