#include "CameraManager.hpp"
#include "API/Objects/Camera/PerspectiveCamera.hpp"
#include "API/Objects/Camera/CameraAdapter.hpp"
#include "Utils/Logger.hpp"


static std::shared_ptr<PerspectiveCamera> perspCam;

CameraManager::CameraManager(std::shared_ptr<SceneManager> sceneManager)
    : sceneManager(sceneManager)
{
    perspCam = std::make_shared<PerspectiveCamera>();

    //perspCam->setViewport(((QtRenderer*)&*renderer)->getViewport());

    perspCam->setNear(0.1);
    perspCam->setFar(1000.0);
    perspCam->setFov(75.0 * 3.1415926535 / 180);

    perspCam->setViewMatrix(Matrix::translation({ 0.0, 0.0, 10.0 }));
}

std::shared_ptr<ICamera> CameraManager::getActiveCamera()
{
    return perspCam;
}

void CameraManager::switchActiveCamera()
{
    LOG_FUNC;
}
