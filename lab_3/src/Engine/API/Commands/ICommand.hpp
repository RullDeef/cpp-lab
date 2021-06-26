#pragma once

#include <memory>

class Controller;


class ICommand
{
public:
    virtual ~ICommand();
    virtual void execute(std::shared_ptr<Controller> controller) = 0;
};
