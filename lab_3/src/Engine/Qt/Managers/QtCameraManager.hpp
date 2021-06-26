#pragma once

#include "API/Managers/ICameraManager.hpp"
#include "API/Managers/IStateManager.hpp"
#include "API/Managers/ISelectionManager.hpp"
#include "API/Objects/Camera/CameraAdapter.hpp"


class QtCameraManager : public ICameraManager
{
public:
    QtCameraManager(std::shared_ptr<IStateManager> stateManager, std::shared_ptr<ISelectionManager> selectionManager);
    virtual ~QtCameraManager() = default;

    virtual std::shared_ptr<ICamera> getActiveCamera() override;
    virtual void switchActiveCamera() override;
    virtual void lookAtSelection() override;

private:
    std::shared_ptr<IStateManager> stateManager;
    std::shared_ptr<ISelectionManager> selectionManager;
    std::shared_ptr<ISceneObject> activeCamera = nullptr;
};
