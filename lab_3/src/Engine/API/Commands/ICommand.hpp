#pragma once

#include <memory>
#include "../Controller.hpp"

class ICommand
{
public:
    ICommand(std::weak_ptr<Controller> controller);

    virtual ~ICommand();

    virtual bool isRevertible();

    virtual void execute() = 0;
    virtual void revert();

protected:
    std::shared_ptr<Controller> getController();

private:
    std::weak_ptr<Controller> controller;
};
