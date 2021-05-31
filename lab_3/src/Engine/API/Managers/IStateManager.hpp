#pragma once

#include <memory>
#include "IManager.hpp"
#include "API/Scene/Scene.hpp"
#include "API/Objects/SceneObjectGroup.hpp"


class IStateManager : public IManager
{
public:
    virtual ~IStateManager() = default;

    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void saveState() = 0;

    virtual std::shared_ptr<Scene> getScene() = 0;
    virtual void setScene(std::shared_ptr<Scene> newScene) = 0;

    virtual std::shared_ptr<SceneObjectGroup> getSelection() = 0;
    virtual void setSelection(std::shared_ptr<SceneObjectGroup> newSelection) = 0;
};
