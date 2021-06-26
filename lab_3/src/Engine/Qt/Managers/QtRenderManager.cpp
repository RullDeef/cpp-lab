#include "QtRenderManager.hpp"
#include "API/Objects/Camera/PerspectiveCamera.hpp"
#include "Qt/Renderer/QtRenderer.hpp"

// #include "APIdefaulthullube builder!!! tes moc"
#include "API/Objects/Builders/DefaultHullCubeBuilder.hpp"
#include "API/Objects/Builders/TransformBuilder.hpp"


static std::shared_ptr<PerspectiveCamera> perspCam;


QtRenderManager::QtRenderManager(std::shared_ptr<IStateManager> stateManager, std::shared_ptr<IRenderer> renderer)
    : stateManager(stateManager), renderer(renderer)
{
    

    perspCam = std::make_shared<PerspectiveCamera>();
    perspCam->setViewport(((QtRenderer*)&*renderer)->getViewport());
    perspCam->setNear(0.1);
    perspCam->setFar(1000.0);
    perspCam->setFov(75.0 * 3.1415926535 / 180);

    perspCam->setViewMatrix(Matrix::translation({ 0.0, 0.0, 10.0 }));
}

void QtRenderManager::renderScene()
{
    auto scene = stateManager->getScene();
    IRenderer* rendererPtr = &*renderer;

    perspCam->setViewport(((QtRenderer*)&*renderer)->getViewport());

    renderer->beginFrame(&*perspCam);
    for (auto& obj : *scene)
        obj->accept(rendererPtr);
    renderer->endFrame();
}
