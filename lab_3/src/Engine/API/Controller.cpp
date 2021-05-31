#include "Controller.hpp"
#include <algorithm>
#include "Engine/Utils/Logger.hpp"


Controller::Controller(std::shared_ptr<IManagerFactory> managerFactory)
{
    stateManager = managerFactory->createStateManager();
    sceneManager = managerFactory->createSceneManager(stateManager);
}

std::shared_ptr<IStateManager> Controller::getStateManager()
{
    return stateManager;
}

std::shared_ptr<ISceneManager> Controller::getSceneManager()
{
    return sceneManager;
}


/*
void Controller::renderScene(std::shared_ptr<IRenderer> renderer)
{
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
*/
