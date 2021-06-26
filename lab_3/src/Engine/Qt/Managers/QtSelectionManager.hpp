#pragma once

#include "API/Managers/IStateManager.hpp"
#include "API/Managers/ISelectionManager.hpp"


class QtSelectionManager : public ISelectionManager
{
public:
    QtSelectionManager(std::shared_ptr<IStateManager> stateManager);
    virtual ~QtSelectionManager() = default;

    virtual void clearSelection() override;
    virtual std::shared_ptr<SceneObjectGroup> getSelected() override;

    virtual void toggleSelection(std::shared_ptr<ISceneObject> object) override;
    virtual void select(std::shared_ptr<ISceneObject> object) override;
    virtual void deselect(std::shared_ptr<ISceneObject> object) override;

private:
    std::shared_ptr<IStateManager> stateManager;
};
