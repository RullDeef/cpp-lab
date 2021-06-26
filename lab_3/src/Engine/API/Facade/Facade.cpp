#include "Facade.hpp"
#include "Commands/ICommand.hpp"
#include "Utils/Logger.hpp"


void Facade::execute(ICommand& command)
{
    LOG_FUNC;

    try
    {
        command.execute();
    }
    catch (std::exception e)
    {
        std::string msg = "Error: ";
        msg += e.what();
        LOGGER_ERROR(msg.c_str());
    }
}
