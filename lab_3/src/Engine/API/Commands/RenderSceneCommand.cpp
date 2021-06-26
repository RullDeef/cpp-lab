#include "RenderSceneCommand.hpp"
#include "Utils/Logger.hpp"
#include "API/Controller.hpp"


void RenderSceneCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getRenderManager()->renderScene();
}
