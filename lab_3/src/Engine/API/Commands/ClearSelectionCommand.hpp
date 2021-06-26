#pragma once

#include "ICommand.hpp"


class ClearSelectionCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<Controller> controller) override;
};
