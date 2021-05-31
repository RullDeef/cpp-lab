#include "Facade.hpp"
#include "Utils/Logger.hpp"


void Facade::execute(std::shared_ptr<ICommand> command)
{
    try
    {
        command->execute();
    }
    catch (std::exception e)
    {
        LOGGER_ERROR(e.what());
    }
}
