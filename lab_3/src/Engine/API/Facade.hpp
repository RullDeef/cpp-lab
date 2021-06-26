#pragma once

#include <memory>
#include "API/Commands/ICommand.hpp"
#include "API/Controller.hpp"
#include "API/Managers/IManagerFactory.hpp"

class Facade
{
public:
    Facade(std::shared_ptr<IManagerFactory> managerFactory);

    void execute(std::shared_ptr<ICommand> command);

private:
    std::shared_ptr<Controller> controller;
};
