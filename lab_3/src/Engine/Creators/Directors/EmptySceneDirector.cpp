#include "EmptySceneDirector.hpp"
#include "Creators/Builders/SceneBuilder.hpp"
#include "Creators/Builders/CameraBuilder.hpp"
#include "Creators/Builders/WireframeModelBuilder.hpp"
#include "Creators/Directors/WireframeCubeDirector.hpp"
#include "Scene/Scene.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Utils/Logger.hpp"


Scene* EmptySceneDirector::makeScene()
{
    LOG_FUNC;

    SceneBuilder builder;

    IObject* camera = new CameraAdapter(CameraBuilder().getResult());
    camera->setName("Main Camera");
    builder.addObject(camera);

    builder.addObject(WireframeCubeDirector().makeObject());

    return builder.getResult();
}
