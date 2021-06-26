#pragma once

#include "API/Managers/IObjectManager.hpp"
#include "API/Managers/IStateManager.hpp"


class QtObjectManager : public IObjectManager
{
public:
    explicit QtObjectManager(std::shared_ptr<IStateManager> stateManager);
    virtual ~QtObjectManager() = default;

    virtual void addObject(std::shared_ptr<ISceneObject> object) override;
    virtual void removeObject(std::shared_ptr<ISceneObject> object) override;

    virtual void removeAllObjects() override;

private:
    std::shared_ptr<IStateManager> stateManager;
};
