#include "LoadManager.hpp"
#include "Creators/Directors/EmptySceneDirector.hpp"
#include "Creators/Directors/SceneDirector.hpp"
#include "Creators/Directors/FileWireframeModelDirector.hpp"
#include "Creators/Directors/FileSceneDirector.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"
#include <algorithm>


std::shared_ptr<Scene> LoadManager::loadEmptyScene()
{
    LOG_FUNC;

    return EmptySceneDirector().makeScene();
}

std::shared_ptr<Scene> LoadManager::loadScene(const std::string& filename)
{
    LOG_FUNC;

    return FileSceneDirector(filename).makeScene();
}

void LoadManager::loadWireframe(Scene& scene, const std::string& filename)
{
    LOG_FUNC;

    std::shared_ptr<IObject> object = FileWireframeModelDirector(filename).makeObject();
    std::copy(&object, &object + 1, scene.end());
}

void LoadManager::loadCamera(Scene& scene, const std::string& filename)
{
    LOG_FUNC;

    IObject* object = new CameraAdapter(new Camera());
    std::copy(&object, &object + 1, scene.end());
}
