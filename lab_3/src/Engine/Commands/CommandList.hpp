#pragma once

#include <memory>
#include "ICommand.hpp"
#include "API/Managers/SceneManager.hpp"
#include "API/Managers/CameraManager.hpp"
#include "API/Managers/RenderManager.hpp"
#include "API/Managers/LoadManager.hpp"
#include "Scene/Scene.hpp"
#include "Objects/Camera/Camera.hpp"


class RenderSceneCommand : public ICommand
{
public:
    RenderSceneCommand(RenderManager& manager, const Scene& scene, const Camera& camera)
        : manager(manager), scene(scene), camera(camera) {}

    void execute() override { manager.renderScene(scene, camera); }

private:
    RenderManager& manager;
    const Scene& scene;
    const Camera& camera;
};

using RequestSceneCommand = RequestCommand<SceneManager, Scene, (Scene& (SceneManager::*)())&SceneManager::getScene>;
using RequestConstSceneCommand = RequestCommand<SceneManager, const Scene, (const Scene& (SceneManager::*)() const)&SceneManager::getScene>;

class SetSceneCommand : public ICommand
{
public:
    SetSceneCommand(SceneManager& manager, std::shared_ptr<Scene> scene)
        : manager(manager), scene(scene) {}

    void execute() override { manager.setScene(scene); }

private:
    SceneManager& manager;
    std::shared_ptr<Scene> scene;
};

using RequestActiveCameraCommand = RequestCommand<CameraManager, Camera, (Camera& (CameraManager::*)())&CameraManager::getActiveCamera>;
using RequestConstActiveCameraCommand = RequestCommand<CameraManager, const Camera, (const Camera& (CameraManager::*)() const)&CameraManager::getActiveCamera>;

using SwitchNextActiveCamera = ManagerCommand<CameraManager, &CameraManager::switchNextCamera>;
using SwitchPrevActiveCamera = ManagerCommand<CameraManager, &CameraManager::switchPrevCamera>;

class LoadEmptySceneCommand : public ICommand
{
public:
    LoadEmptySceneCommand(LoadManager& manager, Scene*& scene)
        : manager(manager), scene(scene) {}

    void execute() override { scene = manager.loadEmptyScene(); }

private:
    LoadManager& manager;
    Scene*& scene;
};
