#pragma once

#include "IManager.hpp"
#include "API/Objects/SceneObjectGroup.hpp"


class ISelectionManager : public IManager
{
public:
    virtual void clearSelection() = 0;
    virtual std::shared_ptr<SceneObjectGroup> getSelected() = 0;
    
    virtual void toggleSelection(std::shared_ptr<ISceneObject> object) = 0;
    virtual void select(std::shared_ptr<ISceneObject> object) = 0;
    virtual void deselect(std::shared_ptr<ISceneObject> object) = 0;
};
