#include "CommandQueue.hpp"
#include "../../Tools/Logger.hpp"

void CommandQueue::postCommand(std::shared_ptr<ICommand> command)
{
    LOG_FUNC;

    futureCommands.push_back(command);
}

void CommandQueue::executeNext()
{
    if (!futureCommands.empty())
    {
        LOG_FUNC;

        revertedCommands.clear();
        
        auto command = futureCommands.front();
        futureCommands.pop_front();

        command->execute();
    }
}

void CommandQueue::revert()
{
    LOG_FUNC;
}
