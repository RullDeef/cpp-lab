#include "DefaultCameraDirector.hpp"
#include "Objects/Camera/CameraAdapter.hpp"
#include "Creators/Builders/CameraBuilder.hpp"
#include "Utils/Logger.hpp"


IObject* DefaultCameraDirector::makeObject()
{
    LOG_FUNC;

    CameraBuilder builder;

    auto camera = new CameraAdapter(builder.getResult());
    camera->setName("Main Camera");
    return camera;
}
