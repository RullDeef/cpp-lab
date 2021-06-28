#include <stdexcept>
#include "CameraManager.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"


Camera& CameraManager::getActiveCamera()
{
    if (!activeCamera)
        throw std::runtime_error("CameraManager::getActiveCamera: invalid camera pointer");
    return *activeCamera;
}

const Camera& CameraManager::getActiveCamera() const
{
    if (!activeCamera)
        throw std::runtime_error("CameraManager::getActiveCamera: invalid camera pointer");
    return *activeCamera;
}

void CameraManager::setScene(Scene& newScene)
{
    scene = &newScene;

    for (auto& object : *scene)
    {
        if (auto camera = dynamic_cast<CameraAdapter*>(object))
        {
            activeCamera = &camera->getCamera();
            break;
        }
    }
}

void CameraManager::switchNextCamera()
{
    LOG_FUNC;
}

void CameraManager::switchPrevCamera()
{
    LOG_FUNC;
}
