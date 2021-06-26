#include "API/Controller.hpp"
#include "AddHullModelCommand.hpp"
#include "API/Objects/ISceneObject.hpp"


AddHullModelCommand::AddHullModelCommand(std::shared_ptr<ISceneObject> object)
    : object(object)
{
}

void AddHullModelCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getObjectManager()->addObject(object);
}
