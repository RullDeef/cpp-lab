#include "API/Controller.hpp"
#include "ClearSceneCommand.hpp"


void ClearSceneCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getObjectManager()->removeAllObjects();
}
