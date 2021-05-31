#pragma once

#include <memory>

class ICommand
{
public:
    virtual ~ICommand();
    virtual void execute() = 0;
};
