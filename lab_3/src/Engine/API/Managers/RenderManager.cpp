#include "RenderManager.hpp"
// #include "RenderManager.hpp"
// #include "API/Objects/Camera/PerspectiveCamera.hpp"
// #include "Qt/Renderer/QtRenderer.hpp"
// #include "APIdefaulthullube builder!!! tes moc"
// #include "API/Objects/Builders/DefaultHullCubeBuilder.hpp"
// #include "API/Objects/Builders/TransformBuilder.hpp"


RenderManager::RenderManager(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<CameraManager> cameraManager, std::shared_ptr<IRenderer> renderer)
    : renderer(renderer), sceneManager(sceneManager), cameraManager(cameraManager)
{
}

void RenderManager::renderScene()
{
    IRenderer* rendererPtr = &*renderer;

    auto scene = sceneManager->getScene();
    auto camera = cameraManager->getActiveCamera();
    camera->setViewport(renderer->getViewport());

    renderer->beginFrame(&*camera);
    for (const auto& obj : scene)
        obj->accept(rendererPtr);
    renderer->endFrame();
}
