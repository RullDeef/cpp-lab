#pragma once

#include <memory>
#include "ICommand.hpp"
#include "API/Managers/SceneManager.hpp"
#include "API/Managers/CameraManager.hpp"
#include "API/Managers/RenderManager.hpp"
#include "API/Managers/LoadManager.hpp"
#include "API/Managers/ObjectManager.hpp"
#include "API/Managers/TransformManager.hpp"
#include "API/Managers/SelectionManager.hpp"
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

    SetSceneCommand(SceneManager& manager, Scene* scene)
        : manager(manager), scene(scene) {}

    void execute() override { manager.setScene(scene); }

private:
    SceneManager& manager;
    std::shared_ptr<Scene> scene;
};

using RequestActiveCameraCommand = RequestCommand<CameraManager, Camera, (Camera& (CameraManager::*)())&CameraManager::getActiveCamera>;
using RequestConstActiveCameraCommand = RequestCommand<CameraManager, const Camera, (const Camera& (CameraManager::*)() const)&CameraManager::getActiveCamera>;

class UpdateSceneCameraCommand : public ICommand
{
public:
    UpdateSceneCameraCommand(CameraManager& manager, Scene& scene)
        : manager(manager), scene(scene) {}

    void execute() override { manager.setScene(scene); }

private:
    CameraManager& manager;
    Scene& scene;
};

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

class AddObjectCommand : public ICommand
{
public:
    AddObjectCommand(ObjectManager& manager, Scene& scene, IObject* object)
        : manager(manager), scene(scene), object(object) {}

    void execute() override { manager.addObject(scene, object); }

private:
    ObjectManager& manager;
    Scene& scene;
    IObject* object;
};

class RemoveObjectCommand : public ICommand
{
public:
    RemoveObjectCommand(ObjectManager& manager, Scene& scene, IObject* object)
        : manager(manager), scene(scene), object(object) {}

    void execute() override { manager.deleteObject(scene, object); }

private:
    ObjectManager& manager;
    Scene& scene;
    IObject* object;
};

class ClearSceneCommand : public ICommand
{
public:
    ClearSceneCommand(ObjectManager& manager, Scene& scene)
        : manager(manager), scene(scene) {}

    void execute() override { manager.clearScene(scene); }

private:
    ObjectManager& manager;
    Scene& scene;
};

template<void(TransformManager::* _Method)(IObject*, const Vector&)>
class BaseTransformCommand : public ICommand
{
public:
    BaseTransformCommand(TransformManager& manager, IObject* object, const Vector& vector)
        : manager(manager), object(object), vector(vector) {}

    void execute() override { (manager.*_Method)(object, vector); }

private:
    TransformManager& manager;
    IObject* object;
    const Vector& vector;
};

using TranslateObjectCommand = BaseTransformCommand<&TransformManager::translateObject>;
using RotateObjectCommand = BaseTransformCommand<&TransformManager::rotateObject>;
using ScaleObjectCommand = BaseTransformCommand<&TransformManager::scaleObject>;

template<void(SelectionManager::* _Method)(IObject*)>
class BaseSelectionCommand : public ICommand
{
public:
    BaseSelectionCommand(SelectionManager& manager, IObject* object)
        : manager(manager), object(object) {}

    void execute() override { (manager.*_Method)(object); }

private:
    SelectionManager& manager;
    IObject* object;
};

using SelectObjectCommand = BaseSelectionCommand<&SelectionManager::selectObject>;
using DeselectObjectCommand = BaseSelectionCommand<&SelectionManager::deselectObject>;
using ClearSelectionCommand = ManagerCommand<SelectionManager, &SelectionManager::clearSelection>;

class GetSelectionCommand : public ICommand
{
public:
    GetSelectionCommand(SelectionManager& manager, IObject*& selection)
        : manager(manager), selection(selection) {}

    void execute() override { selection = manager.getSelection(); }

private:
    SelectionManager& manager;
    IObject*& selection;
};
