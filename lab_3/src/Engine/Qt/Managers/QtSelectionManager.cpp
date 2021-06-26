#include "QtSelectionManager.hpp"

QtSelectionManager::QtSelectionManager(std::shared_ptr<IStateManager> stateManager)
    : stateManager(stateManager)
{
}

void QtSelectionManager::clearSelection()
{
    auto selection = stateManager->getSelection();
    while (*selection->begin())
        selection->removeChild(*selection->begin());
}

std::shared_ptr<SceneObjectGroup> QtSelectionManager::getSelected()
{
    return stateManager->getSelection();
}

void QtSelectionManager::toggleSelection(std::shared_ptr<ISceneObject> object)
{
    auto selection = stateManager->getSelection();
    bool contains = false;

    for (auto& obj : *selection)
    {
        if (obj.get() == object.get())
        {
            contains = true;
            break;
        }
    }

    if (contains)
        selection->removeChild(object);
    else
        selection->addChild(object);
}

void QtSelectionManager::select(std::shared_ptr<ISceneObject> object)
{
    stateManager->getSelection()->addChild(object);
}

void QtSelectionManager::deselect(std::shared_ptr<ISceneObject> object)
{
    stateManager->getSelection()->removeChild(object);
}
