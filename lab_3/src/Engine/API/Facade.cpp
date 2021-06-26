#include "Facade.hpp"
#include "Utils/Logger.hpp"

Facade::Facade(std::shared_ptr<IManagerFactory> managerFactory)
{
    LOG_FUNC;

    controller = std::make_shared<Controller>(managerFactory);
}

void Facade::execute(std::shared_ptr<ICommand> command)
{
    try
    {
        command->execute(controller);
    }
    catch (std::exception e)
    {
        LOGGER_ERROR(e.what());
    }
}
