#include "CreateEmptySceneCommand.hpp"
#include "API/Controller.hpp"


void CreateEmptySceneCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getSceneManager()->createEmptyScene();
}
