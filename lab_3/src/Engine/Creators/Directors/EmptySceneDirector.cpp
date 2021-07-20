#include "EmptySceneDirector.hpp"
#include "Creators/Builders/SceneBuilder.hpp"
#include "Creators/Builders/CameraBuilder.hpp"
#include "Creators/Builders/WireframeModelBuilder.hpp"
#include "Creators/Directors/WireframeCubeDirector.hpp"
#include "Scene/Scene.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Utils/Logger.hpp"


std::shared_ptr<Scene> EmptySceneDirector::makeScene()
{
    LOG_FUNC;

    SceneBuilder builder;

    std::shared_ptr<IObject> camera = std::shared_ptr<IObject>(new CameraAdapter(CameraBuilder().getResult()));
    camera->setName("Main Camera");
    builder.addObject(camera);

    builder.addObject(WireframeCubeDirector().makeObject());

    return builder.getResult();
}
