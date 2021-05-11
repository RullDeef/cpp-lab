#include <stdexcept>
#include "ICommand.hpp"

ICommand::ICommand(std::weak_ptr<Controller> controller)
    : controller(controller)
{
}

ICommand::~ICommand()
{
}

bool ICommand::isRevertible()
{
    return false;
}

void ICommand::revert()
{
}

std::shared_ptr<Controller> ICommand::getController()
{
    if (auto ptr = controller.lock())
        return ptr;

    throw std::runtime_error("controller expired in Command::execute()");
}
