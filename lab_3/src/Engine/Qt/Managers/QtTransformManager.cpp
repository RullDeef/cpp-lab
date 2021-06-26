#include "QtTransformManager.hpp"

QtTransformManager::QtTransformManager(std::shared_ptr<ISelectionManager> selectionManager)
    : selectionManager(selectionManager)
{
}

void QtTransformManager::transformSelected(const Transform& t)
{
    auto group = selectionManager->getSelected();

    for (auto& object : *group)
        object->getTransform().apply(t);
}
