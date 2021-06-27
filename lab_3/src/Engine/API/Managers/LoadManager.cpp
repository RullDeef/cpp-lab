#include "LoadManager.hpp"
#include "Creators/Directors/EmptySceneDirector.hpp"
#include "Creators/Directors/FileWireframeModelDirector.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"
#include <algorithm>


Scene* LoadManager::loadEmptyScene()
{
    LOG_FUNC;

    return EmptySceneDirector().makeScene();
}

void LoadManager::loadWireframe(Scene& scene, const std::string& filename)
{
    LOG_FUNC;

    IObject* object = FileWireframeModelDirector(filename).makeWireframeModel();
    std::copy(&object, &object + 1, scene.end());
}

void LoadManager::loadCamera(Scene& scene, const std::string& filename)
{
    LOG_FUNC;

    IObject* object = new CameraAdapter(new Camera());
    std::copy(&object, &object + 1, scene.end());
}
