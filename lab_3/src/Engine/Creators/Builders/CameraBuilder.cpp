#include "CameraBuilder.hpp"
#include "Objects/Camera/Camera.hpp"


Camera* CameraBuilder::getResult()
{
    return new Camera();
}
