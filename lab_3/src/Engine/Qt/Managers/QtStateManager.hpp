#pragma once

#include "API/Managers/IStateManager.hpp"


class QtStateManager : public IStateManager
{
public:
    QtStateManager();
    virtual ~QtStateManager() = default;

    virtual void undo() override {}
    virtual void redo() override {}
    virtual void saveState() override {}

    virtual std::shared_ptr<Scene> getScene() override;
    virtual void setScene(std::shared_ptr<Scene> newScene) override;

    virtual std::shared_ptr<SceneObjectGroup> getSelection() override;
    virtual void setSelection(std::shared_ptr<SceneObjectGroup> newSelection) override;

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<SceneObjectGroup> selection;
};
