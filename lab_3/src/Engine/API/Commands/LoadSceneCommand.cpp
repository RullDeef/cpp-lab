#include "LoadSceneCommand.hpp"
#include "Utils/Logger.hpp"
#include "API/Controller.hpp"


void LoadSceneCommand::execute(std::shared_ptr<Controller> controller)
{
    LOG_FUNC;

    controller->getSceneManager()->loadScene();
}
