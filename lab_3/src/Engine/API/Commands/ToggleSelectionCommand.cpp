#include "ToggleSelectionCommand.hpp"
#include "API/Controller.hpp"
#include "Utils/Logger.hpp"


ToggleSelectionCommand::ToggleSelectionCommand(std::shared_ptr<ISceneObject> object)
    : object(object)
{
}

void ToggleSelectionCommand::execute(std::shared_ptr<Controller> controller)
{
    LOG_FUNC;

    if (object.expired())
    {
        LOGGER_ERROR("expired object pointer");
        return;
    }

    controller->getSelectionManager()->toggleSelection(object.lock());
}
