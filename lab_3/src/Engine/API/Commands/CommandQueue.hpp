#pragma once

#include <memory>
#include <deque>
#include "ICommand.hpp"

class CommandQueue
{
public:
    void postCommand(std::shared_ptr<ICommand> command);
    void executeNext();

    void revert();
    void executeReverted();

private:
    std::deque<std::shared_ptr<ICommand>> futureCommands;
    std::deque<std::shared_ptr<ICommand>> revertedCommands;
};