#include <algorithm>
#include "SelectionManager.hpp"
#include "Utils/Logger.hpp"


void SelectionManager::selectObject(IObject* object)
{
    LOG_FUNC;

    if (!isObjectSelected(object))
        selection.insert(selection.end(), object);
}

void SelectionManager::deselectObject(IObject* object)
{
    LOG_FUNC;

    if (isObjectSelected(object))
    {
        auto iter = std::find(selection.begin(), selection.end(), object);
        selection.erase(iter);
    }
}

IObject* SelectionManager::getSelection()
{
    LOG_FUNC;

    return &selection;
}

const IObject* SelectionManager::getSelection() const
{
    LOG_FUNC;

    return &selection;
}

void SelectionManager::clearSelection()
{
    LOG_FUNC;

    selection.erase(selection.begin(), selection.end());
}

bool SelectionManager::isObjectSelected(const IObject* object) const
{
    return std::find(selection.begin(), selection.end(), object) != selection.end();
}
