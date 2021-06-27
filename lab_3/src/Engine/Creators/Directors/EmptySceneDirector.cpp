#include "EmptySceneDirector.hpp"
#include "Scene/Scene.hpp"
#include "Utils/Logger.hpp"


Scene* EmptySceneDirector::makeScene()
{
    LOG_FUNC;

    return new Scene();
}
