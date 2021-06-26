#include "ClearSelectionCommand.hpp"
#include "API/Controller.hpp"


void ClearSelectionCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getSelectionManager()->clearSelection();
}
