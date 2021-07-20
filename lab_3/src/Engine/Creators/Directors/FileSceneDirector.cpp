#include "FileSceneDirector.hpp"
#include "Creators/Builders/SceneBuilder.hpp"
#include "Creators/Directors/DefaultCameraDirector.hpp"
#include "Creators/Directors/WireframeCubeDirector.hpp"


FileSceneDirector::FileSceneDirector(const std::string& filename)
    : filename(filename)
{
}

std::shared_ptr<Scene> FileSceneDirector::makeScene()
{
    SceneBuilder builder;

    builder.addObject(DefaultCameraDirector().makeObject());
    builder.addObject(WireframeCubeDirector().makeObject());

    return builder.getResult();
}
