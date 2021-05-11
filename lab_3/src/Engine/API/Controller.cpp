#include "Controller.hpp"
#include "Scene/PerspectiveCamera.hpp"
#include "../Tools/Logger.hpp"

Controller::Controller()
{
}

void Controller::createEmptyScene()
{
    LOG_FUNC;

    sceneManager.createEmptyScene();
}

void Controller::loadScene(const char* filename)
{
    LOG_FUNC;

    sceneManager.loadScene(filename);
}

bool Controller::addSceneObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    return sceneManager.addSceneObject(object);
}

void Controller::renderScene(std::shared_ptr<IRenderer> renderer)
{
    LOG_FUNC;

    PerspectiveCamera* perspCam = new PerspectiveCamera();
    perspCam->setViewport(renderer->getViewport());
    perspCam->setNear(0.1);
    perspCam->setFar(1000.0);
    perspCam->setFov(75.0 * 3.1415926535 / 180);

    perspCam->getTransform().translate({ 0.0, 0.0, 10.0 });

    std::shared_ptr<ICamera> camera = std::shared_ptr<ICamera>(perspCam);

    renderer->clear(Color(0xFF, 0xFF, 0xFF, 0xFF));
    sceneManager.renderScene(renderer, camera);
}
