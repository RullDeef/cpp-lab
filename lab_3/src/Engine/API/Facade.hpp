#pragma once

#include <memory>
#include "API/Commands/ICommand.hpp"


class Facade
{
public:
    void execute(std::shared_ptr<ICommand> command);
};
