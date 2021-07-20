#include "DefaultCameraDirector.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Creators/Builders/CameraBuilder.hpp"
#include "Utils/Logger.hpp"


std::shared_ptr<IObject> DefaultCameraDirector::makeObject()
{
    LOG_FUNC;

    CameraBuilder builder;

    auto camera = std::shared_ptr<IObject>(new CameraAdapter(builder.getResult()));
    camera->setName("Main Camera");
    return camera;
}
