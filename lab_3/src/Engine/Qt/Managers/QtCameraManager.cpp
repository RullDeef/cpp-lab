#include "QtCameraManager.hpp"

QtCameraManager::QtCameraManager(std::shared_ptr<IStateManager> stateManager, std::shared_ptr<ISelectionManager> selectionManager)
    : stateManager(stateManager), selectionManager(selectionManager)
{
}

std::shared_ptr<ICamera> QtCameraManager::getActiveCamera()
{
    if (!activeCamera)
    {
        switchActiveCamera();
        if (!activeCamera)
            return nullptr;
    }
    return (dynamic_cast<CameraAdapter*>(&*activeCamera))->getCamera();
}

void QtCameraManager::switchActiveCamera()
{
    auto scene = stateManager->getScene();
    for (auto& obj : *scene)
    {
        if (dynamic_cast<CameraAdapter*>(&*obj))
        {
            activeCamera = obj;
            break;
        }
    }
}

void QtCameraManager::lookAtSelection()
{

}
